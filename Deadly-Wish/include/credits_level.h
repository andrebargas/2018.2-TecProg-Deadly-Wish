#ifndef CREDITS_LEVEL_H
#define CREDITS_LEVEL_H

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>

#include <string>
#include <memory>
#include <vector>
#include <utility>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using namespace ijengine;

#define MAX_WIDTH 16
#define MAX_HEIGHT 12

class CreditsLevel : public Level, public GameEventsListener  {
public:
    CreditsLevel(const string& next = "");
    ~CreditsLevel();

    bool done() const;
    string next() const;
    string audio() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    void set_credits_strings();
    bool on_event(const GameEvent& event);

private:
    bool m_done;
    string m_next;
    vector <string> m_credits_strings;
    int m_start;
    int m_winner_player;

    shared_ptr<Texture> m_texture;
};

#endif