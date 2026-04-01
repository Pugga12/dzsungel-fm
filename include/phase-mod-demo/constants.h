#pragma once
#include "fix16.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288) // Define M_PI with high precision
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