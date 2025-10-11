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
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif // VIA_ENABLE

#ifndef __arm__
/* Disable unused features. */
#    define NO_ACTION_ONESHOT
#endif // __arm__

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TIMEOUT 250
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

#define MOUSEKEY_DELAY            0
#define MOUSEKEY_INTERVAL         12   // lower = faster updates (default ~16)
#define MOUSEKEY_MOVE_DELTA       8    // pixels per step
#define MOUSEKEY_MAX_SPEED        12   // higher cap
#define MOUSEKEY_TIME_TO_MAX      20   // reach max speed quicker

// Wheel speed (optional)
#define MOUSEKEY_WHEEL_DELAY      0
#define MOUSEKEY_WHEEL_INTERVAL   30
#define MOUSEKEY_WHEEL_MAX_SPEED  12
#define MOUSEKEY_WHEEL_TIME_TO_MAX 20
#define MOUSEKEY_WHEEL_DELTA      2
