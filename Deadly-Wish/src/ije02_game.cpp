#include "ije02_game.h"
#include "character.h"

#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

namespace ijengine
{
    namespace game_event
    {
        unsigned HEAVY_ATTACK_P1 = GameEvent::assign_id();
        unsigned HEAVY_ATTACK_P2 = GameEvent::assign_id();
        unsigned HEAVY_ATTACK_P3 = GameEvent::assign_id();
        unsigned HEAVY_ATTACK_P4 = GameEvent::assign_id();
        unsigned LIGHT_ATTACK_P1 = GameEvent::assign_id();
        unsigned LIGHT_ATTACK_P2 = GameEvent::assign_id();
        unsigned LIGHT_ATTACK_P3 = GameEvent::assign_id();
        unsigned LIGHT_ATTACK_P4 = GameEvent::assign_id();
        unsigned DEFENSE_P1 = GameEvent::assign_id();
        unsigned DEFENSE_P2 = GameEvent::assign_id();
        unsigned DEFENSE_P3 = GameEvent::assign_id();
        unsigned DEFENSE_P4 = GameEvent::assign_id();
        unsigned SPECIAL_P1 = GameEvent::assign_id();
        unsigned SPECIAL_P2 = GameEvent::assign_id();
        unsigned SPECIAL_P3 = GameEvent::assign_id();
        unsigned SPECIAL_P4 = GameEvent::assign_id();
        unsigned MOVEMENT_P1 = GameEvent::assign_id();
        unsigned MOVEMENT_P2 = GameEvent::assign_id();
        unsigned MOVEMENT_P3 = GameEvent::assign_id();
        unsigned MOVEMENT_P4 = GameEvent::assign_id();
        unsigned MOTION = GameEvent::assign_id();
        unsigned CLICK = GameEvent::assign_id();
        unsigned ENTER_GAME = GameEvent::assign_id();
        unsigned CHOOSE_CHARACTER = GameEvent::assign_id();
        unsigned UP = GameEvent::assign_id();
        unsigned DOWN = GameEvent::assign_id();
        unsigned LEFT = GameEvent::assign_id();
        unsigned RIGHT = GameEvent::assign_id();
    }
}


Ije02Game::Ije02Game(const string& title, int w, int h, double scale)
    : ije_game(title, w, h, scale), ije_engine(), ije_level_factory()
{
    event::register_translator(&ije_translator);

    level::register_factory(&ije_level_factory);
    resources::set_textures_dir("res/images");
    resources::set_fonts_dir("res/fonts");
    audio::set_audio_dir("res/sound");

    physics::set_collision_mode(physics::Mode::ALL_TO_ALL, nullptr);
}

Ije02Game::~Ije02Game()
{
    level::unregister_factory();
    event::unregister_translator(&ije_translator);
}

int
Ije02Game::run(const string& level_id)
{
    return ije_game.run(level_id);
}
