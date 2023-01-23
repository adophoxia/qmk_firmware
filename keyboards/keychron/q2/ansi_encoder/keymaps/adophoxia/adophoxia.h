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
#define CTL_GRV MT(MOD_LCTL, KC_GRV)  // Left Control when held, Grave accent when tapped `
#define ALT_GRV MT(MOD_LALT, KC_GRV)  // Left Alt when held, Grave accent when tapped ~