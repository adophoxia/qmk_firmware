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

uint8_t ctrl_pressed = false;
uint8_t shift_pressed = false;
uint8_t l_alt_pressed = false;
uint8_t r_alt_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //uint8_t mods_state = get_mods() | get_weak_mods();
    switch (keycode) {
        case KC_LCTL:
            ctrl_pressed = record->event.pressed;
            break;
        case KC_RSFT:
            shift_pressed = record->event.pressed;
            break;
        case KC_LALT:
            l_alt_pressed = record->event.pressed;
            break;
        case KC_RALT:
            r_alt_pressed = record->event.pressed;
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
                    case WIN_BASE: //Default Layer
                        if (shift_pressed) { // If you are holding R shift, Page up/dn
                            tap_code(KC_PGDN);
                        } else if (l_alt_pressed) {  // if holding Left Alt, change media next/prev track
                            tap_code(KC_MPRV);
                        } else {
                            tap_code16_delay(KC_VOLD, 2);;       // Otherwise it just changes volume
                        }
                        break;
                    case WIN_MM: //RGB Control
                        if (shift_pressed) { // If you are holding R shift, Page up/dn
                            rgb_matrix_decrease_speed_noeeprom();
                        } else if (l_alt_pressed) {  // if holding Left Alt, change media next/prev track
                            rgb_matrix_step_reverse_noeeprom();
                        } else if (ctrl_pressed){
                            rgb_matrix_decrease_hue_noeeprom();
                        } else if (ctrl_pressed && shift_pressed) {
                            rgb_matrix_decrease_sat_noeeprom();
                        } else {
                            rgb_matrix_decrease_val_noeeprom();       // Otherwise it just changes volume
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
                        if (shift_pressed) { // If you are holding R shift, Page up/dn
                            tap_code(KC_PGUP);
                        } else if (l_alt_pressed) {  // if holding Left Alt, change media next/prev track
                            tap_code(KC_MNXT);
                        } else {
                            tap_code16_delay(KC_VOLU, 2);;       // Otherwise it just changes volume
                        }
                        break;
                    case WIN_MM: //RGB Control
                        if (shift_pressed) { // If you are holding R shift, Page up/dn
                            rgb_matrix_increase_speed_noeeprom();
                        } else if (l_alt_pressed) {  // if holding Left Alt, change media next/prev track
                            rgb_matrix_step_noeeprom();
                        } else if (ctrl_pressed){
                            rgb_matrix_increase_hue_noeeprom();
                        } else if (ctrl_pressed && shift_pressed) {
                            rgb_matrix_increase_sat_noeeprom();
                        } else {
                            rgb_matrix_increase_val_noeeprom();       // Otherwise it just changes volume
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