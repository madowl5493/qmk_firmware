/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance declarations
enum {
    TD_ESC_TG2,
    TD_HYPR_CAPS,
    TD_TAB_TO1
};

td_state_t cur_dance(tap_dance_state_t *state);

void hypr_finished(tap_dance_state_t *state, void *user_data);
void hypr_reset(tap_dance_state_t *state, void *user_data);

void tab_finished(tap_dance_state_t *state, void *user_data);
void tab_reset(tap_dance_state_t *state, void *user_data);

enum layers {
    _DEFAULT,
    _FIRST,
    _SECOND
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x5_3(
  //,-------------------------------------------------------------------------------------------------------------.                        ,-------------------------------------------------------------------------------------------------------------.
            KC_Q,                   KC_W,                 KC_E,                 KC_R,                 KC_T,                                          KC_Y,                  KC_U,                KC_I,                  KC_O,                  KC_P,
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
      MT(MOD_LSFT, KC_A),    MT(MOD_LCTL, KC_S),   MT(MOD_LALT, KC_D),   MT(MOD_LGUI, KC_F),           KC_G,                                          KC_H,         MT(MOD_RGUI, KC_J),     MT(MOD_LALT, KC_K),   MT(MOD_RCTL, KC_L),  MT(MOD_RSFT, KC_SCLN),
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
            KC_Z,                   KC_X,                 KC_C,                 KC_V,                 KC_B,                                          KC_N,                  KC_M,                KC_COMM,               KC_DOT,             KC_QUOT,
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
                                                                                     TD(TD_ESC_TG2), TD(TD_HYPR_CAPS),  TD(TD_TAB_TO1),     KC_ENT,  KC_SPC, KC_BSPC
                                                                                                 //`--------------------------'  `--------------------------'

  ),

    [_FIRST] = LAYOUT_split_3x5_3(
  //,-------------------------------------------------------------------------------------------------------------.                         ,-------------------------------------------------------------------------------------------------------------.
            KC_1,                   KC_2,                 KC_3,                 KC_4,                 KC_5,                                          KC_6,                  KC_7,                KC_8,                 KC_9,                KC_0,
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
      MT(MOD_LSFT, KC_GRV),        KC_LCTL,             KC_LALT,              KC_LGUI,             XXXXXXX,                                      KC_LEFT,       MT(MOD_RGUI, KC_DOWN),  MT(MOD_RALT, KC_UP), MT(MOD_RCTL, KC_RIGHT),     KC_RSFT,
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
            XXXXXXX,                XXXXXXX,             XXXXXXX,                XXXXXXX,            XXXXXXX,                                        KC_MINS,               KC_EQL,              KC_LBRC,              KC_RBRC,           KC_SLSH,
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
                                                                                                    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS
                                                                                                 //`--------------------------'  `--------------------------'
  ),

