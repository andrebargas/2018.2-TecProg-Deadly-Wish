#ifndef IJENGINE_KEYBOARD_EVENT_H
#define IJENGINE_KEYBOARD_EVENT_H

#include "event.h"

#define KEYBOARD_EVENT_ID 0x02

#include <sstream>

using std::ostringstream;

namespace ijengine {

    class KeyboardEvent : public Event {
    public:
        typedef enum {PRESSED, RELEASED} State;

        typedef
        enum {
            BACKSPACE, TAB, CLEAR, RETURN, PAUSE, ESCAPE, SPACE, EXCLAIM,
            DOUBLE_QUOTE, HASH, DOLLAR, AMPERSAND, QUOTE, LEFT_PARENTESIS,
            RIGHT_PARENTESIS, ASTERISK, PLUS, COMMA, MINUS, PERIOD, SLASH, ZERO,
            ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, COLON, SEMICOLON,
            LESS, EQUALS, GREATER, QUESTION, AT, LEFT_BRACKET, BACKSLASH,
            RIGHT_BRACKET, CARET, UNDERSCORE, BACKQUOTE, DELETE, A, B, C, D, E, F,
            G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, LEFT,
            RIGHT, UP, DOWN, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
             } Key;

        typedef enum {NONE, SHIFT, CONTROL, ALT, CAPS} Modifier;

        KeyboardEvent(unsigned t, State s, Key k, Modifier m, bool r = false) :
            Event(t), state(s), m_key(k), m_modifier(m), m_repeated(r) {}

        State state() const { return state; }
        Key key() const { return m_key; }
        Modifier modifier() const { return m_modifier; }
        bool repeated() const { return m_repeated; }

        string serialize() const 
        {
            ostringstream os;
            os << KEYBOARD_EVENT_ID << "," << (int) state << ","
                << (int) m_key << "," << (int) m_modifier;

            return os.str();
        }

    private:
        State state;
        Key m_key;
        Modifier m_modifier;
        bool m_repeated;
    };
}

#endif
