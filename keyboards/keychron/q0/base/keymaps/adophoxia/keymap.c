/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H

enum layers { _BASE, _FN1};

/*
    * ┌───┬───┬───┬───┐
    * │TG1│Esc│Bsp│Tab│
    * ├───┼───┼───┼───┤
    * │Num│ / │ * │ - │
    * ├───┼───┼───┼───┤
    * │ 7 │ 8 │ 9 │   │
    * ├───┼───┼───┤ + │
    * │ 4 │ 5 │ 6 │   │
    * ├───┼───┼───┼───┤
    * │ 1 │ 2 │ 3 │   │
    * ├───┴───┼───┤Ent│
    * │ 0     │ . │   │
    * └───────┴───┴───┘
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_numpad_6x4(
        TG(_FN1),   KC_ESC,  KC_BSPC,   KC_TAB,
        KC_NUM,     KC_PSLS, KC_PAST,   KC_PMNS,
        KC_P7,      KC_P8,   KC_P9,
        KC_P4,      KC_P5,   KC_P6,     KC_PPLS,
        KC_P1,      KC_P2,   KC_P3,
        KC_P0,               KC_PDOT,   KC_PENT
    ),

    [_FN1] = LAYOUT_numpad_6x4(
        TG(_FN1),   KC_MUTE, KC_VOLD,   KC_VOLU,
        RGB_MOD,    RGB_VAI, RGB_HUI,   KC_DEL,
        RGB_RMOD,   RGB_VAD, RGB_HUD,
        RGB_SAI,    RGB_SPI, KC_MPRV,   _______,
        RGB_SAD,    RGB_SPD, KC_MPLY,
        RGB_TOG,             KC_MNXT,   _______
    )
};

#define ARRAYSIZE(arr) sizeof(arr)/sizeof(arr[0])

uint8_t numlock_arrows[] = {
    9, 11, 13, 16
};

void numlock_arrows_indicators(void);

void numlock_arrows_indicators() {
    if (!host_keyboard_led_state().num_lock) {
        for (uint8_t i = 0; i < ARRAYSIZE(numlock_arrows); i++) {
            rgb_matrix_set_color(numlock_arrows[i], RGB_BLUE);
        }
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, RGB_WHITE);
    } else {
        if (!rgb_matrix_get_flags()) {
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, RGB_BLACK);
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            numlock_arrows_indicators();
            rgb_matrix_set_color(0, RGB_RED);
        break;
        case _FN1:
            rgb_matrix_set_color(0, RGB_YELLOW);
        break;
    }
    return false;
}