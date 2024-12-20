/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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
 // Timeout duration (in milliseconds)
#include "pointing_device.h"
#include "timer.h"
#define SCROLL_LOCK_TIMEOUT 5000
// Dummy
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{ KC_NO }}}

// Timer to track inactivity
static uint32_t last_movement_time = 0;

void toggle_scroll_lock(bool enable) {
    if (enable) {
        // Enable Scroll Lock
        tap_code(KC_SLCK);
    } else {
        // Disable Scroll Lock
        tap_code(KC_SLCK);
    }
}

void pointing_device_task(void) {
    report_mouse_t mouse_report = pointing_device_get_report();

    // Detect if cursor moved
    if (mouse_report.x != 0 || mouse_report.y != 0) {
        last_movement_time = timer_read();  // Update the timer
        toggle_scroll_lock(true);          // Enable Scroll Lock
    }

    // Call the default pointing device handler
    pointing_device_send();
}

void matrix_scan_user(void) {
    // Check if the timeout has elapsed
    if (timer_elapsed(last_movement_time) > SCROLL_LOCK_TIMEOUT) {
        toggle_scroll_lock(false);  // Disable Scroll Lock
    }
}


void suspend_power_down_user(void) {
    // Switch off sensor + LED making trackball unable to wake host
    adns5050_power_down();
}

void suspend_wakeup_init_user(void) {
    adns5050_init();
}
