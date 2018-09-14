#include "main_level.h"
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

using std::cout;
using std::endl;

#define NUMBER_OF_BASES 4


MainLevel::MainLevel(const string& next_level, vector < int > players_characters)
    : main_level_done(false), main_level_next(next_level), main_level_start(-1),
      main_level_has_winner(false)
{
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/ingame.ogg", 30, 50);
    printf("Entrou no main leven\n");
    main_level_texture = resources::get_texture("map/Map003.jpg");

    for (int i = 0; i < MAX_WIDTH; ++i)
        for (int j = 0; j < MAX_HEIGHT; ++j)
            main_level_map[i][j] = 1;

    main_level_map[0][0] = 0;
    main_level_map[0][MAX_HEIGHT - 1] = 0;
    main_level_map[MAX_WIDTH - 1][0] = 0;
    main_level_map[MAX_WIDTH - 1][MAX_HEIGHT - 1] = 0;

    main_level_players_characters = players_characters;
    double axis_x =0.0;
    double axis_y = 0.0;
    unsigned player_id = 0;

    for(const int &current_player_character : main_level_players_characters) {

        set_players_characters_position(player_id, axis_x, axis_y);
        Character *current_character = main_level_character_factory.make_character(
                                                                    current_player_character,
                                                                     player_id, axis_x, axis_y);
        Base *current_base = new Base(player_id);
        current_character->set_base(current_base);
        main_level_bases.push_back(current_base);
        add_child(current_character);
        add_child(current_base);
        player_id++;
    }
}

MainLevel::~MainLevel() {

}

bool
MainLevel::done() const
{
    return main_level_done;
}

string
MainLevel::next() const
{
    return main_level_next;
}

string
MainLevel::audio() const {
    return ".";
}

void
MainLevel::update_self(unsigned now, unsigned)
{
    if (main_level_start == -1)
        main_level_start = now;

    if(not main_level_has_winner and now - main_level_start > 200) {
        main_level_start = now;
        verify_bases();
    }

    if(main_level_has_winner and now - main_level_start > 3200) {
        main_level_done = true;
    }
}

void
MainLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();

    canvas->draw(main_level_texture.get(), 0, 0);
}

void
MainLevel::set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos)
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

void
MainLevel::verify_bases()
{
    int dead_base_counter = 0;
    int winner_player_id = 0;

    for(int i = 0; i < NUMBER_OF_BASES; i++) {
        if(main_level_bases[i]->get_base_life() <= 0) {
            dead_base_counter++;
        }
        else {
            winner_player_id = main_level_bases[i]->get_base_player_id();
        }
    }

    if(dead_base_counter == 3) {
        main_level_has_winner = true;
        audio::stop_audio_channel(0);
        audio::play_sound_effect("res/sound/music/winning.ogg", 30, 1);
        winner::winner_player = winner_player_id;

    }

    if(dead_base_counter > 3) {
        printf("Something is wrong.... \nMore than 3 bases destroyed!\n");
    }

    //printf("Contando.....\n %d \n", count);
}
