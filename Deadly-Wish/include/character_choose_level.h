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

    bool done() const;
    string next() const;
    string audio() const;
    const vector < int > players_characters() const { return m_players_characters; }
    vector < int > m_players_characters;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    bool on_event(const GameEvent& event);


private:
    bool m_done;
    string m_next;
    int m_start;
    int frame;
    vector<int> m_selected_characters;
    int m_current_player;
    int m_number_of_players;
    vector<CharacterSelection *> m_character_selections;
    int m_current_player_character;

    vector< shared_ptr<Texture> > m_textures;

};

#endif