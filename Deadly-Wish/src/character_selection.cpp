#include "character_selection.h"
#include "ije02_game.h"

#include <ijengine/engine.h>
#include <ijengine/canvas.h>
#include <ijengine/rectangle.h>

#include <cmath>

#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 9

using namespace std;

CharacterSelection::CharacterSelection(const string sprite_path, int base_x, 
                                       int base_y, int player_id)
    : axis_base_x(base_x), axis_base_y(base_y), m_player_id(player_id), frame(player_id), 
      start(-1), current_selection(KNIGHT) {
    m_texture = resources::get_texture(sprite_path);

    width = CHARACTER_WIDTH;
    height = CHARACTER_HEIGHT;

    chosen = false;

    event::register_listener(this);
    update_position();
}

CharacterSelection::~CharacterSelection() {
    event::unregister_listener(this);
}

void CharacterSelection::update_self(unsigned now, unsigned last) {
    if (start == -1)
        start = now;

    if (now - start > 100) {
        start += 100;
    }
}

const int DIFF_X = 43;
const int DIFF_Y = 42;

void CharacterSelection::update_position() {
    switch(current_selection) {
        case KNIGHT:
            set_x(axis_base_x);
            set_y(axis_base_y);
        break;

        case SOLDIER:
            set_x(axis_base_x + DIFF_X);
            set_y(axis_base_y);
        break;

        case MAGE:
            set_x(axis_base_x);
            set_y(axis_base_y + DIFF_Y);
        break;

        case INFILTRATOR:
            set_x(axis_base_x + DIFF_X);
            set_y(axis_base_y + DIFF_Y);
        break;

        default:
            printf("Argumento inválido no update_position() do character_selection.cpp\n");
        break;
    }
}

void CharacterSelection::draw_self(Canvas *canvas, unsigned, unsigned) {
    Rectangle rect {0.0, (m_texture->h() / (double) 4) * frame, (double) width, (double) height};
    canvas->draw(m_texture.get(), rect, x(), y());
}

bool CharacterSelection::on_event(const GameEvent &event) {
    if(((event.id() == game_event::MOVEMENT_P1 && m_player_id == 0) ||
       (event.id() == game_event::MOVEMENT_P2 && m_player_id == 1) ||
       (event.id() == game_event::MOVEMENT_P3 && m_player_id == 2) ||
       (event.id() == game_event::MOVEMENT_P4 && m_player_id == 3)) and 
       (chosen == false)) {
        string axis = event.get_property<string>("axis");
        int value = event.get_property<int>("value");

        if(axis == "X") {
            if(value > 0) {
                current_selection = (current_selection + 1) % 4;
            }
            else if(value < 0) {
                current_selection = (current_selection - 1) % 4;
            }
        }
        else if(axis == "Y") {
            if(value > 0) {
                current_selection = (current_selection - 2) % 4;
            }
            else if(value < 0) {
                current_selection = (current_selection + 2) % 4;
            }
        }
        
        if(current_selection < 0) {
            current_selection += 4;
        }
        update_position();
        return true;
    }
    else if((event.id() == game_event::LIGHT_ATTACK_P1 && m_player_id == 0) ||
            (event.id() == game_event::LIGHT_ATTACK_P2 && m_player_id == 1) ||
            (event.id() == game_event::LIGHT_ATTACK_P3 && m_player_id == 2) ||
            (event.id() == game_event::LIGHT_ATTACK_P4 && m_player_id == 3)) {
        chosen = true;
    }
    else if((event.id() == game_event::DEFENSE_P1 && m_player_id == 0) ||
            (event.id() == game_event::DEFENSE_P2 && m_player_id == 1) ||
            (event.id() == game_event::DEFENSE_P3 && m_player_id == 2) ||
            (event.id() == game_event::DEFENSE_P4 && m_player_id == 3)) {
        chosen = false;
   }
    return false;
}