/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software : you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

// clang-format off

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, CB1_CA15,   C_15,   B_15},
    {0, CB1_CA14,   C_14,   B_14},
    {0, CB1_CA13,   C_13,   B_13},
    {0, CB1_CA12,   C_12,   B_12},
    {0, CB1_CA11,   C_11,   B_11},
    {0, CB1_CA10,   C_10,   B_10},
    {0, CB1_CA9,    C_9,    B_9},
    {0, CB1_CA8,    C_8,    B_8},
    {0, CB1_CA7,    C_7,    B_7},
    {0, CB1_CA6,    C_6,    B_6},
    {0, CB1_CA5,    C_5,    B_5},
    {0, CB1_CA4,    C_4,    B_4},
    {0, CB1_CA3,    C_3,    B_3},
    {0, CB1_CA2,    C_2,    B_2},

    {0, G_15,   I_15,   H_15},
    {0, G_14,   I_14,   H_14},
    {0, G_13,   I_13,   H_13},
    {0, G_12,   I_12,   H_12},
    {0, G_11,   I_11,   H_11},
    {0, G_10,   I_10,   H_10},
    {0, G_9,    I_9,    H_9},
    {0, G_8,    I_8,    H_8},
    {0, G_7,    I_7,    H_7},
    {0, G_6,    I_6,    H_6},
    {0, G_5,    I_5,    H_5},
    {0, G_4,    I_4,    H_4},
    {0, G_3,    I_3,    H_3},
    {0, G_2,    I_2,    H_2},
    {0, G_1,    I_1,    H_1},

    {0, D_15,   F_15,   E_15},
    {0, D_14,   F_14,   E_14},
    {0, D_13,   F_13,   E_13},
    {0, D_12,   F_12,   E_12},
    {0, D_11,   F_11,   E_11},
    {0, D_10,   F_10,   E_10},
    {0, D_9,    F_9,    E_9},
    {0, D_8,    F_8,    E_8},
    {0, D_7,    F_7,    E_7},
    {0, D_6,    F_6,    E_6},
    {0, D_5,    F_5,    E_5},
    {0, D_4,    F_4,    E_4},
    {0, D_3,    F_3,    E_3},
    {0, D_2,    F_2,    E_2},
    {0, D_1,    F_1,    E_1},

    {1, CB1_CA15,   C_15,   B_15},
    {1, CB1_CA14,   C_14,   B_14},
    {1, CB1_CA13,   C_13,   B_13},
    {1, CB1_CA12,   C_12,   B_12},
    {1, CB1_CA11,   C_11,   B_11},
    {1, CB1_CA10,   C_10,   B_10},
    {1, CB1_CA9,    C_9,    B_9},
    {1, CB1_CA8,    C_8,    B_8},
    {1, CB1_CA7,    C_7,    B_7},
    {1, CB1_CA6,    C_6,    B_6},
    {1, CB1_CA5,    C_5,    B_5},
    {1, CB1_CA4,    C_4,    B_4},
    {1, CB1_CA2,    C_2,    B_2},
    {1, CB1_CA1,    C_1,    B_1},

    {1, G_15,   I_15,   H_15},
    {1, G_13,   I_13,   H_13},
    {1, G_12,   I_12,   H_12},
    {1, G_11,   I_11,   H_11},
    {1, G_10,   I_10,   H_10},
    {1, G_9,    I_9,    H_9},
    {1, G_8,    I_8,    H_8},
    {1, G_7,    I_7,    H_7},
    {1, G_6,    I_6,    H_6},
    {1, G_5,    I_5,    H_5},
    {1, G_4,    I_4,    H_4},
    {1, G_3,    I_3,    H_3},
    {1, G_2,    I_2,    H_2},

    {1, D_15,   F_15,   E_15},
    {1, D_14,   F_14,   E_14},
    {1, D_13,   F_13,   E_13},
    {1, D_9,    F_9,    E_9},
    {1, D_6,    F_6,    E_6},
    {1, D_5,    F_5,    E_5},
    {1, D_4,    F_4,    E_4},
    {1, D_3,    F_3,    E_3},
    {1, D_2,    F_2,    E_2},
    {1, D_1,    F_1,    E_1},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, __ },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 },
        { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43 },
        { 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, __, 56, 57 },
        { 58, __, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, __},
        { 71, 72, 73, __, __, __, 74, __, __, 75, 76, 77, 78, 79, 80 },
    },
    {
        // LED Index to Physical Position
        {0, 0}, {18, 0}, {33, 0}, {48, 0}, {62, 0}, {81, 0}, {95, 0}, {110, 0}, {125, 0}, {143, 0}, {158, 0}, {178, 0}, {187, 0}, {203, 0},
        {0,15}, {15,15}, {29,15}, {44,15}, {59,15}, {73,15}, {88,15}, {103,15}, {117,15}, {132,15}, {146,15}, {161,15}, {176,15}, {195,15}, {224,15},
        {4,26}, {22,26}, {37,26}, {51,26}, {66,26}, {81,26}, {95,26}, {110,26}, {125,26}, {139,26}, {154,26}, {173,26}, {187,26}, {201,26}, {224,26},
        {6,38}, {26,38}, {40,38}, {55,38}, {70,38}, {84,38}, {99,38}, {114,38}, {128,38}, {143,38}, {158,38}, {172,38},           {195,38}, {224,38},
        {8,49},          {33,49}, {48,49}, {62,49}, {77,49}, {92,49}, {106,49}, {121,49}, {136,49}, {150,49}, {165,49}, {186,49}, {203,52},
        {2,61}, {20,61}, {38,61},                            {94,61},                     {147,61}, {161,61}, {178,61}, {192,64}, {203,64}, {224,64},
    },
    {
        // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1,          1,       1, 1, 1, 1, 1, 1,
    }
};
#endif
