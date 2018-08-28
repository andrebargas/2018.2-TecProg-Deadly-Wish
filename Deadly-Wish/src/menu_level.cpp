#include "menu_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>

using namespace std;

MenuLevel::MenuLevel(const string& next_level)
    :m_done(false), m_next(next_level), m_start(-1), m_current_option(0)
{
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/menu.ogg", 60, 10);
    m_textures.push_back(resources::get_texture("Titlecard.png"));
    m_textures.push_back(resources::get_texture("character_selection/option_selection.png"));
    event::register_listener(this);
    m_option_y_position = 13;

    m_options.push_back("Modo Bases!");
    m_options.push_back("Modo Mata-Mata!");
    m_options.push_back("Créditos");

}

MenuLevel::~MenuLevel() {
    event::unregister_listener(this);
}

bool
MenuLevel::done() const
{
    return m_done;
}

string
MenuLevel::next() const
{
    return m_next;
}

string
MenuLevel::audio() const {
    return ".";
}

void
MenuLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;
}

void
MenuLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    int option_y_pos = 5;
    canvas->clear();
    auto font = resources::get_font("Forelle.ttf", 20);
    canvas->set_font(font);

    Rectangle rect {0.0, (m_textures[POINTER]->h() / (double) 4), 9.0, 8.0};
    
    canvas->draw(m_textures[BACKGROUND].get(), 0, 0);
    canvas->draw(m_textures[POINTER].get(), rect, 100, m_option_y_position);

    for(string option : m_options) {
        canvas->draw(option, 110, option_y_pos);
        option_y_pos += 20;
    }
}

bool
MenuLevel::on_event(const GameEvent& event) {
    if(event.id() == game_event::LIGHT_ATTACK_P1) {
        if(m_current_option == DEATHMATCH_OPTION) {
            game_mode::choosen_mode = "deathmatch-mode";
        }
        else if(m_current_option == CREDITS) {
            m_next = "credits";
        }

        m_done = true;
        return true;
    }

    if(event.id() == game_event::MOVEMENT_P1) {

        string axis = event.get_property<string>("axis");
        int value = event.get_property<int>("value");

        if(axis == "X") {
            if(value > 0) {
                m_current_option = (m_current_option + 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
            else if(value < 0) {
                m_current_option = (m_current_option - 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
        }
        else if(axis == "Y") {
            if(value > 0) {
                m_current_option = (m_current_option + 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
            else if(value < 0) {
                m_current_option = (m_current_option - 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
        }
        
        if(m_current_option < 0) {
            m_current_option += 3;
        }
        update_position();
        return true;
    }
    return false;
}

void
MenuLevel::update_position()
{
    switch(m_current_option) {
        case BASE_OPTION:
            m_option_y_position = 13;
            break;

        case DEATHMATCH_OPTION:
            m_option_y_position = 33;
            break;

        case CREDITS:
            m_option_y_position = 53;
            break;

        default:
            printf("Error on update_position() menu level\n");
            break;
    }
}
