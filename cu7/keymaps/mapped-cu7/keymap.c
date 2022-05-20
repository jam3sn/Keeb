#include QMK_KEYBOARD_H

/**
 * Bindings
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
              KC_MUTE,
    KC_MPRV,  KC_MPLY,  KC_MNXT,
    KC_F15,   KC_F16,   KC_F17
  )
};

/**
 * Color management
 */
enum COLORS {
  WHITE,
  RED,
  PURPLE,
  COLORS_COUNT,
};

const uint8_t colorMapping[3][3] = {
  {HSV_WHITE},
  {HSV_RED},
  {HSV_PURPLE},
};

bool activeColors[COLORS_COUNT] = {true, false, false};

/**
 * Set base lighting
 * 
 * @return void
 */
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_WHITE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

/**
 * Volume up/down on the encoder
 * 
 * @param uint8_t index
 * @param bool clockwise
 * @return bool
 */
bool encoder_update_user(uint8_t index, bool clockwise) {
  tap_code_delay(clockwise ? KC_VOLU : KC_VOLD, 10);
  return true;
}

/**
 * Handle button color state
 * 
 * @param enum COLORS color - Color to toggle.
 * @return void
 */ 
void handle_rgb_rgb(enum COLORS color) {
  activeColors[color] = !activeColors[color];

  for (int i = COLORS_COUNT-1; i >= 0; i--) {
    if (activeColors[i]) {
      rgblight_sethsv_noeeprom(colorMapping[i][0], colorMapping[i][1], colorMapping[i][2]);

      (i == WHITE) ?
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT) :
        rgblight_mode_noeeprom(RGBLIGHT_MODE_ALTERNATING);

      break;
    }
  }
}

/**
 * Handle additional button functions
 * 
 * @param uint16_t keycode
 * @param keyrecord_t *record
 * @return void
 */
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
