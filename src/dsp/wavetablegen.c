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
#include "dsp/wavetablegen.h"

#include <assert.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "constants.h"
#include <stdbool.h>

bool wavetableGenSine(float *ptr, size_t length) {
    if (ptr == NULL || length == 0) {
        assert(0 && "wtSineDiscretize() called with invalid args");
        return false;
    }

    for (int i = 0; i < length; i++) {
        float theta = (2 * M_PI) * ((float)i / length);
        ptr[i] = sinf(theta);
    }

    return true;
}

// TODO: Rewrite to use polyBLEP because the fourier series generates bad points at the discontinuity 
bool wavetableGenBLSaw(float *table, size_t length, uint32_t maxHarmonics) {
    if (table == NULL || length == 0 || maxHarmonics == 0) {
        assert(0 && "wtSawBL() called with invalid args");
        return false;
    }

    for (int i = 0; i < length; i++) {
        float phase = (float)i / (float)length;
        float x = 0.0f;

        for (int k = 1; k <= maxHarmonics; k++) {
            x += sinf(2.0f * M_PI * phase * k) / (float)k;
        }

        x *= TWO_OVER_PI;

        table[i] = x;
    }

    table[length - 1] = table[0];
    return true;
}

bool wavetableGenTriangle(float *table, size_t length) {
    if (table == NULL || length == 0) {
        assert(0 && "wtTriangle() called with invalid args");
        return false;
    }

    for (int i = 0; i < length; i++) {
        float phase = (float)i / (float)length;
        table[i] = 1.0f - 4.0f * fabsf(phase - 0.5f);
    }

    return true;
}