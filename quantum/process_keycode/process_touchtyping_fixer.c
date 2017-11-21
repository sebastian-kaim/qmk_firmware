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
#include "action.h"
#include "action_util.h"
#include "quantum_keycodes.h"
#include "process_touchtyping_fixer.h"

// this functions checks whether a keycode is contained in an array
bool contains_keycode(uint16_t keycode, uint16_t array[], uint8_t len) {
    for(uint8_t i = 0; i < len; i++) {
        if (array[i] == keycode) {
            return true;
        }
    }

    return false;
}

uint16_t lsft_blocked[] = LEFT_SHIFT_BLOCKED;
uint16_t rsft_blocked[] = RIGHT_SHIFT_BLOCKED;


// these two helper macros detect whether a keycode is contained in the
// respective blocked arrays
#define IS_FOR_RSHFT_BLOCKED(keycode) contains_keycode(keycode, rsft_blocked, \
        sizeof(rsft_blocked)/sizeof(rsft_blocked[0]))
#define IS_FOR_LSHFT_BLOCKED(keycode) contains_keycode(keycode, lsft_blocked, \
        sizeof(lsft_blocked)/sizeof(lsft_blocked[0]))

bool process_touchtyping_fixer(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
    uint8_t shifted = mods & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));

    if (record->event.pressed && shifted) {
        // check LR bit; 0 is left, 1 is right (see action_code.h)
        bool should_be_blocked = (mods & (1<<4)) ? 
            IS_FOR_RSHFT_BLOCKED(keycode) : IS_FOR_LSHFT_BLOCKED(keycode);

        if(should_be_blocked) {
            // when this is defined the keycode is supressed instead of unshifted
#ifdef TOUCHTYPING_FIXER_SUPRESSIVE
            return false; // processed, don't do more (= do not output)
#else
            press_key_with_level_mods(keycode);
#endif
        }

    }

    return true;
}


void press_key_with_level_mods(uint16_t key) {
    const uint8_t interesting_mods = MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT) | MOD_BIT(KC_RALT);

    // Save the state
    const uint8_t real_mods = get_mods();
    const uint8_t weak_mods = get_weak_mods();
    const uint8_t macro_mods = get_macro_mods();

    uint8_t target_mods = (key >> 8) & (QK_MODS_MAX >> 8);
    // The 5th bit indicates that it's a right hand mod,
    // which needs some fixup
    if (target_mods & 0x10) {
        target_mods &= 0xF;
        target_mods <<= 4;
    }

    // Clear the mods that we are potentially going to modify,
    del_mods(interesting_mods);
    del_weak_mods(interesting_mods);
    del_macro_mods(interesting_mods);

    // Enable the mods that we need
    add_mods(target_mods & interesting_mods);

    // Press and release the key
    register_code(key & 0xFF);

    // Restore the previous state
    set_mods(real_mods);
    set_weak_mods(weak_mods);
    set_macro_mods(macro_mods);
    send_keyboard_report();
}

#endif // TOUCHTYPING_FIXER
