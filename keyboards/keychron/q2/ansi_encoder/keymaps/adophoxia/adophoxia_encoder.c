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

#ifdef ENCODER_ENABLE
    void encoder_action_volume(bool clockwise) {
        if (clockwise)
            tap_code(KC_VOLU);
        else
            tap_code(KC_VOLD);
    }

    void encoder_action_mediatrack(bool clockwise) {
        if (clockwise)
            tap_code(KC_MNXT);
        else
            tap_code(KC_MPRV);
    }

    void encoder_action_navpage(bool clockwise) {
        if (clockwise)
            tap_code16(KC_PGUP);
        else
            tap_code16(KC_PGDN);
    }
#endif // ENCODER_ENABLE

#if defined(ENCODER_ENABLE)
    bool encoder_update_user(uint8_t index, bool clockwise) {
        uint8_t mods_state = get_mods();
        if (mods_state & MOD_BIT(KC_LSFT) ) { // If you are holding R shift, Page up/dn
            unregister_mods(MOD_BIT(KC_LSFT));
            encoder_action_navpage(clockwise);
            register_mods(MOD_BIT(KC_LSFT));
        } else if (mods_state & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next/prev track
            encoder_action_mediatrack(clockwise);
        } else {
            encoder_action_volume(clockwise);       // Otherwise it just changes volume
        }
        //return true; //set to return false to counteract enabled encoder in pro.c
        return false;
    }
#endif // ENCODER_ENABLE && !ENCODER_DEFAULTACTIONS_ENABLE