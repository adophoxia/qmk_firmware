/* Copyright 2022 @ Keychron(https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 20

/* RGB Matrix Driver Configuration */
#define SNLED27351_DRIVER_COUNT 2
#define DRIVER_ADDR_1 SNLED27351_I2C_ADDRESS_VDDIO
#define DRIVER_ADDR_2 SNLED27351_I2C_ADDRESS_GND

#define SNLED27351_CURRENT_TUNE \
    { 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52 }

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {5, 4} }

/* Disable DIP switch in matrix data */
#define MATRIX_MASKED

/* turn off effects when suspended */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES