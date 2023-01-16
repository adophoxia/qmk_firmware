#pragma once

enum custom_keycodes {
    KC_WLCK,
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

/* Use 3 dynamic keymap layers */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

// ENCODER ACTIONS
#ifdef ENCODER_ENABLE
    void encoder_action_volume(bool clockwise);
    void encoder_action_mediatrack(bool clockwise);
    void encoder_action_navpage(bool clockwise);
#endif // ENCODER_ENABLE