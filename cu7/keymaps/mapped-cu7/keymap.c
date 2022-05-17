/*
Copyright 2021 CapsUnlocked

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

bool muted = false;

// Set RGB color
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_WHITE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

// Macro keys
enum macros {
  M_DEAFEN,
  M_MUTE,
  M_CALL,
};

// Bindings
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
              KC_MUTE,
    KC_MPRV,  KC_MPLY, KC_MNXT,
    // M_DEAFEN, M_MUTE,  M_CALL
    KC_F15, KC_F16,  KC_F17
  )
};

// Volume up/down on the encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    tap_code_delay(KC_VOLU, 10);
  }
  else {
    tap_code_delay(KC_VOLD, 10);
  }

  return true;
}

// Change RGB to red when muted
void handle_mute_rgb(void) {
  if (muted) {
    rgblight_sethsv_noeeprom(HSV_WHITE);
    muted = false;
  } else {
    rgblight_sethsv_noeeprom(HSV_RED);
    muted = true;
  }
}

// Execute Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_DEAFEN:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT("d")));
        handle_mute_rgb();
      }
      break;
    case M_MUTE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT("m")));
        handle_mute_rgb();
      }
      break;
    case M_CALL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT(SS_LALT("v"))));
      }
      break;
  }
  return true;
};