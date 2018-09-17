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
    const vector < int >
      get_players_characters() const { return character_choose_level_players_characters; }
    vector < int > character_choose_level_players_characters;

    //Metodos virtual de Level
    bool done() const;
    string next() const;
    string audio() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);

    //metodo virtual de GameEvent
    bool on_event(const GameEvent& event);


private:
    bool character_choose_level_done;
    string character_choose_level_next;
    int character_choose_level_start;
    int character_choose_level_frame;
    vector<int> character_choose_level_selected_characters;
    int character_choose_level_current_player;
    int character_choose_level_number_of_players;
    vector<CharacterSelection *> character_choose_level_character_selections;
    int character_choose_level_current_player_character;

    vector< shared_ptr<Texture> > character_choose_level_textures;

};

#endif
