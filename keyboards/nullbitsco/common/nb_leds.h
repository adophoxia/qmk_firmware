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

#include "quantum.h"

enum led_mode {
    LED_OFF = 0,
    LED_DIM,
    LED_ON,
    NUM_LED_MODE
};

#if defined(MCU_RP)
#include <hal.h>

enum rgb_idx {
    RED = 0,
    GREEN,
    BLUE,
    NUM_RGB_IDX
};

typedef struct pwm_led_t {
    uint32_t pin[3];
    PWMDriver* driver[3];
    uint8_t channel[3];
    uint8_t mode;
    uint8_t init_complete;
} pwm_led_t;

#define PWM_PAL_MODE (PAL_MODE_ALTERNATE_PWM | PAL_RP_PAD_DRIVE12 | PAL_RP_GPIO_OE)
#define PWM_PWM_COUNTER_FREQUENCY 1000000
#define PWM_PWM_PERIOD PWM_PWM_COUNTER_FREQUENCY / 1000

#else // AVR
// SCRAMBLE
#define SCRAMBLE_LED B2

// NIBBLE
#define NIBBLE_LED_R D7
#define NIBBLE_LED_G C6
#define NIBBLE_LED_B D0

// Bit-C
#define BITC_LED F0
#endif // MCU_RP

// Functions available on AVR and RP2040
void
    set_scramble_LED(uint8_t mode),
    set_bitc_LED(uint8_t mode),
    set_nibble_LED_rgb(uint8_t r_mode, uint8_t g_mode, uint8_t b_mode),
    set_nibble_LED_r(uint8_t mode),
    set_nibble_LED_g(uint8_t mode),
    set_nibble_LED_b(uint8_t mode);

#if defined(MCU_RP)
// RP2040 adds HW PWM control!
// PWM values are in percent, 0-100
void
    set_scramble_LED_rgb_pwm(uint8_t r_pwm, uint8_t g_pwm, uint8_t b_pwm),
    set_scramble_LED_r_pwm(uint8_t pwm),
    set_scramble_LED_g_pwm(uint8_t pwm),
    set_scramble_LED_b_pwm(uint8_t pwm),

    set_nibble_LED_rgb_pwm(uint8_t r_pwm, uint8_t g_pwm, uint8_t b_pwm),
    set_nibble_LED_r_pwm(uint8_t pwm),
    set_nibble_LED_g_pwm(uint8_t pwm),
    set_nibble_LED_b_pwm(uint8_t pwm),

    set_bitc_LED_rgb_pwm(uint8_t r_pwm, uint8_t g_pwm, uint8_t b_pwm),
    set_bitc_LED_r_pwm(uint8_t pwm),
    set_bitc_LED_g_pwm(uint8_t pwm),
    set_bitc_LED_b_pwm(uint8_t pwm);
#endif // MCU_RP
