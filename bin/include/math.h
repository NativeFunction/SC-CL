/*H**********************************************************************
* FILENAME :	math.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Types to be used with all targets and platforms of SC-CL.
*
* NOTES :
*		This file is part of SC-CL's include library.
*
* LICENSE :
*
*		Copyright 2016 SC-CL
*
*		Redistribution and use in source and binary forms, with or without
*		modification, are permitted provided that the following conditions are met:
*
*		* Redistributions of source code must retain the above copyright
*		notice, this list of conditions and the following disclaimer.
*
*		* Redistributions in binary form must reproduce the above copyright
*		notice, this list of conditions and the following disclaimer in the
*		documentation and/or other materials provided with the distribution.
*
*		* Neither SC-CL nor its contributors may be used to endorse or promote products
*		derived from this software without specific prior written permission.
*
*		* Redistribution of this software in source or binary forms shall be free
*		of all charges or fees to the recipient of this software.
*
*		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*		ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*		WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*		DISCLAIMED. IN NO EVENT SHALL SC-CL BE LIABLE FOR ANY
*		DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*		(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*		(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* AUTHORS :
*		Rocko Tompkins
*		Nathan James
*       Pliskin
*H*/
#pragma once

#define SCR_PI 3.14159265358979323846
#define SCR_EXP 2.71828182845904523536

float scr_abs(float x) {
    return (x < 0) ? -x : x;
}

float scr_sign(float x) {
    return (x > 0) ? 1.0f : ((x < 0) ? -1.0f : 0.0f);
}

float scr_pow(float base, float exponent) {
    float result = 1.0f;
    int i;
    for (i = 0; i < scr_abs(exponent); i++) {
        result *= base;
    }
    return (exponent >= 0) ? result : 1.0f / result;
}

float scr_sqrt(float x) {
    float guess = 1.0f;
    float prev_guess;
    do {
        prev_guess = guess;
        guess = 0.5f * (prev_guess + x / prev_guess);
    } while (scr_abs(guess - prev_guess) >= 0.00001f);
    return guess;
}

float scr_exp(float x) {
    float result = 1.0f;
    float term = 1.0f;
    for (int i = 1; scr_abs(term) >= 0.00001f; i++) {
        term *= x / i;
        result += term;
    }
    return result;
}

float scr_log(float x) {
    float result = 0.0f;
    float term = (x - 1) / (x + 1);
    float prev_term;
    for (int i = 1; scr_abs(term) >= 0.00001f; i += 2) {
        prev_term = term;
        term = prev_term * ((x - 1) / (x + 1)) * ((x - 1) / (x + 1));
        result += term / i;
    }
    return 2.0f * result;
}

float scr_sin(float x) {
    float result = x;
    float term = x;
    for (int i = 3; scr_abs(term) >= 0.00001f; i += 2) {
        term *= -1.0f * x * x / (i * (i - 1));
        result += term;
    }
    return result;
}

float scr_cos(float x) {
    return scr_sin(SCR_PI / 2 - x);
}

float scr_tan(float x) {
    return scr_sin(x) / scr_cos(x);
}

float scr_asin(float x) {
    float result = x;
    float term = x;
    float prev_term;
    float x_squared = x * x;
    for (int i = 1; scr_abs(term) >= 0.00001f; i += 2) {
        prev_term = term;
        term *= (x_squared * i * i) / ((i + 1) * (i + 2));
        result += term;
    }
    return result;
}

float scr_acos(float x) {
    return SCR_PI / 2 - scr_asin(x);
}

float scr_atan(float x) {
    float result = x;
    float term = x;
    for (int i = 1; scr_abs(term) >= 0.00001f; i += 2) {
        term *= -1.0f * x * x;
        result += term / (i + 1);
    }
    return result;
}

float scr_atan2(float y, float x) {
    if (x > 0) {
        return scr_atan(y / x);
    } else if (x < 0) {
        if (y >= 0) {
            return scr_atan(y / x) + SCR_PI;
        } else {
            return scr_atan(y / x) - SCR_PI;
        }
    } else {
        if (y > 0) {
            return SCR_PI / 2;
        } else if (y < 0) {
            return -SCR_PI / 2;
        } else {
            return 0.0f;
        }
    }
}

float scr_cosh(float x) {
    return (scr_exp(x) + scr_exp(-x)) / 2.0f;
}

float scr_sinh(float x) {
    return (scr_exp(x) - scr_exp(-x)) / 2.0f;
}

float scr_tanh(float x) {
    float ex = scr_exp(x);
    float e_minus_x = scr_exp(-x);
    return (ex - e_minus_x) / (ex + e_minus_x);
}

float scr_ceil(float x) {
    int intPart = (int)x;
    return (x > intPart) ? intPart + 1.0f : intPart;
}

float scr_floor(float x) {
    int intPart = (int)x;
    return (x < intPart) ? intPart - 1.0f : intPart;
}

float scr_fmod(float x, float y) {
    return x - y * scr_floor(x / y);
}

float scr_modf(float x, float *intPart) {
    *intPart = scr_floor(x);
    return x - *intPart;
}

float scr_ldexp(float x, int exp) {
    float result = x;
    int i;
    if (exp > 0) {
        for (i = 0; i < exp; i++) {
            result *= 2.0f;
        }
    } else {
        for (i = 0; i < -exp; i++) {
            result /= 2.0f;
        }
    }
    return result;
}

void scr_frexp(float x, int *exp, float *frac) {
    *exp = 0;
    *frac = x;

    while (scr_abs(*frac) >= 0.5f) {
        *frac /= 2.0f;
        (*exp)++;
    }
}