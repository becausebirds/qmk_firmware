/* Copyright 2015-2023 Jack Humbert
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
#include "os_detection.h"

enum planck_layers { _QWERTY, _LOWER, _RAISE, _NUMBERS };
enum custom_keycodes { KC_CMD_CTRL = SAFE_RANGE, KC_NEW_TAB, KC_1Pass };
enum planck_keycodes { QWERTY = SAFE_RANGE };
enum { TD_RSFT_ENT = 0 };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NUMBERS TO(_NUMBERS)
#define KC_CAD	LALT(LCTL(KC_DEL))
#define AUDIO_INIT_DELAY

tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Shift, twice for Enter
  [TD_RSFT_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_ENT)
// Other declarations would go here, separated by commas, if you have them
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
,-----------------------------------------------------------------------------------.
| Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |SFTENT|
|------+------+------+------+------+------+------+------+------+------+------+------|
|CmdCtl| LGUI | Alt  |      | Lower|    Space    |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_1x2uC(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD(TD_RSFT_ENT),
    KC_CMD_CTRL, KC_LGUI, KC_LALT, KC_NO,  LOWER,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
,-----------------------------------------------------------------------------------.
|   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |  F7  |  F8  |  F9  |  F10 | Copy | Paste|      |      |      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
| 1Pwd |      |      |NewTab|      |    Space    |  Num |      | Mute | Vol+ | Vol+ |
`-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_1x2uC(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   LCMD(KC_T),   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  LCTL(KC_C),  LCTL(KC_V),      KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,
    KC_1Pass,   KC_NO,   KC_NO,   KC_NEW_TAB,   KC_NO,   KC_SPC,   TO(NUMBERS),   KC_NO,      KC_MUTE,    KC_VOLD,    KC_VOLU
),

/* Raise
 ,-----------------------------------------------------------------------------------.
|   -  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|RGBTog| RGB- | RGB+ |RGBMod|  Num |    Space    |      |      | Mute | Vol+ | Vol+ |
`-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_1x2uC(
    KC_MINS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PLUS,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    RGB_TOG, RGB_VAD, RGB_VAI, RGB_MOD, TO(NUMBERS), KC_SPC, KC_NO,   KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU
),

/*
,-----------------------------------------------------------------------------------.
| CAD  |      |      |      |      |      |      |      |   7  |   8  |   9  | MINS |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |   4  |   5  |   6  | PLUS |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |   1  |   2  |   3  |  =   |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      | TO 0 | TO 0 |     SPC     | TO 0 |   0  |   0  |   .  | Enter|
`-----------------------------------------------------------------------------------'
*/
[_NUMBERS] = LAYOUT_planck_1x2uC(
    KC_CAD,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_7,    KC_8,    KC_9,    KC_MINS,
    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_4,    KC_5,    KC_6,    KC_PLUS,
    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_1,    KC_2,    KC_3,    KC_EQL,
    KC_TRNS,   KC_TRNS,  KC_TRNS,  TO(0),    TO(0),    KC_SPC,   TO(0),    KC_0,     KC_0,    KC_DOT,  KC_ENT
),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CMD_CTRL:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    register_code(KC_LGUI);  // Command key on Mac
                } else if (detected_host_os() == OS_WINDOWS) {
                    register_code(KC_LCTL);  // Control key on Windows
                }
            } else {
                unregister_code(KC_LGUI);
                unregister_code(KC_LCTL);
            }
            return false;
        case KC_NEW_TAB:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    register_code(KC_LGUI);
                    tap_code(KC_T);
                    unregister_code(KC_LGUI);
                } else if (detected_host_os() == OS_WINDOWS) {
                    register_code(KC_LCTL);
                    tap_code(KC_T);
                    unregister_code(KC_LCTL);
                }
            } else {
                unregister_code(KC_LGUI);
                unregister_code(KC_LCTL);
            }
            return false;
        case KC_1Pass:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS) {
                    register_code(KC_LGUI);
                    tap_code(KC_BSLS);
                    unregister_code(KC_LGUI);
                } else if (detected_host_os() == OS_WINDOWS) {
                    register_code(KC_LCTL);
                    tap_code(KC_BSLS);
                    unregister_code(KC_LCTL);
                }
            } else {
                unregister_code(KC_LGUI);
                unregister_code(KC_LCTL);
            }
            return false;
        default:
            return true;
    }
}