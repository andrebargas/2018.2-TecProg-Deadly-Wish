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

#define NUMBER_OF_CHARACTERS 4

using namespace std;
using namespace ijengine;

DeathMatchLevel::DeathMatchLevel(const string& next_level, vector < int > players_characters)
    : death_match_level_done(false), death_match_level_next(next_level),
      death_match_level_start(-1), death_match_level_has_winner(false)
{
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/ingame.ogg", 30, 50);
    printf("Entrou na Death Match level!\n");
    death_match_level_texture = resources::get_texture("map/Map003.jpg");

    for (int i = 0; i < MAX_WIDTH; ++i)
        for (int j = 0; j < MAX_HEIGHT; ++j)
            death_match_level_map[i][j] = 1;

    death_match_level_map[0][0] = 0;
    death_match_level_map[0][MAX_HEIGHT - 1] = 0;
    death_match_level_map[MAX_WIDTH - 1][0] = 0;
    death_match_level_map[MAX_WIDTH - 1][MAX_HEIGHT - 1] = 0;

    death_match_level_players_characters = players_characters;
    double axis_x =0.0;
    double axis_y = 0.0;
    unsigned player_id = 0;

    for(const int &current_player_character : death_match_level_players_characters) {
        set_players_characters_position(player_id, axis_x, axis_y);
        Character *current_character = 
        death_match_level_character_factory.make_character(current_player_character,player_id,
                                                           axis_x, axis_y);
        Base *current_base = new Base(player_id);
        current_character->set_base(current_base);
        death_match_level_characters.push_back(current_character);
        current_base->set_base_status(8 - current_character->get_number_of_lives());
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
    if (death_match_level_start == -1)
        death_match_level_start = now;

    if(not death_match_level_has_winner and now - death_match_level_start > 200) {
        death_match_level_start = now;
        verify_characters();
    }

    if(death_match_level_has_winner and now - death_match_level_start > 3200) {
        death_match_level_done = true;
    }
}

void
DeathMatchLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();

    canvas->draw(death_match_level_texture.get(), 0, 0);
}

void
DeathMatchLevel::verify_characters()
{
    int player_counter = 0;
    int valid_index = 0;

    for(int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        if(death_match_level_characters[i]->valid()) {
            player_counter++;
            valid_index = i;
        }
    }

    if(player_counter == 1) {
        death_match_level_has_winner = true;
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
    return death_match_level_done;
}

string
DeathMatchLevel::next() const
{
    return death_match_level_next;
}
string
DeathMatchLevel::audio() const {
    return ".";
}