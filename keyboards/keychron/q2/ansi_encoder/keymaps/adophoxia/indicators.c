/* Copyright 2023 @Adophoxia

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
#include "indicators.h"
#include "lib/lib8tion/lib8tion.h"

#define ARRAYSIZE(arr) sizeof(arr)/sizeof(arr[0])

uint8_t alphabets[] = {
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    31, 32, 33, 34, 35, 36, 37, 38, 39,
    45, 46, 47, 48, 49, 50, 51,
};

uint8_t alphas[] = {
    26, 27, 28,
    40, 41,
    52, 53, 54,
};

uint8_t multimedia_f_row[] = {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
};

void breathing_win_lock(){
    HSV      hsv  = {HSV_RED};
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    RGB rgb       = hsv_to_rgb(hsv);
    if (keymap_config.no_gui){ // Sets a breathing LED effect on Win Key
        rgb_matrix_set_color(58, rgb.r, rgb.g, rgb.b);
    }
};

void breathing_caps_lock(){
    HSV      hsv  = {HSV_WHITE};
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    RGB rgb       = hsv_to_rgb(hsv);
    if (host_keyboard_led_state().caps_lock) { // Sets a breathing LED effect on caps locks and KC_A - KC_Z
        for (uint8_t i = 0; i < ARRAYSIZE(alphabets); i++){
            rgb_matrix_set_color(alphabets[i], rgb.r, rgb.g, rgb.b);
        } 
        rgb_matrix_set_color(30, RGB_WHITE);
    }
};

// Lights up certain areas of the keyboard when L_SFT/R_SFT is held
void shift_indicators(){
    if (get_mods() & MOD_BIT(KC_LSFT)){
        uint8_t i;
        for (i = 0; i < ARRAYSIZE(alphabets); i++){ // Lights up KC_A - KC_Z as PINK
            rgb_matrix_set_color(alphabets[i], RGB_PINK);
        }
        for (i = 0; i < ARRAYSIZE(multimedia_f_row); i++){ // Lights up KC_1 - KC_EQL as CYAN
            if (get_highest_layer(layer_state) == WIN_FN){ // Switches CYAN to RED if either SFT is press while in _FN3 
                rgb_matrix_set_color(multimedia_f_row[i], RGB_RED);
            } else { // "break;" for color switch
            rgb_matrix_set_color(multimedia_f_row[i], RGB_CYAN);
            }
        }
        for (uint8_t i = 0; i < ARRAYSIZE(alphas); i++){ // Lights up keys like [], ;, ', etc., as GREEN
            rgb_matrix_set_color(alphas[i], RGB_GREEN);
        } 
    }
};

bool mediatrack_navpage_indicators(void) {
    if (get_mods() & MOD_BIT(KC_LALT)){
        rgb_matrix_set_color(64, RGB_WHITE);
        rgb_matrix_set_color(66, RGB_WHITE);
    } else if (get_mods() & MOD_BIT(KC_LSFT)) {
        rgb_matrix_set_color(56, RGB_RED);
        rgb_matrix_set_color(65, RGB_RED);
    }
    return false;
}



bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer > 0) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                uint8_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});

                if (index >= led_min && index < led_max && index != NO_LED &&
                keycode > KC_TRNS) {
                    switch(get_highest_layer(layer_state|default_layer_state)) {
                        case WIN_MM:
                            rgb_matrix_set_color(index, RGB_BLUE);
                            break;
                        case WIN_FN:
                            if (keycode <= KC_1 && keycode >= KC_0 && keycode == KC_MINS && keycode == KC_EQL) {
                                rgb_matrix_set_color(index, RGB_RED);
                            }
                            rgb_matrix_set_color(index, RGB_YELLOW);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    if (layer == WIN_BASE){ // Checks if layers are either `MAC_BASE` or `WIN_BASE`
        breathing_caps_lock();
        shift_indicators();
        breathing_win_lock();
    }
    mediatrack_navpage_indicators();
    return false;
}