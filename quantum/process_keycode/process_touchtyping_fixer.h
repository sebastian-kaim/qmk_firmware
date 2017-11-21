/* Copyright 2017 Sebastian Kaim
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
#ifdef TOUCHTYPING_FIXER
#ifndef TOUCHTYPING_FIXER_H
#define TOUCHTYPING_FIXER_H

#include "keycode.h"

bool contains_keycode(uint16_t keycode, uint16_t array[], uint8_t len);
bool process_touchtyping_fixer(uint16_t keycode, keyrecord_t *record);
void press_key_with_level_mods(uint16_t key);

/*
 * The list of keycodes blocked for each shift. KC_Y is omitted since you can
 * use both shifts for this key.
 *
 * You can easily overwrite this in your config.h by defining LEFT_SHIFT_BLOCKED
 * and/or RIGHT_SHIFT_BLOCKED.
 */

#ifndef LEFT_SHIFT_BLOCKED
#define LEFT_SHIFT_BLOCKED { \
KC_Q, KC_W, KC_E, KC_R, KC_T, \
KC_A, KC_S, KC_D, KC_F, KC_G, \
KC_Z, KC_X, KC_C, KC_V, KC_B, \
}
#endif

#ifndef RIGHT_SHIFT_BLOCKED
#define RIGHT_SHIFT_BLOCKED { \
KC_U, KC_I, KC_O, KC_P, \
KC_H, KC_J, KC_K, KC_L, \
KC_N, KC_M \
}
#endif

#endif // TOUCHTYPING_FIXER_H
#endif // TOUCHTYPING_FIXER
