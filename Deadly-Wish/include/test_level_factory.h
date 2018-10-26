/** /file test_level_factory.cpp
  * /brief File to class that create the levels in the game
  */
#ifndef TEST_LEVEL_FACTORY_H
#define TEST_LEVEL_FACTORY_H

// Import of parent class
#include <ijengine/level_factory.h>

#include <vector>

using std::vector;

using namespace ijengine;

namespace ijengine
{
    namespace character_selection
    {
        extern vector<int> players_characters;
    }
    namespace winner
    {
        extern int winner_player;
    }
    namespace game_mode
    {
        extern string choosen_mode;
    }
}

/** \class TestLevelFactory test_level_factory.h "include/test_level_factory.h"
 *  \brief Class used to create the levels in game
 */
class TestLevelFactory : public LevelFactory {
public:
    /** \fn make_level(const string& level_id)
      * \public
      * \brief Method to create a new level
      * \param level_id string& id of level to be created
      * \return Level* a pointer to the created level
      */
    Level * make_level(const string& level_id);
    /** \fn release(Level *level)
      * \public
      * \brief Method to destroy the created level
      * \param level Level* Pointer to the level that will be destroied
      * \return void
      */
    void release(Level *level);

private:
};

#endif
