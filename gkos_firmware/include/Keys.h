#pragma once
#include <Arduino.h>
#include <Keyboard.h>

namespace Keys {
    const uint8_t N_MODIFIERS= 6;
    const uint8_t MODIFIERS[N_MODIFIERS] = {
        3,      // o
        5,      // native
        6,      // s
        24,     // g
        40,     // w
        48,     // k
    };
    const uint8_t ALPHA[64] = {
        0,                  // 0
        'a',
        'b',
        'o',
        'c',                // 4
        0,
        's',
        KEY_BACKSPACE,
        'd',                // 8
        KEY_UP_ARROW,
        '\'',
        'p',
        '!',                // 12
        0,
        't',
        KEY_LEFT_ARROW,
        'e',                // 16
        '-',
        KEY_LEFT_SHIFT,
        'q',
        ',',                // 20
        0,
        'u',
        0,
        'g',                // 24
        'h',
        'i',
        KEY_PAGE_UP,
        'j',                // 28
        0,
        '/',
        KEY_ESC,
        'f',                // 32
        '?',
        '.',
        'r',
        KEY_DOWN_ARROW,     // 36
        0,
        'v',
        KEY_HOME,
        'w',                // 40
        'x',
        'y',
        KEY_INSERT,
        'z',                // 44
        0,
        0,
        KEY_LEFT_CTRL,
        'k',                // 48
        'l',
        'm',
        '\\',
        'n',                // 52
        0,
        KEY_PAGE_DOWN,
        KEY_LEFT_ALT,
        ' ',                // 56
        KEY_RIGHT_ARROW,
        0,
        KEY_RETURN,
        KEY_END,            // 60
        KEY_TAB,
        KEY_DELETE,
        0,
    };
    const uint8_t ALPHA_SHIFTED[64] = {
        0,                  // 0
        'A',
        'B',
        'O',
        'C',                // 4
        0,
        'S',
        0,
        'D',                // 8
        0,
        0,
        'P',
        0,                  // 12
        0,
        'T',
        0,
        'E',                // 16
        0,
        KEY_CAPS_LOCK,
        'Q',
        0,                  // 20
        0,
        'U',
        0,
        'G',                // 24
        'H',
        'I',
        0,
        'J',                // 28
        0,
        0,
        0,
        'F',                // 32
        0,
        0,
        'R',
        0,                  // 36
        0,
        'V',
        0,
        'W',                // 40
        'X',
        'Y',
        0,
        'Z',                // 44
        0,
        0,
        0,
        'K',                // 48
        'L',
        'M',
        0,
        'N',                // 52
        0,
        0,
        0,
        0,                  // 56
        0,
        0,
        0,
        0,                  // 60
        0,
        0,
        0,
    };
}