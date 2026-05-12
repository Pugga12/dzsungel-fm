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
#include <stdbool.h>
#include <stdlib.h>
#define WAV_FORMAT_PCM 1
#define WAV_FORMAT_IEEE_FLOAT 3

/**
 * Generate a WAV file in the Signed 16-bit PCM format
 *
 * @param name Filename
 * @param data Pointer to samples
 * @param frameCount Number of samples in the input buffer
 * @param sampleRate Sample rate in Hz (typical is 44000 Hz)
 * @see writeWavF32() IEEE Float version of this function
 */
bool writeWavS16(char *name, int16_t *data, size_t frameCount, uint32_t sampleRate);
bool writeWavF32(const char *name, float *data, size_t frameCount, uint32_t sampleRate);