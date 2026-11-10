#include QMK_KEYBOARD_H

enum layers {
    BASE,
    NAV,
    SYM,
    FN,
};

// Each layout ends with the left and right encoder presses.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3_enc(
        KC_TAB,        KC_Q, KC_W, KC_E,          KC_R,    KC_T,        KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    LSFT(KC_BSLS),
        OSM(MOD_LCTL), KC_A, KC_S, KC_D,          KC_F,    KC_G,        KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        OSM(MOD_LSFT), KC_Z, KC_X, KC_C,          KC_V,    KC_B,        KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
                                   OSM(MOD_LGUI), MO(NAV), KC_SPC,      KC_ENT, MO(SYM), KC_BSPC,
        KC_A, KC_B
    ),
    [NAV] = LAYOUT_split_3x6_3_enc(
        KC_TRNS, KC_1,  KC_2,          KC_3,          KC_4,          KC_5,           KC_6,    KC_7,    KC_8,          KC_9,    KC_0,  KC_BSPC,
        KC_TRNS, KC_NO, OSM(MOD_LALT), OSM(MOD_LGUI), OSM(MOD_LSFT), CW_TOGG,        KC_LEFT, KC_DOWN, KC_UP,         KC_RGHT, KC_NO, KC_NO,
        KC_TRNS, KC_NO, LALT(KC_F),    LALT(KC_V),    LALT(KC_N),    LSA(KC_V),      KC_HOME, KC_PGDN, KC_PGUP,       KC_END,  KC_NO, KC_DEL,
                                       KC_TRNS,       KC_NO,         KC_TRNS,        KC_TRNS, MO(FN),  OSM(MOD_LALT),
        KC_A, KC_B
    ),
    [SYM] = LAYOUT_split_3x6_3_enc(
        KC_TRNS, KC_1,          KC_2,         KC_3,          KC_4,           KC_5,            KC_6,          KC_7,       KC_8,    KC_9,    KC_0,    KC_NUHS,
        KC_TRNS, LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_SCLN), LSFT_T(KC_EQL), KC_DOT,          KC_MINS,       LSFT(KC_9), KC_LBRC, KC_BSLS, KC_SCLN, KC_GRV,
        KC_TRNS, LSFT(KC_7),    LSFT(KC_4),   LSFT(KC_1),    LSFT(KC_8),     LSFT(KC_2),      LSFT(KC_MINS), LSFT(KC_0), KC_RBRC, KC_DOT,  KC_SLSH, LSFT(KC_GRV),
                                              KC_BSPC,       MO(FN),         KC_TRNS,         KC_TRNS,       KC_NO,      KC_TRNS,
        KC_A, KC_B
    ),
    [FN] = LAYOUT_split_3x6_3_enc(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,                               KC_F9,   KC_F10, KC_F11, KC_F12,
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, KC_NO,   KC_NO,       KC_PSCR, OSM(MOD_LCTL | MOD_LSFT | MOD_LGUI), KC_NO,   KC_NO,  KC_NO,  KC_NO,
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, KC_NO,   KC_NO,       KC_NO,   KC_NO,                               KC_NO,   KC_NO,  KC_NO,  KC_NO,
                                   KC_LGUI, KC_TRNS, KC_SPC,      KC_ENT,  KC_TRNS,                             KC_RALT,
        KC_A, KC_B
    ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [NAV]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [SYM]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [FN]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
