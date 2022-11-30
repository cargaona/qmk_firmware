/*
Copyright 2020 Dimitris Mantzouranis
Copyright 2022 Philip Mourdjis

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
    _WINDOWS,
    _FNW,
    _MAC,
    _FNM,
    _FN2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   
/* _WINDOWS Base ISO layout
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ - │       │DEL│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │HOM│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │PUP│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │      │UP │PDN│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │CTRL│WIN │ALT │                        │CTL│FN1│FN2│LFT│DWN│RGT│
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 *      Row:        0          1          2          3        4        5        6         7        8        9          10         11         12         13         14         15        */
 [_WINDOWS] = { {   KC_GESC,   KC_1,      KC_2,      KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_BSPC,   KC_NO,     RGB_MOD    },
                {   KC_TAB,    KC_Q,      KC_W,      KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   KC_NO,     KC_NO,     KC_HOME    },
                {   KC_CAPS,   KC_A,      KC_S,      KC_D,    KC_F,    KC_G,    KC_H,     KC_J,    KC_K,    KC_L,      KC_SCLN,   KC_QUOT,   KC_NUHS,   KC_ENT,    KC_NO,     KC_PGUP    },
                {   KC_LSFT,   KC_NUBS,   KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM,   KC_DOT,    KC_SLSH,   KC_NO,     KC_RSFT,   KC_UP,     KC_PGDN    },
                {   KC_LCTL,   KC_LGUI,   KC_LALT,   KC_NO,   KC_NO,   KC_NO,   KC_SPC,   KC_NO,   KC_NO,   KC_NO,     KC_RCTRL,  MO(_FNW),  MO(_FN2),  KC_LEFT,   KC_DOWN,   KC_RGHT    }
              },
/* _FNW Settings
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ ` │BR+│BR-│   │   │VAD│VAI│PRV│PLY│NXT│MTE│VL-│VL+│       │TOG│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │   │   │   │   │   │   │   │   │INS│DEL│END│     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │   │   │   │   │   │   │NKR│   │   │   │   │      │SPI│   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │    │    │    │                        │   │FN1│FN2│VAD│SPD│VAI│
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 *      Row:        0          1          2          3        4        5        6         7        8        9          10         11         12         13         14         15        */
     [_FNW] = { {   KC_GRV,    KC_BRIU,   KC_BRID,   KC_NO,   KC_NO,   RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_NO,     KC_NO,     RGB_TOG    },
                {   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_INS,    KC_DEL,    KC_END,    KC_NO,     KC_NO,     KC_NO      },
                {   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO      },
                {   KC_TRNS,   KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    NK_ON,   KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     RGB_SPI,   KC_NO      },
                {   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_RGUI,   KC_NO,     KC_NO,     RGB_VAD,   RGB_SPD,   RGB_VAI    }
              },
/* _MAC Base ISO layout
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │       │MOD│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │HOM│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │ FN1  │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │PGU│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │      │UP │PGD│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │CTRL│ALT │MAC │                        │CTL│FN2│HOM│LFT│DWN│RGT│
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 *      Row:        0          1          2          3        4        5        6         7        8        9          10         11         12         13         14         15        */
     [_MAC] = { {   KC_GESC,   KC_1,      KC_2,      KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_BSPC,   KC_NO,     RGB_MOD    },
                {   KC_TAB,    KC_Q,      KC_W,      KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   KC_NO,     KC_NO,     KC_HOME    },
                {   KC_CAPS,   KC_A,      KC_S,      KC_D,    KC_F,    KC_G,    KC_H,     KC_J,    KC_K,    KC_L,      KC_SCLN,   KC_QUOT,   KC_NUHS,   KC_ENT,    KC_NO,     KC_PGUP    },
                {   KC_LSFT,   KC_NUBS,   KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM,   KC_DOT,    KC_SLSH,   KC_NO,     KC_RSFT,   KC_UP,     KC_PGDN    },
                {   KC_LCTL,   KC_LALT,   KC_LGUI,   KC_NO,   KC_NO,   KC_NO,   KC_SPC,   KC_NO,   KC_NO,   KC_NO,     KC_RGUI,   MO(_FNM),  MO(_FN2),  KC_LEFT,   KC_DOWN,   KC_RGHT    }
              },
/* _FNM Settings
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ ` │BR+│BR-│   │   │VAD│VAI│PRV│PLY│NXT│MTE│VL-│VL+│       │TOG│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │   │   │   │   │   │   │   │   │INS│DEL│END│     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │   │   │   │   │   │   │NKR│   │   │   │   │      │VAI│   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │    │    │    │                        │   │FN1│   │HUD│VAD│HUI│
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 *      Row:        0          1          2          3        4        5        6         7        8        9          10         11         12         13         14         15        */
     [_FNM] = { {   RGB_TOG,   KC_SLCK,   KC_PAUS,   KC_NO,   KC_NO,   RGB_VAD, RGB_VAI,  KC_MPRV, KC_MPLY, KC_MNXT,   KC_MUTE,   KC_VOLD,   KC_VOLU,   KC_NO,     KC_NO,     RGB_TOG    },
                {   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_INS,    KC_DEL,    KC_END,    KC_NO,     KC_NO,     KC_NO      },
                {   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO      },
                {   KC_TRNS,   KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    NK_ON,   KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     RGB_VAI,   KC_NO      },
                {   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_RCTRL,  KC_NO,     KC_NO,     RGB_HUD,   RGB_VAD,   RGB_HUI    }
              },
/* _FN2 MOD Keys (common to mac / win)
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ ` │ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│ RESET │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │   │   │   │   │   │   │   │   │INS│DEL│END│     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │SPI│   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │    │    │    │                        │   │   │FN2│SAD│SPD│SAI│
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 *      Row:        0          1          2          3        4        5        6         7        8        9          10         11         12         13         14         15        */
     [_FN2] = { {   KC_GRV,    KC_F1,     KC_F2,     KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,     KC_F10,    KC_F11,    KC_F12,    RESET,     KC_NO,     RGB_RMOD   },
                {   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO      },
                {   KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO      },
                {   KC_TRNS,   KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     RGB_SPI,   KC_NO      },
                {   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,     KC_RALT,   KC_NO,     KC_NO,     RGB_SAD,   RGB_SPD,   RGB_SAI    }
              }
};

bool dip_switch_update_user(uint8_t index, bool active){
    switch(index){
        case 0: // macos/windows togggle
            if(active){ //macos
                layer_off(_WINDOWS);
                layer_on(_MAC);
            }
            else{ //windows
                layer_on(_WINDOWS);
                layer_off(_MAC);
            }
        break;
    }
    return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}
