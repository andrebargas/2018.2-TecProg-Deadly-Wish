/** /file test_level_factory.cpp
  * /brief File to class that create the levels in the game
  */
#include "main_level.h"
#include "menu_level.h"
#include "winner_level.h"
#include "death_match_level.h"
#include "credits_level.h"
#include "test_level_factory.h"
#include "character_choose_level.h"
#include "ije02_game.h"

#include <iostream>

using std::cout;

namespace ijengine
{
    namespace character_selection
    {
        vector<int> players_characters = vector<int>();
    }
    namespace winner
    {
        int winner_player = -1;
    }
    namespace game_mode
    {
        string choosen_mode = "base-mode";
    }
}

/** \fn make_level(const string& level_id)
  * \public
  * \brief Method to create a new level
  * \param level_id string& id of level to be created
  * \return Level* a pointer to the created level
  */
Level *
TestLevelFactory::make_level(const string& level_id)
{
    // For each level_id a diferente level will be created
    if (level_id == "menu"){
        return new MenuLevel("choose-character");
    }
    else if (level_id == "choose-character") {
        return new CharacterChooseLevel(game_mode::choosen_mode);
    }
    else if (level_id == "base-mode") {
        return new MainLevel("winner", character_selection::players_characters);
    }
    else if(level_id == "deathmatch-mode") {
        return new DeathMatchLevel("winner", character_selection::players_characters);
    }
    else if (level_id == "winner") {
        return new WinnerLevel("menu", winner::winner_player);
    }
    else if(level_id == "credits") {
        return new CreditsLevel("menu");
    }
    else
        cout << "Invalid value in test_level_factory";
        return nullptr;
}

/** \fn release(Level *level)
  * \public
  * \brief Method to destroy the created level
  * \param level Level* Pointer to the level that will be destroied
  * \return void
  */
void
TestLevelFactory::release(Level *level)
{
    delete level;
}
