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
#include "nb_leds.h"

#if defined(MCU_RP)
void set_scramble_LED(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            set_scramble_LED_rgb_pwm(65, 100, 95);
        break;

        case LED_DIM:
            set_scramble_LED_rgb_pwm(3, 9, 3);
        break;

        default: //LED_OFF
            set_scramble_LED_rgb_pwm(0, 0, 0);
        break;
    }
}

void set_bitc_LED(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            set_bitc_LED_rgb_pwm(65, 100, 95);
        break;

        case LED_DIM:
            set_bitc_LED_rgb_pwm(3, 9, 3);
        break;

        default: //LED_OFF
            set_bitc_LED_rgb_pwm(0, 0, 0);
        break;
    }
}

void set_nibble_LED_rgb(uint8_t r_mode, uint8_t g_mode, uint8_t b_mode) {
    set_nibble_LED_r(r_mode);
    set_nibble_LED_g(g_mode);
    set_nibble_LED_b(b_mode);
}

void set_nibble_LED_r(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            set_nibble_LED_r_pwm(100);
        break;

        case LED_DIM:
            set_nibble_LED_r_pwm(20);
        break;

        default: //LED_OFF
            set_nibble_LED_r_pwm(0);
        break;
    }
}

void set_nibble_LED_g(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            set_nibble_LED_g_pwm(100);
        break;

        case LED_DIM:
            set_nibble_LED_g_pwm(20);
        break;

        default: //LED_OFF
            set_nibble_LED_g_pwm(0);
        break;
    }
}
void set_nibble_LED_b(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            set_nibble_LED_b_pwm(100);
        break;

        case LED_DIM:
            set_nibble_LED_b_pwm(20);
        break;

        default: //LED_OFF
            set_nibble_LED_b_pwm(0);
        break;
    }
}

// SCRAMBLE PWM LED configu
pwm_led_t scramble_rgb = {
    {GP18, GP19, GP20},
    {&PWMD1, &PWMD1, &PWMD2},
    {0, 1, 0},
    PWM_OUTPUT_ACTIVE_LOW,
    0
};

// NIBBLE big PWM LED config
pwm_led_t nibble_rgb = {
    {GP6, GP5, GP3},
    {&PWMD3, &PWMD2, &PWMD1},
    {0, 1, 1},
    PWM_OUTPUT_ACTIVE_HIGH,
    0
};

// Bit-C PWM LED config
pwm_led_t bit_c_rgb = {
    {GP16, GP17, GP18},
    {&PWMD0, &PWMD0, &PWMD1},
    {0, 1, 0},
    PWM_OUTPUT_ACTIVE_LOW,
    0
};

// Internal PWM init 
// only runs once per PWM LED
void _init_pwm(pwm_led_t* led) {
    if (!led->init_complete) {
        for (int i=0; i<NUM_RGB_IDX; i++) {
            palSetPadMode(PAL_PORT(led->pin[i]), PAL_PAD(led->pin[i]), PWM_PAL_MODE);

            static PWMConfig pwmCFG = {
                .frequency = PWM_PWM_COUNTER_FREQUENCY,
                .period    = PWM_PWM_PERIOD,
            };

            // Channels are always configured as active low
            // If active high is needed, pwm is inverted in _set_led_pwm()
            pwmCFG.channels[0].mode = PWM_OUTPUT_ACTIVE_LOW;
            pwmCFG.channels[1].mode = PWM_OUTPUT_ACTIVE_LOW;
            pwmStart(led->driver[i], &pwmCFG);

            // Start LEDs in the OFF state 
            uint8_t pwm = led->mode == PWM_OUTPUT_ACTIVE_HIGH ? 100 : 0;
            pwmEnableChannel(led->driver[i], led->channel[i], PWM_FRACTION_TO_WIDTH(led->driver[i], 99, pwm));
        }
        
        led->init_complete = 1;
    }
}

// Internal generic PWM setter
void _set_led_pwm(uint8_t pwm, pwm_led_t* led, uint8_t channel) {
    if (pwm > 100) pwm = 100;
    if (led->mode == PWM_OUTPUT_ACTIVE_HIGH) pwm = (100 - pwm);

    _init_pwm(led);
    pwmEnableChannel(led->driver[channel], led->channel[channel], PWM_FRACTION_TO_WIDTH(led->driver[channel], 99, pwm));
}

// SCRAMBLE
void set_scramble_LED_rgb_pwm(uint8_t r_pwm, uint8_t g_pwm, uint8_t b_pwm) {
    _set_led_pwm(r_pwm, &scramble_rgb, RED);
    _set_led_pwm(g_pwm, &scramble_rgb, GREEN);
    _set_led_pwm(b_pwm, &scramble_rgb, BLUE);
}

void set_scramble_LED_r_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &scramble_rgb, RED);
}

void set_scramble_LED_g_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &scramble_rgb, GREEN);
}

void set_scramble_LED_b_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &scramble_rgb, BLUE);
}

// NIBBLE
void set_nibble_LED_rgb_pwm(uint8_t r_pwm, uint8_t g_pwm, uint8_t b_pwm) {
    _set_led_pwm(r_pwm, &nibble_rgb, RED);
    _set_led_pwm(g_pwm, &nibble_rgb, GREEN);
    _set_led_pwm(b_pwm, &nibble_rgb, BLUE);
}

void set_nibble_LED_r_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &nibble_rgb, RED);
}

void set_nibble_LED_g_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &nibble_rgb, GREEN);
}

void set_nibble_LED_b_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &nibble_rgb, BLUE);
}

// Bit-C
void set_bitc_LED_rgb_pwm(uint8_t r_pwm, uint8_t g_pwm, uint8_t b_pwm) {
    _set_led_pwm(r_pwm, &bit_c_rgb, RED);
    _set_led_pwm(g_pwm, &bit_c_rgb, GREEN);
    _set_led_pwm(b_pwm, &bit_c_rgb, BLUE);
}

void set_bitc_LED_r_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &bit_c_rgb, RED);
}

void set_bitc_LED_g_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &bit_c_rgb, GREEN);
}

void set_bitc_LED_b_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &bit_c_rgb, BLUE);
}

#else // AVR
// Internal generic LED setter
void _set_led(uint8_t pin, uint8_t mode) {
    switch(mode) {
        case LED_ON:
            setPinOutput(pin);
            writePin(pin, 1);
        break;

        case LED_DIM:
            setPinInput(pin);
        break;

        case LED_OFF:
            setPinOutput(pin);
            writePin(pin, 0);
        break;

        default:
        break;
    }
}

// SCRAMBLE
void set_scramble_LED(uint8_t mode) {
    _set_led(SCRAMBLE_LED, mode);
}

// Bit-C
void set_bitc_LED(uint8_t mode) {
    _set_led(BITC_LED, mode);
}

// NIBBLE
void set_nibble_LED_rgb(uint8_t r_mode, uint8_t g_mode, uint8_t b_mode) {
    set_nibble_LED_r(r_mode);
    set_nibble_LED_g(g_mode);
    set_nibble_LED_b(b_mode);
}

void set_nibble_LED_r(uint8_t mode) {
    // NIBBLE LED does not support dim mode
    if (mode == LED_DIM) mode = LED_ON;
    _set_led(NIBBLE_LED_R, mode);
}

void set_nibble_LED_g(uint8_t mode) {
    if (mode == LED_DIM) mode = LED_ON;
    _set_led(NIBBLE_LED_G, mode);
}

void set_nibble_LED_b(uint8_t mode) {
    if (mode == LED_DIM) mode = LED_ON;
    _set_led(NIBBLE_LED_B, mode);
}
#endif // MCU_RP
