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


#include QMK_KEYBOARD_H
#include "adophoxia.h"

bool tab_pressed = false; // ADD this near the beginning of keymap.c
bool ctrl_pressed = false;
bool l_shift_pressed = false;
bool r_shift_pressed = false;
bool l_alt_pressed = false;
bool r_alt_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //uint8_t mods_state = get_mods() | get_weak_mods();
    switch (keycode) {
        case KC_LCTL:
            ctrl_pressed = record->event.pressed;
            break;
        case KC_LSFT:
            l_shift_pressed = record->event.pressed;
            break;
        case KC_RSFT:
            r_shift_pressed = record->event.pressed;
            break;
        case KC_LALT:
            l_alt_pressed = record->event.pressed;
            break;
        case KC_RALT:
            r_alt_pressed = record->event.pressed;
            break;
        case KC_TAB:
            tab_pressed = record->event.pressed;
            break;
        case ENC_PRS:
            if (record->event.pressed) {
                switch(get_highest_layer(layer_state)) {
                    case WIN_BASE:
                        if (r_alt_pressed) {
                            tap_code(KC_MUTE);
                        } else {
                            tap_code(KC_MPLY);
                        }
                        break;
                    case WIN_FN:
                        soft_reset_keyboard();
                        break;
                    case WIN_MM:
                        reset_keyboard();
                        break;
                    default:
                        break;
                }
            }
            return false;
        case ENC_LFT:
            if (record->event.pressed) {
                switch(get_highest_layer(layer_state)) {
                    case WIN_BASE:
                        if (ctrl_pressed) { // If you are holding R shift, Page up/dn
                            tap_code(KC_PGDN);
                        } else if (l_alt_pressed) {  // if holding Left Alt, change media next/prev track
                            tap_code(KC_MPRV);
                        } else if (r_alt_pressed) {
                            if (tab_pressed) {
                                tap_code(KC_LEFT);
                            }
                        } else {
                            tap_code16_delay(KC_VOLD, 2);;       // Otherwise it just changes volume
                        }
                        break;
                    case WIN_MM: //RGB Control
                        if (l_shift_pressed) { // If you are holding R shift, Page up/dn
                            rgb_matrix_decrease_speed();
                        } else if (l_alt_pressed) {  // if holding Left Alt, change media next/prev track
                            rgb_matrix_step_reverse();
                        } else if (ctrl_pressed){
                            rgb_matrix_decrease_hue();
                        } else if (ctrl_pressed && l_shift_pressed) {
                            rgb_matrix_decrease_sat();
                        } else {
                            rgb_matrix_decrease_val();       // Otherwise it just changes volume
                        }
                        break;
                    default:
                        break;
                }
            }
            return false;
        case ENC_RGT:
            if (record->event.pressed) {
                switch(get_highest_layer(layer_state)) {
                    case WIN_BASE: //Default Layer
                        if (ctrl_pressed) { // If you are holding R shift, Page up/dn
                            tap_code(KC_PGUP);
                        } else if (l_alt_pressed) {  // if holding Left Alt, change media next/prev track
                            tap_code(KC_MNXT);
                        } else if (r_alt_pressed && tab_pressed) {
                            tap_code(KC_RGHT);
                        } else {
                            tap_code16_delay(KC_VOLU, 2);;       // Otherwise it just changes volume
                        }
                        break;
                    case WIN_MM: //RGB Control
                        if (l_shift_pressed) { // If you are holding R shift, Page up/dn
                            rgb_matrix_increase_speed();
                        } else if (l_alt_pressed) {  // if holding Left Alt, change media next/prev track
                            rgb_matrix_step();
                        } else if (ctrl_pressed){
                            rgb_matrix_increase_hue();
                        } else if (ctrl_pressed && l_shift_pressed) {
                            rgb_matrix_increase_sat();
                        } else {
                            rgb_matrix_increase_val();       // Otherwise it just changes volume
                        }
                        break;
                    default:
                        break;
                }
            }
            return false;
    }
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = { ENCODER_CCW_CW(ENC_LFT, ENC_RGT) },
    [WIN_FN]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_MM]   = { ENCODER_CCW_CW(ENC_LFT, ENC_RGT) },
};
#endif