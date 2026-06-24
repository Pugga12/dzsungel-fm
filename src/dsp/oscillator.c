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
#include <stdint.h>
#include <stdlib.h>
#include "dsp/oscillator.h"

void oscIncreasePhase(Oscillator* oscillator) {
    oscillator->phase += oscillator->phaseIncrement;
    if (oscillator->phase >= oscillator->tableLen) oscillator->phase -= oscillator->tableLen;
}

void oscInit(Oscillator* osc, float *table, size_t tableLen, float freq, float modIndex, float sampleRate) {
    osc->table = table;
    osc->tableLen = tableLen;
    osc->phase = 0.0f;
    osc->oscillatorFrequency = freq;
    osc->modIndex = modIndex;
    osc->phaseIncrement = ((float)tableLen * freq) / sampleRate;
    osc->sampleRate = sampleRate;
}

void oscUpdateFrequency(Oscillator *osc, float newFreq) {
    osc->oscillatorFrequency = newFreq;
    osc->phaseIncrement = ((float)osc->tableLen * newFreq) / osc->sampleRate;
}
