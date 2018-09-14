#ifndef IJE02_GAME_H
#define IJE02_GAME_H

#include "translator.h"

#include <ijengine/game.h>
#include <ijengine/engine.h>
#include <ijengine/mouse_event.h>
#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/events_translator.h>
#include <ijengine/joystick_event.h>

#include "test_level_factory.h"
#include <iostream>
#include <vector>

using namespace ijengine;
using namespace std;

namespace ijengine
{
    namespace game_event
    {
        extern unsigned HEAVY_ATTACK_P1;
        extern unsigned HEAVY_ATTACK_P2;
        extern unsigned HEAVY_ATTACK_P3;
        extern unsigned HEAVY_ATTACK_P4;
        extern unsigned LIGHT_ATTACK_P1;
        extern unsigned LIGHT_ATTACK_P2;
        extern unsigned LIGHT_ATTACK_P3;
        extern unsigned LIGHT_ATTACK_P4;
        extern unsigned DEFENSE_P1;
        extern unsigned DEFENSE_P2;
        extern unsigned DEFENSE_P3;
        extern unsigned DEFENSE_P4;
        extern unsigned SPECIAL_P1;
        extern unsigned SPECIAL_P2;
        extern unsigned SPECIAL_P3;
        extern unsigned SPECIAL_P4;
        extern unsigned MOVEMENT_P1;
        extern unsigned MOVEMENT_P2;
        extern unsigned MOVEMENT_P3;
        extern unsigned MOVEMENT_P4;
        extern unsigned MOTION;
        extern unsigned CLICK;
        extern unsigned ENTER_GAME;
        extern unsigned CHOOSE_CHARACTER;
        extern unsigned UP;
        extern unsigned DOWN;
        extern unsigned LEFT;
        extern unsigned RIGHT;
    }
}

const int SCREEN_WIDTH_PROPORTION = 4;
const int SCREEN_HEIGHT_PROPORTION = 3;
const int SCREEN_BASE_SIZE = 80;

const int GAME_SCALE = 3;
const int SCREEN_WIDTH = SCREEN_WIDTH_PROPORTION * SCREEN_BASE_SIZE;
const int SCREEN_HEIGHT = SCREEN_HEIGHT_PROPORTION * SCREEN_BASE_SIZE;

const int SCREEN_SCALED_WIDTH = SCREEN_WIDTH * GAME_SCALE;
const int SCREEN_SCALED_HEIGHT = SCREEN_HEIGHT * GAME_SCALE;

class Ije02Game {
public:
    Ije02Game(const string& title, int w, int h, double scale);
    ~Ije02Game();

    int run(const string& level_id);

private:
	Game ije_game;
	Engine ije_engine;
	Translator ije_translator;
	TestLevelFactory ije_level_factory;

};

#endif
