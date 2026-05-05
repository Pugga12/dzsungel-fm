#include <stdlib.h>
#include <stdio.h>
#include "dsp/adsr.h"
#include "dsp/oscillator.h"
#include "io/wav.h"
#include "dsp/wavetablegen.h"
#include <stdbool.h>
#include "synth/voice.h"
#include "synth/mixer.h"
#define MS_TO_S(ms) (ms / 1000.0f)


static Oscillator o1C;
static Oscillator o1M;
static Oscillator o2C;
static Oscillator o2M;
static ADSR a1;
static ADSR a2;

static float* ob1;
static float* ob2;
static float* sinePtr;
static float* trianglePtr;

static Voice voices[2] = {};

void printPoints(float* values, size_t length) {
    printf("i = [");
    for (int i = 0; i < length; i++) {
        printf("(%i, %.9f)", i, values[i]);
        if (!(i == length - 1)) {
            printf(",");
        }
    }
    printf("]\n");
}

void initEverything() {
    oscInit(&o1C, trianglePtr, WT_SIZE, 32.7f, 1, 44100.0f);
    oscInit(&o1M, sinePtr, WT_SIZE, 49.05f, 2.0f, 44100.0f);
    oscInit(&o2C, sinePtr, WT_SIZE, 261.63f, 1, 44100.0f);
    oscInit(&o2M, sinePtr, WT_SIZE, 523.26f, 2.0f, 44100.0f);

    initADSR(&a1, MS_TO_S(500), MS_TO_S(250), MS_TO_S(25), 0.5, 44100.0f);
    initADSR(&a2, MS_TO_S(500), MS_TO_S(250), MS_TO_S(25), 0.5, 44100.0f);
    initVoice(&voices[0], &o1C, &o1M, &a1, ob1, 88200);
    initVoice(&voices[1], &o2C, &o2M, &a2, ob2, 88200);

    voiceModulate(&voices[0], 80000);
    voiceModulate(&voices[1], 75000);
}

int main(int argc, char const *argv[])
{
    sinePtr = malloc(sizeof(float) * WT_SIZE);
    trianglePtr = malloc(sizeof(float) * WT_SIZE);
    ob1 = malloc(sizeof(float) * 88200);
    ob2 = malloc(sizeof(float) * 88200);
    float* obFinal = malloc(sizeof(float) * 88200);

    wavetableGenSine(sinePtr, WT_SIZE);
    wavetableGenTriangle(trianglePtr, WT_SIZE);
    initEverything();

    mix(voices, 2, obFinal, 88200);
    writeWavF32("demo-f32.wav", obFinal, 88200, 44100);

    free(sinePtr);
    free(obFinal);
    free(ob1);
    free(ob2);
    free(trianglePtr);
    return 0;
}
