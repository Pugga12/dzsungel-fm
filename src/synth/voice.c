//
// Created by adama on 5/1/26.
//
#include "synth/voice.h"
#include <stdbool.h>
#include <assert.h>
#include "constants.h"
#include "math.h"
#include "dsp/wavetablegen.h"

bool initVoice(Voice *v, Oscillator* carrier, Oscillator* modulator, ADSR* adsr, float* outBuffer, size_t bufferSize) {
    if (!v || !carrier || !modulator || !adsr || !outBuffer || bufferSize == 0) {
        assert(0 && "Invalid arguments passed to initVoice().l.");
        return false;
    }

    v->carrier = carrier;
    v->modulator = modulator;
    v->adsr = adsr;
    v->bufferSize = bufferSize;
    v->outBuffer = outBuffer;
    v->on = true;

    return true;
}

float tableLinInterp(float* wtPtr, float x) {
    int i = (int)x;
    float a1 = wtPtr[i];
    float a2 = wtPtr[(i + 1) % WT_SIZE];
    float decimal = x - (float)i;
    return a1 + decimal * (a2 - a1);
}

static float bitCrush(const float x, const uint8_t precision) {
    const float max = (float)(1 << precision) - 1;
    const float max2 = max / 2;

    int quantitized = (int)roundf((x + 1) * max2);
    return (((float)quantitized / max) * 2) - 1;
}

void voiceModulate(Voice* v, uint64_t releaseAt) {
    setGate(v->adsr, true);
    const float scalingConstant = v->modulator->tableLen / (1.0f * M_PI);
    const float deviationMultiplier = v->modulator->modIndex * scalingConstant;

    for (int i = 0; i < v->bufferSize; i++) {
        const float modVal = v->modulator->table[(int)v->modulator->phase];
        const float qModVal = bitCrush(modVal, 8);

        // modulate the carrier by adding the phase deviation to the accumulator value
        float perturbed = v->carrier->phase + (qModVal * deviationMultiplier);

        if (i == releaseAt) {
            setGate(v->adsr, false);
        }

        // phase accumulator wrapping
        perturbed = fmodf(perturbed, (float)v->carrier->tableLen);
        while (perturbed < 0) perturbed += v->carrier->tableLen;

#ifdef EXPONENTIAL_ADSR
        const float amplitude = adsrCalculateExp(v->adsr);
#else
        const float amplitude = adsrCalculateLinear(v->adsr);
#endif
        const float qPerturbation = bitCrush(perturbed, 8);
        v->outBuffer[i] = v->carrier->table[(int)qPerturbation] * amplitude;

        // increase accumulators
        oscIncreasePhase(v->carrier);
        oscIncreasePhase(v->modulator);
    }
}