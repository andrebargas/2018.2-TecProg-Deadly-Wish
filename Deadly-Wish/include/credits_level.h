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

    bool exit_level() const;
    string go_to_next_level() const;
    string audio() const;

protected:
    void update_self(unsigned now_moment, unsigned last_moment);
    void draw_self(Canvas *canvas, unsigned now_moment, unsigned last_moment);
    void set_credits_text();
    bool on_event(const GameEvent& event);

private:
    bool exit;
    string next_level;
    vector <string> credits_text;
    int start;
    int winner_player;

    shared_ptr<Texture> texture;
};

#endif
