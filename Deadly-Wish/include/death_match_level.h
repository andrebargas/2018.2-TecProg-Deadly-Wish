#ifndef DEATH_MATCH_LEVEL_H
#define DEATH_MATCH_LEVEL_H

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

class DeathMatchLevel : public Level {
public:
    DeathMatchLevel(const string& next = "", vector < int > players_characters = {});
    ~DeathMatchLevel();

    enum 
    {
        INFILTRATOR,
        MAGE,
        SOLDIER,
        KNIGHT
    };

    enum 
    {
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4
    };
    
    bool done() const;
    string next() const;
    string audio() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    void set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos);
    void verify_characters();

private:
    bool death_match_level_done;
    string death_match_level_next;
    int death_match_level_start;
    bool death_match_level_has_winner;

    vector <Character* > death_match_level_characters;
    vector < int > death_match_level_players_characters;
    shared_ptr<Texture> death_match_level_texture;
    int death_match_level_map[MAX_WIDTH][MAX_HEIGHT];
    CharacterFactory death_match_level_character_factory;
};

#endif