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

enum layers {
    _DEFAULT,
    _FIRST,
    _SECOND
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,   KC_I,     KC_O,     KC_P,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,   KC_K,     KC_L,    KC_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,   KC_LCTL,  KC_TAB, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                  TG(1), KC_LSFT,  KC_ENT,     KC_BSPC, KC_SPC,  KC_LALT
                             //`--------------------------'  `--------------------------'

  ),

    [_FIRST] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
       KC_1,    KC_2,    KC_3,  KC_4,    KC_5,                          KC_GRV, KC_QUOT,  KC_NUBS, KC_BSLS, KC_NUHS,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_6,    KC_7,    KC_8,  KC_9,    KC_0,                          KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_SLSH, KC_EQL, KC_MINS,  KC_LBRC, KC_RBRC,                      KC_COMM, KC_DOT, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_TRNS, _______,  _______,     _______,   KC_SPC, MO(2)
                             //`--------------------------'  `--------------------------'
  ),

    [_SECOND] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_MPRV, KC_MPLY, KC_MNXT, BL_DOWN,  BL_UP,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                       KC_HOME, KC_PGDN, KC_PGUP, RGB_HUI,  RGB_SAI,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_F11,  KC_F12, XXXXXXX, XXXXXXX, RGB_MOD,                      XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD,  RGB_SAD,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_TRNS
                             //`--------------------------'  `--------------------------'
  )
};

const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {14, 1, HSV_PURPLE},
    {1, 5, HSV_PURPLE},
    {0, 1, HSV_PURPLE},
    {27, 6, HSV_PURPLE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer1
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _FIRST));
    return state;
};
