#ifndef TEST_GAME_H
#define TEST_GAME_H

#include <ijengine/game.h>
#include <ijengine/engine.h>
#include <ijengine/mouse_event.h>
#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/events_translator.h>

#include "test_level_factory.h"

using namespace ijengine;

namespace ijengine
{
    namespace game_event
    {
        const unsigned MOVEMENT = GameEvent::assign_id();
        const unsigned MOTION = GameEvent::assign_id();
        const unsigned CLICK = GameEvent::assign_id();
    }
}

class TestGame {
public:
    TestGame(const string& title, int w, int h);
    ~TestGame();

    int run(const string& level_id);

private:
    class Translator : public EventsTranslator
    {

        bool
        translate(GameEvent&, const JoystickEvent&)
        {
            return false;
        }

        bool
        translate(GameEvent& to, const MouseEvent& from)
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
        translate(GameEvent& to, const SystemEvent& from)
        {
            if (from.action() == SystemEvent::QUIT)
            {
                to.set_timestamp(from.timestamp());
                to.set_id(game_event::QUIT);

                return true;
            }

            return false;
        }

        virtual bool
        translate(GameEvent& to, const KeyboardEvent& from)
        {
            to.set_timestamp(from.timestamp());

            bool done = true;
            int id = 0;

            switch (from.key()) {
            case KeyboardEvent::ESCAPE:
                id = game_event::QUIT;
                break;
    
            case KeyboardEvent::UP:
                id = game_event::MOVEMENT;
                to.set_property<string>("direction", "up");
                break;

            case KeyboardEvent::DOWN:
                id = game_event::MOVEMENT;
                to.set_property<string>("direction", "down");
                break;

            default:
                done = false;
            }

            to.set_id(id);

            return done;
        }
    };

    Game m_game;
    Engine m_engine;
    TestLevelFactory m_level_factory;
    Translator m_translator;
};

#endif
