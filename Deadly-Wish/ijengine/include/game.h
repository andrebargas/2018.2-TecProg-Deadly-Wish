#ifndef IJENGINE_GAME_H
#define IJENGINE_GAME_H

#include <string>
#include "game_events_listener.h"

using std::string;

namespace ijengine {

    class Level;

    class Game : public GameEventsListener {
    public:
        Game(const string& title, int w = 800, int h = 600, double scale = 1.0);
        ~Game();

        int run(const string& level_id);

        bool on_event(const GameEvent& event);

    private:
        typedef enum { PAUSED, RUNNING, QUIT } State;

        string m_title;
        int m_w, m_h;
        double m_scale;
        State state;
    };

}

#endif
