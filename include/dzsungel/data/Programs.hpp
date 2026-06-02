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
#include "types.hpp"
#include <cstdint>
#include <map>
#include <vector>
#include <ranges>

static Program DEFAULT_PROGRAM {
    1.5,
    2.5,
    {
        MS_TO_S(10),
        MS_TO_S(400),
        0.5,
        MS_TO_S(500)
    },
    {
        MS_TO_S(10),
        MS_TO_S(200),
        0.5,
        MS_TO_S(500)
    },
    FEEDBACK
};

class ProgramManager {
    static const std::map<uint8_t, Program> DEFAULT_PROGRAM_LIBRARY;

    public:
    static const Program* getProgram(uint8_t id) {
        std::map<uint8_t, Program>::const_iterator iter = DEFAULT_PROGRAM_LIBRARY.find(id);

        if (iter != DEFAULT_PROGRAM_LIBRARY.end()) {
            return &iter->second;
        }
        
        return nullptr;
    }

    static bool hasPreset(uint8_t id) {
        return DEFAULT_PROGRAM_LIBRARY.find(id) != DEFAULT_PROGRAM_LIBRARY.end();
    }

    static std::vector<uint8_t> availablePresets() {
        auto keys = std::views::keys(DEFAULT_PROGRAM_LIBRARY);
        return std::vector<uint8_t>(keys.begin(), keys.end());
    }

    static size_t getNumDefaultPrograms() {
        return DEFAULT_PROGRAM_LIBRARY.size();
    }
};