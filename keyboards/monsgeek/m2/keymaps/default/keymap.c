/* Copyright (C) 2023 jonylee@hfd
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

// clang-format off
enum __layers {
    WIN_B,
    WIN_WASD,
    WIN_FN,
    MAC_B,
    MAC_WASD,
    MAC_FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT( /* Base */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,            KC_HOME, KC_END,  KC_PGUP, KC_PGDN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,           KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,           KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,            KC_P4,   KC_P5,   KC_P6,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,   KC_UP,  KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT,      MO(WIN_FN),             KC_LEFT, KC_DOWN,KC_RGHT,          KC_P0,   KC_PDOT),

    [WIN_WASD] = LAYOUT( /* WASD */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______, _______, _______, _______, _______, _______, _______,          _______,           _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,   KC_W,   _______, _______, _______, _______,
        _______, _______, _______,                   _______,                            _______,      MO(WIN_FN),              KC_A,   KC_S,   KC_D,    _______, _______),


    [WIN_FN] = LAYOUT( /* FN */
        _______, KC_MYCM, KC_MAIL, KC_WSCH, KC_WHOM, KC_MSEL, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______,           _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_SPDD, RM_SPDU, _______,           _______, _______, _______, _______,
        _______, _______, TG(WIN_WASD),_______,_______,_______,_______,_______, KC_INS, DF(MAC_B),KC_PSCR, _______, _______, RM_NEXT,           _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_TOGG, _______, _______,          RM_HUEU,           _______, _______, _______,
        _______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, RM_VALU,  _______, _______, _______,   _______,
        _______, GU_TOGG, _______,                   _______,                           _______,        _______,           RM_SATD, RM_VALD,  RM_SATU, _______, _______),

    [MAC_B] = LAYOUT( /* Base */
        KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL,            KC_HOME, KC_END,  KC_PGUP, KC_PGDN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,           KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,           KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,            KC_P4,   KC_P5,   KC_P6,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,  KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI,      MO(MAC_FN),           KC_LEFT,  KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT),

    [MAC_WASD] = LAYOUT( /* WASD */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______, _______, _______, _______, _______, _______, _______,          _______,           _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,   KC_W,   _______, _______, _______, _______,
        _______, _______, _______,                   _______,                            _______,      MO(MAC_FN),              KC_A,   KC_S,   KC_D,    _______, _______),

    [MAC_FN] = LAYOUT( /* FN */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,           _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_SPDD, RM_SPDU, _______,           _______, _______, _______, _______,
        _______, _______, TG(MAC_WASD),_______,_______,_______,_______,_______, KC_INS, DF(WIN_B),KC_PSCR, _______, _______, RM_NEXT,           _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_TOGG, _______, _______,          RM_HUEU,           _______, _______, _______,
        _______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, RM_VALU,  _______, _______, _______, _______,
        _______, _______, _______,                   _______,                           _______,          _______,           RM_SATD, RM_VALD,  RM_SATU, _______, _______)

};
