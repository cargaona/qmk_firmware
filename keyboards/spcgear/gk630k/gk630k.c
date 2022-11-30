/*
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

#include "gk630k.h"

void keyboard_pre_init_kb(void) {
    // Set GUI Key lock diode to output
    setPinOutput(LED_WIN_LOCK_PIN);

    keyboard_pre_init_user();
}

void suspend_power_down_kb(void) {
    // Suspend RGB matrix on S4 and S5 state
    rgb_matrix_set_suspend_state(true);

    suspend_power_down_user();
}

void housekeeping_task_kb(void) {
    // Resume RGB matrix
    rgb_matrix_set_suspend_state(false);

    housekeeping_task_user();
}
