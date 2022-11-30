/*
Copyright 2020 Dimitris Mantzouranis
Copyright 2022 tfuxu <https://github.com/tfuxu>

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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    BASE    = 0,
    FN      = 1,
    VIA1    = 2,
    VIA2    = 3
};

enum spcgear_keycodes {
    RGB_L1 = SAFE_RANGE,
    RGB_L2,
    RGB_L3,
    RGB_L4,
    RGB_L5,
    RGB_L6
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = {

        /* ANSI layout
        +--------------------------------------------------------------------------------------------+
        | ESC |    | F1 | F2 | F3 | F4 | | F5 | F6 | F7 | F8 | | F9 | F10| F11| F12|  |PSCR|SLCK|PAUS|
        +--------------------------------------------------------------------------+  +--------------+
        |  ~  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |BACKSPC |  |INS |HOME|PGUP|
        +--------------------------------------------------------------------------+  +--------------+
        |  TAB  |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] |   \  |  |DEL |END |PGDN|
        +--------------------------------------------------------------------------+  +--------------+
        | CAPSLCK  |  A |  S |  D |  F |  G |  H |  J |  K |  L | ; | ' |  RETURN  |                 |
        +--------------------------------------------------------------------------+       +----+    |
        | LSHIFT     |  Z |  X |  C |  V |  B |  N |  M | , | . |  / |   RSHIFT    |       | UP |    |
        +--------------------------------------------------------------------------+  +--------------+
        |LCTRL| GUI | LALT |            SPACE             | RALT| FN | APP | RCTRL |  |LFT |DWN |RGT |
        +--------------------------------------------------------------------------------------------+
        */

        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16      */
        {   KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_NO,    KC_PSCR,  KC_SLCK,  KC_PAUSE },
        {   KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP  },
        {   KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN  },
        {   KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,    KC_ENT,   KC_NO,    KC_NO,    KC_NO    },
        {   KC_LSFT,  KC_NO,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,    KC_RSFT,  KC_NO,    KC_UP,    KC_NO    },
        {   KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,   KC_RALT,  MO(1),    KC_APP,   KC_NO,    KC_RCTL,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_LEFT,  KC_DOWN,  KC_RIGHT }
    },

        /* FN layout
        +--------------------------------------------------------------------------------------------+
        |RESET|    |MYCM|WHOM|CALC|MSEL| |MPRV|MNXT|MPLY|MSTP| |MUTE|VOLD|VOLU|    |  |    |    |NKTG|
        +--------------------------------------------------------------------------+  +--------------+
        |     |    |    |    |    |    |    |    |    |    |    |    |HUI |        |  |M_B |MOD |    |
        +--------------------------------------------------------------------------+  +--------------+
        |       |    |    |    |    |    |    |    |    |    |    |    |    |      |  |M_R |RMOD|M_P |
        +--------------------------------------------------------------------------+  +--------------+
        |          |    |    |    |    |    |    |    |    |    |   |   |          |                 |
        +--------------------------------------------------------------------------+       +----+    |
        |            |    |    |    |    |    |    |    |   |   |    |             |       |VAI |    |
        +--------------------------------------------------------------------------+  +--------------+
        |     |GUI_TOG|     |                              |     |     |     |     |  |SPD |VAD |SPI |
        +--------------------------------------------------------------------------------------------+
        */

    [FN]   = {
        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16      */
        {   RESET,    KC_MYCM,  KC_WHOM,  KC_CALC,  KC_MSEL,  KC_MPRV,  KC_MNXT,  KC_MPLY,  KC_MSTP,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  NK_TOGG  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUI,  _______,  RGB_L1,   RGB_L2,   RGB_L3   },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_L4,   RGB_L5,   RGB_L6   },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAI,  _______  },
        {   _______,  GUI_TOG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_VAD,  RGB_SPI  }
    },

    [VIA1] = {
        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16      */
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  }
    },

    [VIA2] = {
        /*  0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16      */
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  },
        {   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______  }
    }
};

/* RGB_L* current mode keepers */
uint8_t l1 = 1; uint8_t l2 = 1; uint8_t l3 = 1; uint8_t l4 = 1; uint8_t l5 = 1; uint8_t l6 = 1;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        /* RGB_L1 to RGB_L6 keys are used to choose from 18 different RGB modes (3 modes for each key) */
        case RGB_L1:
            if(record->event.pressed) {
                switch(l1) {
                    case 1:
                        rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
                        l1++;
                        break;
                    case 2:
                        rgb_matrix_mode(RGB_MATRIX_GRADIENT_LEFT_RIGHT);
                        l1++;
                        break;
                    case 3:
                        rgb_matrix_mode(RGB_MATRIX_RAINBOW_BEACON);
                        l1 = 1;
                        break;
                }
            }
            return true;
        case RGB_L2:
            if(record->event.pressed) {
                switch(l2) {
                    case 1:
                        rgb_matrix_mode(RGB_MATRIX_MULTISPLASH);
                        l2++;
                        break;
                    case 2:
                        rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
                        l2++;
                        break;
                    case 3:
                        rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_NEXUS);
                        l2 = 1;
                        break;
                }
            }
            return true;
        case RGB_L3:
            if(record->event.pressed) {
                switch(l3) {
                    case 1:
                        rgb_matrix_mode(RGB_MATRIX_PIXEL_FRACTAL);
                        l3++;
                        break;
                    case 2:
                        rgb_matrix_mode(RGB_MATRIX_GRADIENT_LEFT_RIGHT);
                        l3++;
                        break;
                    case 3:
                        rgb_matrix_mode(RGB_MATRIX_PIXEL_RAIN);
                        l3 = 1;
                        break;
                }
            }
            return true;
        case RGB_L4:
            if(record->event.pressed) {
                switch(l4) {
                    case 1:
                        rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
                        l4++;
                        break;
                    case 2:
                        rgb_matrix_mode(RGB_MATRIX_PIXEL_FRACTAL);
                        l4++;
                        break;
                    case 3:
                        rgb_matrix_mode(RGB_MATRIX_RAINBOW_BEACON);
                        l4 = 1;
                        break;
                }
            }
            return true;
        case RGB_L5:
            if(record->event.pressed) {
                switch(l5) {
                    case 1:
                        rgb_matrix_mode(RGB_MATRIX_JELLYBEAN_RAINDROPS);
                        l5++;
                        break;
                    case 2:
                        rgb_matrix_mode(RGB_MATRIX_RAINDROPS);
                        l5++;
                        break;
                    case 3:
                        rgb_matrix_mode(RGB_MATRIX_CYCLE_UP_DOWN);
                        l5 = 1;
                        break;
                }
            }
            return true;
        case RGB_L6:
            if(record->event.pressed) {
                switch(l6) {
                    case 1:
                        rgb_matrix_mode(RGB_MATRIX_HUE_PENDULUM);
                        l6++;
                        break;
                    case 2:
                        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                        l6++;
                        break;
                    case 3:
                        rgb_matrix_mode(RGB_MATRIX_CYCLE_OUT_IN);
                        l6 = 1;
                        break;
                }
            }
            return true;
        /* GUI_TOG key will now change GUI Key lock diode input accordingly to the state of keymap_config.no_gui */
        case GUI_TOG:
            if(record->event.pressed) {
                writePin(LED_WIN_LOCK_PIN, keymap_config.no_gui);
            }
            return true;
        default:
            return true;
    }
}
