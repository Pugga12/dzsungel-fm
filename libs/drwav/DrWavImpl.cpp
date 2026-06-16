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

#include <cstddef>
#define DR_WAV_IMPLEMENTATION
#include "DrWavImpl.hpp"
#include <stdexcept>
namespace DrWavImpl {
    drwav_uint64 writeWav(std::vector<float> &input, drwav_uint32 sampleRate, const std::string &filename) {
        drwav wav;
        drwav_data_format format;
        format.container = drwav_container_riff;
        format.format = DR_WAVE_FORMAT_IEEE_FLOAT;
        format.channels = 1;
        format.sampleRate = sampleRate;
        format.bitsPerSample = 32;
        drwav_init_file_write(&wav, filename.data(), &format, NULL);

        drwav_uint64 bytesWritten = drwav_write_pcm_frames(&wav, input.size(), input.data());

        if (bytesWritten == 0) {
            drwav_uninit(&wav);
            throw std::runtime_error("DrWav wrote 0 bytes to the output wav file!");
        }

        drwav_uninit(&wav);

        return bytesWritten;
    }
}