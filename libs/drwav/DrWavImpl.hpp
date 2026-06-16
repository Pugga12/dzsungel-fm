/*
Copyright (C) 2026  Adam Aptowitz

Dr Wav Library Implementation
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
#include <string>
#include <vector>
extern "C" {
#include "dr_wav.h"
}

namespace DrWavImpl {
    drwav_uint64 writeWav(std::vector<float>& input, drwav_uint32 sampleRate, const std::string& filename);
}