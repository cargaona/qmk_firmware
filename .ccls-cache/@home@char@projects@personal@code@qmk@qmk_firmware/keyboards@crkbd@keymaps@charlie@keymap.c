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
#include <stdio.h>

enum crkbd_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
  _MOUSE, 
};

enum {
  TD_P_BSPC = 0,
  CT_CLN
};

#define MOD_MASK_LALT MOD_BIT(KC_LALT)
#define LT_LWESC LT(_LOWER, KC_ESC)
#define LT_LWTAB LT(_LOWER, KC_TAB)
#define LT_RABSPC LT(_RAISE, KC_BSPC)


const uint16_t PROGMEM OP_BSPC_COMBO[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM OP_ESC_COMBO[] = {KC_Q, KC_W, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
//    COMBO(OP_BSPC_COMBO, KC_BSPC),
    COMBO(OP_ESC_COMBO, KC_ESC),
};


// Use left alt + upper row as symbols to avoid layer + shift + key to get the symbol. 
const key_override_t exclamation_key_override = ko_make_basic(MOD_MASK_LALT, KC_Q, KC_EXLM);
const key_override_t at_key_override = ko_make_basic(MOD_MASK_LALT, KC_W, KC_AT);
const key_override_t hash_key_override = ko_make_basic(MOD_MASK_LALT, KC_E, KC_HASH);
const key_override_t dollar_key_override = ko_make_basic(MOD_MASK_LALT, KC_R, KC_DLR);
const key_override_t percent_key_override = ko_make_basic(MOD_MASK_LALT, KC_T, KC_PERC);
const key_override_t circumflex_key_override = ko_make_basic(MOD_MASK_LALT, KC_Y, KC_CIRC);
const key_override_t ampersand_key_override = ko_make_basic(MOD_MASK_LALT, KC_U, KC_AMPR);
const key_override_t asterisk_key_override = ko_make_basic(MOD_MASK_LALT, KC_I, KC_ASTR);
const key_override_t left_parenthesis_key_override = ko_make_basic(MOD_MASK_LALT, KC_O, KC_LPRN);
const key_override_t right_parethesis_override = ko_make_basic(MOD_MASK_LALT, KC_P, KC_RPRN);
const key_override_t question_mark_override = ko_make_basic(MOD_MASK_LALT, KC_SLSH, KC_QUES);

const key_override_t back_browser_key_override = ko_make_basic(MOD_MASK_LALT, KC_BSPC, LALT(KC_LEFT));
const key_override_t ctrl_tab_key_override = ko_make_basic(MOD_MASK_LALT, KC_N, LCTL(KC_TAB));

const key_override_t **key_overrides = (const key_override_t *[]){
  	&exclamation_key_override,
  	&at_key_override, 
	&hash_key_override, 
	&dollar_key_override, 
	&percent_key_override, 
	&circumflex_key_override, 
	&ampersand_key_override, 
	&asterisk_key_override , 
	&left_parenthesis_key_override, 
	&right_parethesis_override, 
    &question_mark_override,

	&back_browser_key_override, 

    NULL // Null terminate the array of overrides!
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(             
      QK_GESC,          KC_Q,             KC_W,         KC_E,        KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
      LSFT_T(KC_TAB),   LSFT_T(KC_A),     KC_S,         KC_D,        KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,   TD(CT_CLN),       KC_QUOT,
      KC_LCTL,          LCTL_T(KC_Z),     KC_X,         KC_C,        KC_V,    KC_B,                       KC_N,    KC_M,    KC_COMM, KC_DOT, RSFT_T(KC_SLSH),  RSFT_T(KC_ENT),
                                LALT_T(KC_ESC),   LT_LWTAB,     MT(MOD_LGUI, KC_ENT),                     KC_SPC,  MO(_RAISE), RALT_T(KC_GRV)                      
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_BSPC,  _______,
      _______, KC_LSFT, _______, _______, _______, _______,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_QUOT, KC_DEL,
      _______, _______, _______, _______, _______, _______,                      KC_PGUP, KC_HOME, KC_PGDN, KC_END,   KC_PIPE, _______, 
                                          _______, _______,  _______,            _______, MO(_ADJUST) , _______
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, KC_LSFT, _______, _______, _______, _______,                     KC_EQL,  KC_MINS, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
      _______, LCTL(KC_Z), _______, _______, _______, _______,                     KC_PLUS, KC_UNDS, KC_LCBR, KC_RCBR, _______ , _______,
                                          _______, MO(_ADJUST), _______,        _______, _______, _______
  ),
  
  [_ADJUST] = LAYOUT_split_3x6_3(
      QK_BOOT, KC_F10,  KC_F11,  KC_F12, _______, _______,                      _______, KC_BRIU, KC_VOLU, KC_MPLY, KC_PSCR, _______, 
      _______, LCTL(KC_Z), _______, _______, _______, _______,                   _______, KC_BRID, KC_VOLD, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                  TG(_NUMPAD), TG(_MOUSE), KC_MUTE, _______, _______, _______,
                                          _______, _______,  _______,            _______, _______, _______
  ),

  [_NUMPAD] = LAYOUT_split_3x6_3(
      TG(_NUMPAD), TG(_NUMPAD), _______, _______, _______, _______,                      _______ , KC_SLSH, KC_7 , KC_8 , KC_9,  _______,
      _______,     _______, _______, _______, _______, _______,                      KC_PLUS , KC_ASTR, KC_4 , KC_5 , KC_6,  _______,
      _______,     _______, _______, _______, _______, _______,                      KC_MINS , KC_EQL,  KC_1 , KC_2 , KC_3,  _______,
                                              _______, _______, _______,           KC_COMM , KC_DOT , KC_0
  ), 
  [_MOUSE] = LAYOUT_split_3x6_3(
      TG(_MOUSE), TG(_MOUSE),  _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
      _______,   _______, _______, _______, _______, _______,                      KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
      _______,   _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,             KC_BTN1, _______, _______
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_A):
            return TAPPING_TERM + LONG_TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
} 

// TAP DANCE FUNCTIONS
void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  } else {
    register_code (KC_SCLN);
  }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_SCLN);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
};
