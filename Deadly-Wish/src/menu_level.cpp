#include "menu_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>

using namespace std;

#define BASE_OPTION_Y_POSITION 13
#define DEATHMATCH_OPTION_Y_POSITION 33
#define CREDITS_OPTION_Y_POSITION 53

MenuLevel::MenuLevel(const string& next_level)
    :m_done(false), m_next(next_level), m_start(-1), m_current_option(0)
{
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/menu.ogg", 60, 10);
    menu_level_textures.push_back(resources::get_texture("Titlecard.png"));
    menu_level_textures.push_back(resources::get_texture("character_selection/option_selection.png"));
    event::register_listener(this);
    menu_level_option_y_position = 13;

    menu_level_options.push_back("Modo Bases!");
    menu_level_options.push_back("Modo Mata-Mata!");
    menu_level_options.push_back("Créditos");

}

MenuLevel::~MenuLevel() {
    event::unregister_listener(this);
}

bool
MenuLevel::done() const
{
    return menu_level_done;
}

string
MenuLevel::next() const
{
    return menu_level_next;
}

string
MenuLevel::audio() const {
    return ".";
}

void
MenuLevel::update_self(unsigned now, unsigned)
{
    if (menu_level_start == -1)
        menu_level_start = now;
}

void
MenuLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    int option_y_pos = 5;
    canvas->clear();
    auto font = resources::get_font("Forelle.ttf", 20);
    canvas->set_font(font);

    Rectangle rect {0.0, (menu_level_textures[POINTER]->h() / (double) 4), 9.0, 8.0};
    
    canvas->draw(menu_level_textures[BACKGROUND].get(), 0, 0);
    canvas->draw(menu_level_textures[POINTER].get(), rect, 100, menu_level_option_y_position);

    for(string option : menu_level_options) {
        canvas->draw(option, 110, option_y_pos);
        option_y_pos += 20;
    }
}

bool
MenuLevel::on_event(const GameEvent& event) {
    if(event.id() == game_event::LIGHT_ATTACK_P1) {
        if(menu_level_current_option == DEATHMATCH_OPTION) {
            game_mode::choosen_mode = "deathmatch-mode";
        }
        else if(menu_level_current_option == CREDITS) {
            menu_level_next = "credits";
        }

        menu_level_done = true;
        return true;
    }

    if(event.id() == game_event::MOVEMENT_P1) {

        string axis = event.get_property<string>("axis");
        int value = event.get_property<int>("value");

        if(axis == "X") {
            if(value > 0) {
                menu_level_current_option = (menu_level_current_option + 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
            else if(value < 0) {
                menu_level_current_option = (menu_level_current_option - 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
        }
        else if(axis == "Y") {
            if(value > 0) {
                menu_level_current_option = (menu_level_current_option + 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
            else if(value < 0) {
                menu_level_current_option = (menu_level_current_option - 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
        }
        
        if(menu_level_current_option < 0) {
            menu_level_current_option += 3;
        }
        update_position();
        return true;
    }
    return false;
}

void
MenuLevel::update_position()
{
    switch(menu_level_current_option) {
        case BASE_OPTION:
            menu_level_option_y_position = BASE_OPTION_Y_POSITION; // #DEFINE BASE_OPTION_Y_POSITION
            break;

        case DEATHMATCH_OPTION:
            menu_level_option_y_position = DEATHMATCH_OPTION_Y_POSITION;
            break;

        case CREDITS:
            menu_level_option_y_position = CREDITS_OPTION_Y_POSITION;
            break;

        default:
            printf("Error on update_position() menu level\n");
            break;
    }
}