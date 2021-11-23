        /* Copyright 2021 yunom
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LED_CTRL,
    _LAYER1
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    SCREEN_LOCK = SAFE_RANGE,
    MIC_MUTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        MIC_MUTE,        SCREEN_LOCK,
        MO(_LED_CTRL),  KC_1,    KC_COLON,     KC_A,
        MO(_LAYER1),    KC_2,    KC_SCOLON,    KC_B,
        KC_LSFT,        KC_3,    KC_QUESTION,  KC_C
    ),
    [_LED_CTRL] = LAYOUT(
        RGB_TOG,   RGB_M_R,
        _______,   RGB_M_B,     RGB_VAI,    RGB_VAD,
        RGB_M_G,   RGB_M_SW,    RGB_SAI,    RGB_SAD,
        RGB_MOD,   RGB_RMOD,    RGB_HUI,    RGB_HUD
    ),
    [_LAYER1] = LAYOUT(
        KC_MUTE,   SCREEN_LOCK,
        KC_LSFT,   KC_UP,      KC_TAB,      KC_B,
        _______,   KC_UP,    KC_RGHT,     KC_C,
        KC_LEFT,   KC_DOWN,    KC_RGHT,     KC_D
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SCREEN_LOCK:
            if (record->event.pressed) {
                register_code(KC_LGUI);   // Press and keep holding down
                tap_code(KC_L);         // Press and release
                unregister_code(KC_LGUI); // Release
            }
            break;
        case MIC_MUTE:
            if (record->event.pressed) {
                register_code(KC_LCTL);   // Press and keep holding down
                register_code(KC_LSFT);   // Press and keep holding down
                tap_code(KC_M);         // Press and release
                unregister_code(KC_LCTL); // Release
                unregister_code(KC_LSFT); // Release
            }
            break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First(left side) encoder */
        if (clockwise) {
            tap_code(KC_MFFD);
        } else {
            tap_code(KC_MRWD);
        }
    } else if (index == 1) { /* Second(right side) encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}


