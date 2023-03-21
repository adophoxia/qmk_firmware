/* Copyright 2022 @Adophoxia

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

enum custom_keycodes {
    KC_WLCK = SAFE_RANGE,
    ENC_LFT,
    ENC_RGT,
    ENC_PRS
};

enum layers{
    WIN_BASE,
    WIN_FN,
    WIN_MM
};


#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

#define TSK_EXP C(S(KC_ESC))
#define KC_WLCK MAGIC_TOGGLE_GUI
#define LAYER1 MO(WIN_FN)
#define LAYER2 MO(WIN_MM)