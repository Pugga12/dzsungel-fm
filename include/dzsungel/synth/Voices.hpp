/*
Copyright (C) 2026  Adam Aptowitz

This file is part of Dzsungel

Dzsungel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Dzsungel.  If not, see <http://www.gnu.org/license>
*/
#pragma once
#include <cstdint>
#include <vector>
#include "types.hpp"

extern "C" {
#include "dsp/oscillator.h"
#include "dsp/adsr.h"
}

enum VoiceState {
    VOICE_IDLE,
    VOICE_WAIT,
    VOICE_ACTIVE,
    VOICE_RELEASING,
};

class Voice {
    public:
    virtual ~Voice() = default;
    virtual void processBlock(float* output, size_t blockSize) = 0;
    virtual void pushEv(VoiceEvent& ev) = 0;
    virtual void init(const Program& program, float* modTable, float* carrierTable, float sr, size_t tableSize) = 0;

    virtual VoiceState getState() const = 0;
    virtual uint32_t getNote() const = 0;
};

class WavetableVoice : public Voice{
    private:
        std::vector<VoiceEvent> events;
        OscillatorType type;
        Oscillator carrier;
        Oscillator modulator;
        ADSR ampEnv;
        ADSR modEnv;

        uint32_t currentMidiNote = 0;
        uint8_t eventIndex = 0;
        VoiceState state = VOICE_IDLE;
        float sampleRate;
        float cToMRatio;
        float voiceSr = 44100.0f;
        
        float pitchBendRange = 2.0f;
        float baseCarrier = 0.0f;
        float currentCarrierFrequency = 0.0f;
        float targetCarrierFrequency = 0.0f;
        float rampInc = 0.0f;
        uint32_t rampSamplesRemaining = 0;

        float expresssion = 1.0f;
        float masterVolume = 1.0f;
        float lastOutput = 0;

        uint8_t currentProgramId = 255;

        void noteOn(uint32_t midiNote, uint32_t velocity);
        void noteOff();
        void renderInnerNormal(uint32_t start, uint32_t end, float* outputBuffer);
        void renderInnerFeedback(uint32_t start, uint32_t end, float* output);
        void setMidiBend(uint32_t bVal);
        void changeProgram(uint32_t prgId);
    public:
        void processBlock(float* outputBuffer, size_t blockSize) override;
        void pushEv(VoiceEvent& ev) override;
        void init(const Program& program, float* modTable, float* carrierTable, float sr, size_t tableSize) override;
        
        VoiceState getState() const override {
            return state;
        }

        uint32_t getNote() const override {
            return currentMidiNote;
        }

        // default constructor, to make the VoiceManager init straight-forward
        WavetableVoice() :
            carrier{},
            modulator{},
            ampEnv{},
            modEnv{},
            sampleRate(44100),
            cToMRatio(1),
            type(STANDARD_PM)
        {
            events.reserve(8);
        }
};

