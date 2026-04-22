#pragma once
#include <stdint.h>
#include <stdbool.h>

enum ADSRState {
    IDLE,
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
};

typedef struct 
{
    int state;
    float attackSeconds;
    float releaseSeconds;
    float decaySeconds;
    float sustainLevel;
    bool gate; 
    bool prevGate;
    uint32_t sampleRate;
    uint32_t sampleCounter;

    float aRatioCache;
    float dRatioCache;
    float rRatioCache;
} ADSR;

bool initADSR(ADSR* ptr, float attackSeconds, float releaseSeconds, float decaySeconds, float sustainLevel, float sampleRate, bool precacheRatios);

void reset(ADSR* ptr);

float adsrCalculateLinear(ADSR* ptr);

void setGate(ADSR* adsr, bool gate);