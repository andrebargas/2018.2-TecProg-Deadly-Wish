#include "translator.h"
#include "ije02_game.h"

#include <algorithm>

bool
Translator::translate(GameEvent& to, const MouseEvent& from)
{
    to.set_timestamp(from.timestamp());
    to.set_property<double>("x", from.x());
    to.set_property<double>("y", from.y());

    if (from.state() == MouseEvent::MOTION)
        to.set_id(game_event::MOTION);
    else
        to.set_id(game_event::CLICK);

    return true;
}

bool
Translator::translate(GameEvent& to, const SystemEvent& from)
{
    if (from.action() == SystemEvent::QUIT)
    {
        to.set_timestamp(from.timestamp());
        to.set_id(game_event::QUIT);

        return true;
    }

    return false;
}

bool
Translator::translate(GameEvent& to, const KeyboardEvent& from)
{
    to.set_timestamp(from.timestamp());

    bool done = true;
    int id = 0;

    if(from.key() == KeyboardEvent::ESCAPE) {
        id = game_event::QUIT;
    }
    else if(from.key() == KeyboardEvent::RETURN) {
        id = game_event::ENTER_GAME;
    }
    else if (from.key() == KeyboardEvent::SPACE and from.state() == KeyboardEvent::PRESSED) {
        id = game_event::HEAVY_ATTACK_P1;
    }
    else if (from.key() == KeyboardEvent::Q and from.state() == KeyboardEvent::PRESSED) {
        id = game_event::HEAVY_ATTACK_P2;
    }
    else if (from.key() == KeyboardEvent::Z and from.state() == KeyboardEvent::PRESSED) {
        id = game_event::CHOOSE_CHARACTER;
    }
    else {
        done = false;
    }

    to.set_id(id);

    return done;
}

bool
Translator::translate(GameEvent& to, const JoystickEvent& from)
{
    to.set_timestamp(from.timestamp());

    bool done = true;
    int id = 0;

    // vector<unsigned> p1_moves {KeyboardEvent::LEFT, KeyboardEvent::RIGHT, KeyboardEvent::UP, KeyboardEvent::DOWN};
    // vector<unsigned> p2_moves {KeyboardEvent::A, KeyboardEvent::D, KeyboardEvent::W, KeyboardEvent::S};

    if(from.state() == JoystickEvent::BUTTON_PRESSED) {
        if(from.button() == JoystickEvent::SQUARE || from.button() == JoystickEvent::L1) {
            vector<unsigned> heavy_attack_ids {game_event::HEAVY_ATTACK_P1, game_event::HEAVY_ATTACK_P2, game_event::HEAVY_ATTACK_P3, game_event::HEAVY_ATTACK_P4};
            id = heavy_attack_ids[from.which()];
        }
        else if(from.button() == JoystickEvent::X || from.button() == JoystickEvent::R1) {
            vector<unsigned> light_attack_ids {game_event::LIGHT_ATTACK_P1, game_event::LIGHT_ATTACK_P2, game_event::LIGHT_ATTACK_P3, game_event::LIGHT_ATTACK_P4};
            id = light_attack_ids[from.which()];
        }
        else if(from.button() == JoystickEvent::CIRCLE || from.button() == JoystickEvent::R2) {
            vector<unsigned> defense_ids {game_event::DEFENSE_P1, game_event::DEFENSE_P2, game_event::DEFENSE_P3, game_event::DEFENSE_P4};
            id = defense_ids[from.which()];
        }
        else if(from.button() == JoystickEvent::TRIANGLE || from.button() == JoystickEvent::L2) {
            vector<unsigned> special_ids {game_event::SPECIAL_P1, game_event::SPECIAL_P2, game_event::SPECIAL_P3, game_event::SPECIAL_P4};
            id = special_ids[from.which()];
        }
    }
    else if(from.state() == JoystickEvent::BUTTON_RELEASED) {
        done = false;
    }
    else if(from.state() == JoystickEvent::AXIS_MOTION && (from.axis() == JoystickEvent::LEFTY || from.axis() == JoystickEvent::LEFTX)) {
        if(from.axis() == JoystickEvent::LEFTX) {
            to.set_property<string>("axis", "X");
        }
        else if(from.axis() == JoystickEvent::LEFTY) {
            to.set_property<string>("axis", "Y");
        }

        to.set_property<int>("value", from.value());

        if(from.which() == 0) {
            id = game_event::MOVEMENT_P1;
        }
        else if(from.which() == 1) {
            id = game_event::MOVEMENT_P2;
        }
        else if(from.which() == 2) {
            id = game_event::MOVEMENT_P3;
        }
        else {
            id = game_event::MOVEMENT_P4;
        }
    }
    else {
        done = false;
    }

    to.set_id(id);

    return done;
}

inline void
Translator::set_movement_properties(GameEvent& to, const KeyboardEvent& from, const vector<unsigned> &moves) {
    if(from.state() == KeyboardEvent::PRESSED) {
        to.set_property<string>("action", "start");
    }
    else if(from.state() == KeyboardEvent::RELEASED) {
        to.set_property<string>("action", "stop");
    }

    if(from.key() == moves[0]) {
        to.set_property<string>("direction", "left");
    }
    else if(from.key() == moves[1]) {
        to.set_property<string>("direction", "right");
    }
    else if(from.key() == moves[2]) {
        to.set_property<string>("direction", "up");
    }
    else {
        to.set_property<string>("direction", "down");
    }
}
