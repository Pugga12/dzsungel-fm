#pragma once

extern "C" {
    #include "dsp/adsr.h"
}

enum EventType {
    // CC event (0 - 127)
    CC7_VOLUME = 7,
    CC11_EXPRESSION = 11,

    // other events (>127)
    NOTE_ON = 128,
    NOTE_OFF = 129,
    PROGRAM_CHANGE = 130,
    PITCH_BEND = 131,
};

enum OscillatorType {
    STANDARD_PM,
    FEEDBACK
};

struct Program {
    float modIndex;
    float cToMRatio;
    Envelope ampEnv;
    Envelope modEnv;
    OscillatorType type;
};

struct VoiceEvent {
    uint32_t blockId;
    uint8_t voiceId;
    EventType type;

    uint8_t offset;
    uint32_t val;
    uint32_t p2;
};