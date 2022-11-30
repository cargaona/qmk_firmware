/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "config_common.h"

/* USB Device descriptor parameter */
/* VID:PID = AB16:B00B */
#define VENDOR_ID       0xAB16
#define PRODUCT_ID      0xB00B
#define DEVICE_VER      0x0001

#define MANUFACTURER    VSG
#define PRODUCT         VSG Bellatrix QMK

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7}
#define MATRIX_ROW_PINS { D11, D10, D9, D8, D7}

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define LED_MATRIX_ROWS MATRIX_ROWS
#define LED_MATRIX_ROW_CHANNELS 3
#define LED_MATRIX_ROWS_HW (LED_MATRIX_ROWS * LED_MATRIX_ROW_CHANNELS)
/*                                                       (DISABLED)  PINS for UNDERGLOW------------=V------=-V */
#define LED_MATRIX_ROW_PINS { C6, C5, C4, C9, C8, C7, C12, C11, C10, B13, C14, C13, B14, B15, D3/*, D4, D5, D6*/}

#define LED_MATRIX_COLS MATRIX_COLS
/*               (DISABLED) PINS for UNDERGLOW (LAST TwO DISABLED TO AVOID PWM CHANNEL CONFLICT-------V-----------------------V */
#define LED_MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7/*, B12, B11, B10, B9, C0, C1*/}

#define DRIVER_LED_TOTAL 72

/* RGB Matrix */
#ifdef RGB_MATRIX_ENABLE

#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_KEYPRESSES
#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_BAND_SAT
#   define ENABLE_RGB_MATRIX_BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_DUAL_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define ENABLE_RGB_MATRIX_HUE_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_PENDULUM
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_PIXEL_RAIN
#   define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define ENABLE_RGB_MATRIX_SPLASH
#   define ENABLE_RGB_MATRIX_MULTISPLASH
#   define ENABLE_RGB_MATRIX_SOLID_SPLASH
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
