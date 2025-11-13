/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifdef TAP_DANCE_ENABLE
#    include "process_tap_dance.h"
#endif

#ifdef TAP_DANCE_ENABLE
enum {
    TD_C = 0,
    TD_V,
    TD_K
};
#endif

#define SCREENSAVE_DELAY 120000  //configure how long to wait after last activity. 120000ms = 2 mins

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_SYMBOL,
    LAYER_NAV,
    LAYER_POINTER
};

enum my_keycodes {
  SS_ARRW = SAFE_RANGE,
  SS_FUNC,
  SS_PIPE,
  SS_PASS,
  NO_SLEEP
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define MT_Z LCTL_T(KC_Z)
#define MT_X LALT_T(KC_X)
#define MT_TAB LGUI_T(KC_TAB)
#define MT_MCTL LSFT_T(KC_MCTL)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
#define PT_BSPC LT(LAYER_SYMBOL, KC_BSPC)
#define PT_DEL LT(LAYER_NAV, KC_DEL)
#define MOUSE MO(LAYER_POINTER)

#define OPT_L A(KC_LEFT) // MOVE CURSOR TO BEGINNING OF WORD
#define OPT_R A(KC_RIGHT) // MOVE CURSOR TO END OF WORD
#define KC_LSTR G(KC_LEFT) // MOVE CURSOR TO START OF LINE
#define KC_LEND G(KC_RIGHT) // MOVE CURSOR TO END OF LINE
#define KC_CPDN LSA(KC_DOWN) // COPY LINE DOWN
#define KC_TERM C(KC_GRV) // OPEN VS CODE TERMINAL
#define KC_CNSL LAG(KC_K) // OPEN FIREFOX TERMINAL
#define KC_SALL C(S(KC_L)) // SELECT ALL INSTANCES OF SELECTION
#define KC_RELD LSG(KC_R) // HARD REFRESH IN BROWSER
#define KC_RCST A(KC_SPC)
#define KC_SEND G(KC_ENT)

#define TAP_C TD(TD_C)
#define TAP_V TD(TD_V)
#define TAP_K TD(TD_K)


#define KC_BNAV G(KC_LBRC)
#define KC_FNAV G(KC_RBRC)
#define WIN_TOG G(KC_TAB)
#define CMD_CLK G(KC_BTN1)
#define ALT_CLK A(KC_BTN1)


#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,   TAP_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         MOUSE,    MT_Z,    MT_X,   TAP_C,   TAP_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_MCTL,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  PT_BSPC,  PT_DEL,  MT_TAB,      KC_ENT,  KC_SPC,
                                           MS_BTN1, DRGSCRL,      MT_MCTL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_SYMBOL] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX,  KC_GRV,   OPT_L,   KC_UP,   OPT_R, KC_RELD,    KC_LPRN, KC_RPRN, KC_EXLM, SS_ARRW, SS_FUNC, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LSTR, KC_LEFT, KC_DOWN, KC_RGHT, KC_LEND,    KC_LBRC, KC_RBRC, KC_MINS,  KC_EQL, SS_PIPE, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, KC_SALL, KC_CPDN,  KC_TERM, KC_CNSL,   KC_SCLN, KC_QUOT, KC_LABK, KC_RABK, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    KC_SEND, KC_RCST,
                                           _______, XXXXXXX,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NAV] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_WBAK, WIN_TOG, KC_WFWD, XXXXXXX,    XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       SS_PASS, XXXXXXX, KC_BNAV, XXXXXXX, KC_FNAV, XXXXXXX,    XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,    _______,    KC_0,
                                           _______, _______,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, ALT_CLK, CMD_CLK, DPI_MOD, S_D_MOD,    XXXXXXX, XXXXXXX,   MS_UP, XXXXXXX, XXXXXXX, NO_SLEEP,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, DRGSCRL, MS_BTN4, MS_BTN3, MS_BTN1, MS_BTN2,    XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, SNIPING, XXXXXXX, XXXXXXX,    MS_WHLL, MS_WHLR, XXXXXXX, XXXXXXX, _______, AC_TOGG,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN3, KC_BTN1, KC_BTN2,    MS_WHLU, XXXXXXX,
                                           CMD_CLK, ALT_CLK,    MS_WHLD
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                        \
    {                                                                               \
        .fn        = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
        .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),               \
    }

tap_dance_action_t tap_dance_actions[] = {
    [TD_C] = ACTION_TAP_DANCE_TAP_HOLD(KC_C, LGUI(KC_C)),
    [TD_V] = ACTION_TAP_DANCE_TAP_HOLD(KC_V, LGUI(KC_V)),
    [TD_K] = ACTION_TAP_DANCE_TAP_HOLD(KC_K, LGUI(KC_K)),

};


bool stop_screensaver = false;     //screensaver mode status
uint32_t last_activity_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  tap_dance_action_t *action;

  if (record->event.pressed)
    stop_screensaver = false;  //turn off screensaver mode on any keypress

  switch (keycode) {
    case SS_ARRW:
      if (record->event.pressed) {
        SEND_STRING("=>");
      };
      return false; // Skip all further processing of this key
    case SS_FUNC:
      if (record->event.pressed) {
        SEND_STRING("()=>{}");
      }
      return false; //
    case SS_PIPE:
      if (record->event.pressed) {
        SEND_STRING("||");
      }
      return false; //
    case SS_PASS:
      if (record->event.pressed) {
        SEND_STRING("d!os.apate.minor9");
      }
      return false; //
    case TD(TD_C): // list all tap dance keycodes with tap-hold configurations
      action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
      if (!record->event.pressed && action->state.count && !action->state.finished) {
          tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
          tap_code16(tap_hold->tap);
      }
      return true;
    case TD(TD_V): // list all tap dance keycodes with tap-hold configurations
      action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
      if (!record->event.pressed && action->state.count && !action->state.finished) {
          tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
          tap_code16(tap_hold->tap);
      }
      return true;
    case TD(TD_K): // list all tap dance keycodes with tap-hold configurations
      action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
      if (!record->event.pressed && action->state.count && !action->state.finished) {
          tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
          tap_code16(tap_hold->tap);
      }
      return true;
    case NO_SLEEP:
            if (record->event.pressed) {               //if NO_SLEEP is pressed
                stop_screensaver = true;               //turn on screensaver mode
                last_activity_timer = timer_read32();  //reset timer
            }
            break;
    default:
      return true; // Process all other keycodes normally
  }
  return true;
}

void matrix_scan_user(void) {
    if (stop_screensaver) {                                             //if screensaver mode is active
        if (timer_elapsed32(last_activity_timer) > SCREENSAVE_DELAY) {  //and no key has been pressed in more than SCREENSAVE_DELAY ms
            tap_code16(KC_F13);                                         //  tap F13
            last_activity_timer = timer_read32();                       //  reset last_activity_timer
        }
    }
}
