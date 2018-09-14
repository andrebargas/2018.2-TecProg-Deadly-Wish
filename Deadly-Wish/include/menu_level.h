#ifndef MENU_LEVEL_H
#define MENU_LEVEL_H

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>

#include <string>
#include <memory>
#include <vector>

using std::string;
using std::vector;
using std::shared_ptr;

using ijengine::Level;
using ijengine::Canvas;
using ijengine::Texture;
using ijengine::Event;

using namespace ijengine;

#define MAX_WIDTH 16
#define MAX_HEIGHT 12

class MenuLevel : public Level, public GameEventsListener {
public:
    MenuLevel(const string& next = "");
    ~MenuLevel();
    
    bool done() const;
    string next() const;
    string audio() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    void update_position();
    bool on_event(const GameEvent& event);

private:
    bool menu_level_done;
    string menu_level_next;
    int menu_level_start;
    int menu_level_option_y_position;
    int menu_level_current_option;

    enum { 
            BASE_OPTION, 
            DEATHMATCH_OPTION, 
            CREDITS 
        };

    enum { 
            BACKGROUND, 
            POINTER 
        };

    vector< shared_ptr<Texture> > menu_level_textures;
    vector < string > menu_level_options;
};

#endif