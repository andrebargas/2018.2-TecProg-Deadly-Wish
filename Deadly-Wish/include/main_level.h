#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

#include "character_factory.h"
#include "base.h"

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>

#include <string>
#include <memory>
#include <vector>
#include <utility>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using ijengine::Level;
using ijengine::Canvas;
using ijengine::Texture;
using ijengine::Event;

#define MAX_WIDTH 16
#define MAX_HEIGHT 12


// Level is from ijengine
class MainLevel : public Level {
public:
    MainLevel(const string& next = "", vector < int > players_characters = {});
    ~MainLevel();

    enum {
        INFILTRATOR,
        MAGE,
        SOLDIER,
        KNIGHT
    };

    enum {
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4
    };

    // nao mexer
    bool done() const;
    string next() const;
    string audio() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    void set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos);
    void verify_bases();

private:
    bool main_level_done;
    string main_level_next;
    int main_level_start;
    bool main_level_has_winner;

    vector <Base* > main_level_bases;
    vector < int > main_level_players_characters;
    shared_ptr<Texture> main_level_texture;
    int main_level_map[MAX_WIDTH][MAX_HEIGHT];
    CharacterFactory main_level_character_factory;
};

#endif
