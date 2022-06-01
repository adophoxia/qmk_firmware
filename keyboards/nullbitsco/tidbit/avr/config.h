/* Copyright 2021 Jay Greco
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

#include "config_common.h"

/* Used to set remote for remote KB if VUSB detect doesn't work. */
// #define KEYBOARD_REMOTE

// Workaround for freezing after MacOS sleep
#define USB_SUSPEND_WAKEUP_DELAY 200

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, E6, D7, C6, D4 }
#define MATRIX_COL_PINS { NO_PIN, NO_PIN, F4, F5, F6, F7 }
#define UNUSED_PINS

/* Optional SMT LED pins */
#define RGB_DI_PIN B6

/* Optional encoder pins */
#define ENCODERS_PAD_A { B2, B4, D0, D3 }
#define ENCODERS_PAD_B { B3, B5, D1, D2 }
