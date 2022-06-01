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
#include QMK_KEYBOARD_H

enum layer_names {
  _MA,
  _FN
};

enum custom_keycodes {
  KC_CUST = SAFE_RANGE,
};

#define RGB_LUT_LEN 90
#define RGB_LUT_R 0
#define RGB_LUT_G 1
#define RGB_LUT_B 2
uint8_t rgb_lut_idx = 0;
static const uint8_t rgb_lut[RGB_LUT_LEN][3] = {
    {100,0,0},
    {100,6,0},
    {100,13,0},
    {100,20,0},
    {100,26,0},
    {100,33,0},
    {100,40,0},
    {100,46,0},
    {100,53,0},
    {100,60,0},
    {100,66,0},
    {100,73,0},
    {100,80,0},
    {100,86,0},
    {100,93,0},
    {100,100,0},
    {93,100,0},
    {86,100,0},
    {80,100,0},
    {73,100,0},
    {66,100,0},
    {60,100,0},
    {53,100,0},
    {46,100,0},
    {40,100,0},
    {33,100,0},
    {26,100,0},
    {20,100,0},
    {13,100,0},
    {6,100,0},
    {0,100,0},
    {0,100,6},
    {0,100,13},
    {0,100,20},
    {0,100,26},
    {0,100,33},
    {0,100,40},
    {0,100,46},
    {0,100,53},
    {0,100,60},
    {0,100,66},
    {0,100,73},
    {0,100,80},
    {0,100,86},
    {0,100,93},
    {0,100,100},
    {0,93,100},
    {0,86,100},
    {0,80,100},
    {0,73,100},
    {0,66,100},
    {0,60,100},
    {0,53,100},
    {0,46,100},
    {0,40,100},
    {0,33,100},
    {0,26,100},
    {0,20,100},
    {0,13,100},
    {0,6,100},
    {0,0,100},
    {6,0,100},
    {13,0,100},
    {20,0,100},
    {26,0,100},
    {33,0,100},
    {40,0,100},
    {46,0,100},
    {53,0,100},
    {60,0,100},
    {66,0,100},
    {73,0,100},
    {80,0,100},
    {86,0,100},
    {93,0,100},
    {100,0,100},
    {100,0,93},
    {100,0,86},
    {100,0,80},
    {100,0,73},
    {100,0,66},
    {100,0,60},
    {100,0,53},
    {100,0,46},
    {100,0,40},
    {100,0,33},
    {100,0,26},
    {100,0,20},
    {100,0,13},
    {100,0,6},
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MA] = LAYOUT_ansi(
               _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, _______,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______,                   _______,                   _______, _______, _______, _______,          _______, _______
  ),
  [_FN] = LAYOUT_ansi(
               _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, _______,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______,                   _______,                   _______, _______, _______, _______,          _______, _______
  ),

};

// RGB config, for changing RGB settings on non-VIA firmwares
void change_RGB(bool clockwise) {
    bool shift = get_mods() & MOD_MASK_SHIFT;
    bool alt = get_mods() & MOD_MASK_ALT;
    bool ctrl = get_mods() & MOD_MASK_CTRL;

    if (clockwise) {
        if (alt) {
            rgblight_increase_hue();
        } else if (ctrl) {
            rgblight_increase_val();
        } else if (shift) {
            rgblight_increase_sat();
        } else {
            rgblight_step();
        }

  } else {
      if (alt) {
            rgblight_decrease_hue();
        } else if (ctrl) {
            rgblight_decrease_val();
        } else if (shift) {
            rgblight_decrease_sat();
        } else {
            rgblight_step_reverse();
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (layer_state_is(1)) {
    //change RGB settings
    change_RGB(clockwise);
  }
  else {
    if (clockwise) {
      tap_code(KC_VOLU);
  } else {
      tap_code(KC_VOLD);
    }
  }
    return true;
}

void matrix_scan_user(void) {
    static uint16_t pwm_timer;

    if (timer_elapsed(pwm_timer) > 50) {
        pwm_timer = timer_read();
        if (rgb_lut_idx++ >= RGB_LUT_LEN-1) rgb_lut_idx = 0;
        set_bitc_LED_rgb_pwm(rgb_lut[rgb_lut_idx][RGB_LUT_R], rgb_lut[rgb_lut_idx][RGB_LUT_G], rgb_lut[rgb_lut_idx][RGB_LUT_B]);
        // set_nibble_LED_rgb_pwm(rgb_lut[rgb_lut_idx][RGB_LUT_R], rgb_lut[rgb_lut_idx][RGB_LUT_G], rgb_lut[rgb_lut_idx][RGB_LUT_B]);
    }
}

// Use Big LED to show status
bool led_update_user(led_t led_state) {
    set_nibble_LED_r(led_state.caps_lock ? LED_ON : LED_OFF);
    set_nibble_LED_g(led_state.num_lock ? LED_DIM : LED_OFF);
    set_nibble_LED_b(led_state.scroll_lock ? LED_DIM : LED_OFF);

    // set_nibble_LED_r_pwm(led_state.caps_lock ? 10 : LED_OFF);
    // set_nibble_LED_g_pwm(led_state.num_lock ? 10 : LED_OFF);
    // set_nibble_LED_b_pwm(led_state.scroll_lock ? 10 : LED_OFF);

    set_bitc_LED_r_pwm(led_state.caps_lock ? 100 : LED_OFF);
    set_bitc_LED_g_pwm(led_state.num_lock ? 100 : LED_OFF);
    set_bitc_LED_b_pwm(led_state.scroll_lock ? 100 : LED_OFF);
    return true;
}