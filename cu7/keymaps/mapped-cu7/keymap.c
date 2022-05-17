#include QMK_KEYBOARD_H

bool glowRed = false;
bool glowPurple = false;

enum colors {
  WHITE,
  RED,
  PURPLE
};

// Set RGB color
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_WHITE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

// Bindings
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
              KC_MUTE,
    KC_MPRV,  KC_MPLY,  KC_MNXT,
    KC_F15,   KC_F16,   KC_F17
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

void ledWhite(void) {
  rgblight_sethsv_noeeprom(HSV_WHITE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

void ledRed(void) {
  rgblight_sethsv_noeeprom(HSV_RED);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_ALTERNATING);
}

void ledPurple(void) {
  rgblight_sethsv_noeeprom(HSV_PURPLE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_ALTERNATING);
}

// Handle RGB based on button
void handle_rgb_rgb(enum colors color) {
  if (color == RED) {
    if (glowRed == true && glowPurple == true) {
      ledPurple();
      glowRed = false;
    } else if (glowRed == true && glowPurple== false) {
      ledWhite();
      glowRed = false;
    } else {
      ledRed();
      glowRed = true;
    }
  } else if (color == PURPLE) {
    if (glowPurple == true && glowRed == true) {
      ledRed();
      glowPurple = false;
    } else if (glowPurple == true && glowRed == false) {
      ledWhite();
      glowPurple = false;
    } else {
      ledPurple();
      glowPurple = true;
    }
  }
}


// Execute Macros
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode)
    {
      case KC_F15:
      case KC_F16:
        handle_rgb_rgb(RED);
        break;
      
      case KC_F17:
        handle_rgb_rgb(PURPLE);
        break;
      
      default:
        break;
    }
  }
};