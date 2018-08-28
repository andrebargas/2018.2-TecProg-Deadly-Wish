#include "death_match_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"
#include "util.h"
#include "test_level_factory.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace ijengine;

DeathMatchLevel::DeathMatchLevel(const string& next_level, vector < int > players_characters)
    : m_done(false), m_next(next_level), m_start(-1), m_has_winner(false)
{
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/ingame.ogg", 30, 50);
    printf("Entrou na Death Match level!\n");
    m_texture = resources::get_texture("map/Map003.jpg");

    for (int i = 0; i < MAX_W; ++i)
        for (int j = 0; j < MAX_H; ++j)
            m_map[i][j] = 1;

    m_map[0][0] = 0;
    m_map[0][MAX_H - 1] = 0;
    m_map[MAX_W - 1][0] = 0;
    m_map[MAX_W - 1][MAX_H - 1] = 0;    

    m_players_characters = players_characters;
    double x =0.0;
    double y = 0.0;
    unsigned player_id = 0;

    for(const int &current_player_character : m_players_characters) {
        set_players_characters_position(player_id, x, y);
        Character *current_character = m_character_factory.make_character(current_player_character, player_id, x, y);
        Base *current_base = new Base(player_id);
        current_character->set_base(current_base);
        m_characters.push_back(current_character);
        current_base->set_base_status(8 - current_character->number_of_lives());
        add_child(current_character);
        add_child(current_base);
        player_id++;
    }
}

DeathMatchLevel::~DeathMatchLevel()
{

}

void
DeathMatchLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;

    if(not m_has_winner and now - m_start > 200) {
        m_start = now;
        verify_characters();
    }

    if(m_has_winner and now - m_start > 3200) {
        m_done = true;
    }
}

void
DeathMatchLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();
    
    canvas->draw(m_texture.get(), 0, 0);
}

void 
DeathMatchLevel::verify_characters()
{
    int count = 0;
    int valid_index = 0;

    for(int i = 0; i < 4; i++) {
        if(m_characters[i]->valid()) {
            count++;
            valid_index = i;
        }
    }

    if(count == 1) {
        m_has_winner = true;
        audio::stop_audio_channel(0);
        audio::play_sound_effect("res/sound/music/winning.ogg", 30, 1);
        printf("Index valido: %d\n", valid_index);
        winner::winner_player = valid_index;

    }

    //printf("Contando.....\n %d \n", count);
}

void
DeathMatchLevel::set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos)
{
    switch(player_id) {
        case PLAYER_1:
            x_pos = X_ADJUSTMENT;
            y_pos = Y_ADJUSTMENT;
            break;

        case PLAYER_2:
            x_pos = (double) SCREEN_WIDTH - 32.0 - X_ADJUSTMENT;
            y_pos = Y_ADJUSTMENT;
            break;

        case PLAYER_3:
            x_pos = X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - 32.0 - Y_ADJUSTMENT;
            break;

        case PLAYER_4:
            x_pos = (double) SCREEN_WIDTH - 32.0 - X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - 32.0 - Y_ADJUSTMENT;
            break;

        default:
            printf("Valor errado no set_base_position_position!\n");
            printf("player_id: %d", player_id);
            break;
    }
}



bool
DeathMatchLevel::done() const
{
    return m_done;
}

string
DeathMatchLevel::next() const
{
    return m_next;
}
string
DeathMatchLevel::audio() const {
    return ".";
}
