#ifndef CHARACTER_CHOOSE_LEVEL_h
#define CHARACTER_CHOOSE_LEVEL_h

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>
#include "character_selection.h"

#include <string>
#include <memory>
#include <vector>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using namespace ijengine;

class CharacterChooseLevel : public Level, public GameEventsListener {

public:
    CharacterChooseLevel(const string& next = "");
    ~CharacterChooseLevel();

    enum {
        BACKGROUND,
        PORTRAITS,
        ICONS
    };

    bool is_done() const;
    string get_next() const;
    string get_audio() const;
    const vector < int > get_players_characters() const { return players_characters; }
    vector < int > players_characters;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    bool on_event(const GameEvent& event);


private:
    bool done;
    string next_level;
    int start_level;
    int frame;
    vector<int> selected_characters;
    int current_player;
    int number_of_players;
    vector<CharacterSelection *> character_selections;
    int current_player_character;
    vector< shared_ptr<Texture> > textures;

};

#endif
