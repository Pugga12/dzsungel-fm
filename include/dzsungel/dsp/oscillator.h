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
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    float* table;
    size_t tableLen;
    float phase;
    float phaseIncrement;
    float oscillatorFrequency;
    float modIndex;
    float sampleRate;
} Oscillator;

/** 
 * Increase the stored oscillator phase by the precalculated amount.
 * @par This function uses the floating point variant of Oscillator
 *
 * @param oscillator Pointer to oscillator struct
 * @see oscF16IncreasePhase() OscillatorF16 (Q16.16 fixed point) variant of this function
 */
void oscIncreasePhase(Oscillator* oscillator);

/**
 * Init Oscillator struct
 * @par This function uses the floating point variant of Oscillator
 *
 * @param osc Pointer to oscillator struct
 * @param table Pointer to the wavetable to use
 * @param tableLen Length of the wavetable
 * @param freq Frequency of the oscillator
 * @param modIndex Modulator index/depth when using this oscillator as a modulator
 * @param sampleRate The rate at which this oscillator will be sampled at. Typical is 44100 Hz. Used to calculate oscillator phase increment.
 */
void oscInit(Oscillator* osc, float *table, size_t tableLen, float freq, float modIndex, float sampleRate);

void oscUpdateFrequency(Oscillator* osc, float newFreq);