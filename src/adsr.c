#include "adsr.h"
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#define EPSILON 0.0001

// === MATH ===
static float linInterp(float b, float a2, float a1, float x) {
    return ((a2 - a1) * x) + b; // y = (a1-a2)x + b
}

static float calculateExpRatio(float t, float sampleRate) {
    uint32_t n = (uint32_t)(t*sampleRate);
    float exponent = log(EPSILON) / n;
    return (float) 1 - exp(exponent);
}

// === ADSR Functions ===

void cacheRatios(ADSR* adsr) {
    adsr->aRatioCache = calculateExpRatio(adsr->attackSeconds, adsr->sampleRate);
    adsr->dRatioCache = calculateExpRatio(adsr->decaySeconds, adsr->sampleRate);
    adsr->rRatioCache = calculateExpRatio(adsr->releaseSeconds, adsr->sampleRate);
}

bool initADSR(ADSR* ptr, float attackSeconds, float releaseSeconds, float decaySeconds, float sustainLevel, float sampleRate, bool precalculateRatios) {
    // divide by zero checks at init (time vals cannot be less then 0)
    if (attackSeconds <= 0 || decaySeconds <= 0 || releaseSeconds <= 0) {
        assert(0 && "Invalid time values passed to ADSR creation");
        return false;
    }

    ptr->state = IDLE;
    ptr->attackSeconds = attackSeconds;
    ptr->decaySeconds = decaySeconds;
    ptr->releaseSeconds = releaseSeconds;
    ptr->sustainLevel = sustainLevel;
    ptr->gate = false;
    ptr->prevGate = false;
    ptr->sampleRate = sampleRate;
    ptr->aRatioCache = 0.0f;
    ptr->dRatioCache = 0.0f;
    ptr->rRatioCache = 0.0f;
    if (precalculateRatios) {
        cacheRatios(ptr);
    }
}

void reset(ADSR* ptr) {
    ptr->state = IDLE;
    ptr->gate = false;
    ptr->sampleCounter = 0;
}

void setGate(ADSR* adsr, bool gate) {
    adsr->gate = gate;
}

float adsrCalculateLinear(ADSR* ptr) {
    float timeElapsed = ptr->sampleCounter / ptr->sampleRate;
    float output = 0.0f;

    if (ptr->gate && !ptr->prevGate) {
        ptr->state = ATTACK;
        ptr->sampleCounter = 0;
    }
    if (!ptr->gate && ptr->prevGate) {
        ptr->state = RELEASE;
        ptr->sampleCounter = 0;
    }

    switch (ptr->state) {
        case ATTACK:
            if (timeElapsed >= ptr->attackSeconds) {
                ptr->state = DECAY;
                ptr->sampleCounter = 0;
                return 1.0f;
            }
            output = timeElapsed / ptr->attackSeconds;
            break;
        case DECAY:
            if (timeElapsed >= ptr->decaySeconds) {
                ptr->state = SUSTAIN;
                ptr->sampleCounter = 0;
                return ptr->sustainLevel;
            }
            float decayProgress = timeElapsed / ptr->decaySeconds;
            output = linInterp(1.0f, ptr->sustainLevel, 1.0f, decayProgress);
            break;
        case SUSTAIN:
            output = ptr->sustainLevel;
            break;
        case RELEASE:
            if (timeElapsed >= ptr->releaseSeconds) {
                ptr->state = IDLE;
                return 0.0f;
            }
            float releaseProgress = timeElapsed / ptr->releaseSeconds;
            output = ptr->sustainLevel * (1.0f - releaseProgress);
            break;
        case IDLE:
            break;
        default:
            assert(0 && "Invalid ADSR state");
            return 0.0f;
    }

    ptr->sampleCounter++;
    ptr->prevGate = ptr->gate;
    return output;
}