    [_SECOND] = LAYOUT_split_3x5_3(
  ///,-------------------------------------------------------------------------------------------------------------.                         ,-------------------------------------------------------------------------------------------------------------.
            KC_F1,                  KC_F2,                 KC_F3,               KC_F4,               KC_F5,                                         KC_F6,                KC_F7,                  KC_F8,              KC_F9,               KC_F10,
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
            KC_F11,                 KC_F12,              XXXXXXX,               XXXXXXX,             XXXXXXX,                                       XXXXXXX,             XXXXXXX,              XXXXXXX,              XXXXXXX,              XXXXXXX,
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
            XXXXXXX,                XXXXXXX,             XXXXXXX,               XXXXXXX,             XXXXXXX,                                       XXXXXXX,              XXXXXXX,             XXXXXXX,              XXXXXXX,               KC_NUBS,
  //|---------------------+---------------------+---------------------+---------------------+---------------------|                         |---------------------+---------------------+---------------------+---------------------+---------------------|
                                                                                                    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS
                                                                                                 //`--------------------------'  `--------------------------'
  )
};

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_WHITE},
    {27, 6, HSV_WHITE},
    {7, 6, HSV_AZURE},
    {15, 9, HSV_AZURE},
    {34, 6, HSV_AZURE},
    {43, 4, HSV_AZURE},
    {50, 1, HSV_AZURE},
    {6, 1, HSV_GOLDENROD},
    {13, 2, HSV_GOLDENROD},
    {33, 1, HSV_GOLDENROD},
    {40, 2, HSV_GOLDENROD},
    {42, 1, HSV_SPRINGGREEN},
    {47, 1, HSV_SPRINGGREEN},
    {48, 2, HSV_SPRINGGREEN}
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM first_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 2, HSV_AZURE},
    {17, 2, HSV_AZURE},
    {23, 1, HSV_AZURE},
    {36, 2, HSV_AZURE},
    {44, 2, HSV_AZURE},
    {50, 1, HSV_AZURE},
    {6, 1, HSV_CORAL},
    {11, 1, HSV_SPRINGGREEN},
    {16, 1, HSV_SPRINGGREEN},
    {19, 1, HSV_SPRINGGREEN},
    {22, 1, HSV_SPRINGGREEN},
    {34, 1, HSV_SPRINGGREEN},
    {39, 1, HSV_SPRINGGREEN},
    {42, 1, HSV_SPRINGGREEN},
    {47, 3, HSV_SPRINGGREEN},
    {35, 1, HSV_GOLD},
    {38, 1, HSV_GOLD},
    {43, 1, HSV_GOLD},
    {46, 1, HSV_GOLD},
    {7, 2, HSV_OFF},
    {12, 1, HSV_OFF},
    {15, 1, HSV_OFF},
    {20, 2, HSV_OFF}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM second_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 1, HSV_CHARTREUSE},
    {7, 2, HSV_OFF},
    {11, 2, HSV_OFF},
    {15, 2, HSV_OFF},
    {20, 2, HSV_OFF},
    {34, 2, HSV_OFF},
    {38, 2, HSV_OFF},
    {42, 2, HSV_OFF},
    {46, 2, HSV_OFF},
    {48, 2, HSV_OFF}
);

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {13, 1, HSV_GREEN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    default_layer,
    first_layer,
    second_layer,
    capslock_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULT));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FIRST));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SECOND));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);
    return true;
}

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t hyprtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t tabtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void hypr_finished(tap_dance_state_t *state, void *user_data) {
    hyprtap_state.state = cur_dance(state);
    switch (hyprtap_state.state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            add_mods(MOD_MASK_GUI | MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT);
            break;
        case TD_DOUBLE_TAP: tap_code(KC_CAPS); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        // case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        default: break;
    }
}

void hypr_reset(tap_dance_state_t *state, void *user_data) {
    switch (hyprtap_state.state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            del_mods(MOD_MASK_GUI | MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT);
            break;
        // case TD_DOUBLE_TAP: unregister_code(KC_CAPS); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    hyprtap_state.state = TD_NONE;
}

void tab_finished(tap_dance_state_t *state, void *user_data) {
    tabtap_state.state = cur_dance(state);
    switch (tabtap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_TAB);
            break;
        case TD_SINGLE_HOLD:
            layer_lock_on(1);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_TAB);
            tap_code(KC_TAB);
            break;
        default: break;
    }
}

void tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (tabtap_state.state) {
        case TD_SINGLE_HOLD:
            layer_lock_off(1);
            break;
        case TD_DOUBLE_TAP:
            layer_lock_invert(1);
            break;
        default: break;
    }
    tabtap_state.state = TD_NONE;
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Space, twice for toggle Layer 1
    [TD_ESC_TG2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_ESC, 2),
    [TD_TAB_TO1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_finished, tab_reset),
    [TD_HYPR_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, hypr_finished, hypr_reset)
};

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&delete_key_override
};
