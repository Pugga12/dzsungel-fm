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
#include "fix16.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288) // Define M_PI with high precision
#endif

#ifndef TWO_OVER_PI
#define TWO_OVER_PI (2/M_PI)
#endif


#ifndef TWO_PI_FLOAT
#define TWO_PI_FLOAT (2 * M_PI)
#endif

#ifndef TWO_PI_FIX16
#define TWO_PI_FIX16 (F16(TWO_PI_FLOAT))
#endif

#define FADD(a,b) fix16_add(a,b)
#define FMUL(a,b) fix16_mul(a,b)
#define FSUB(a,b) fix16_sub(a,b)
#define FDIV(a,b) fix16_div(a,b)