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
#include <stdbool.h>
#define WT_SIZE 4096

/**
 * Generate a sine wavetable with n points
 *
 * @param ptr Output buffer
 * @param length Number of points to generate
 */
bool wavetableGenSine(float *ptr, size_t length);

/**
 * Generate a triangle wavetable with n points
 *
 * @param table Output buffer
 * @param length Number of points to generate
 */
bool wavetableGenTriangle(float *table, size_t length);

/**
 * Band-limited sine wave with n length and k harmonics using a fourier series
 *
 * @param table Output buffer
 * @param length Number of points to generate
 * @param maxHarmonics Maximum harmonics used for the fourier series
 * @deprecated This function is deprecated and should not be used. A polyBLEP SM implementation of this function will be created later.
 */
bool wavetableGenBLSaw(float *table, size_t length, uint32_t maxHarmonics);
