/** /file test_level_factory.cpp
  * /brief Esta é o arquivo para a classe responsavel pela criação do Leveis do jogo
  */
#ifndef TEST_LEVEL_FACTORY_H
#define TEST_LEVEL_FACTORY_H

// Import da classe pai
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
 *  \brief Classe usada para instanciar os leveis do jogo, podem ser chamados de fases também.
 */
class TestLevelFactory : public LevelFactory {
public:
    /** \fn make_level(const string& level_id)
      * \public
      * \brief Método para criar um novo level
      * \param level_id string& Codigo do level que se deseja criar.
      * \return Level* O ponteiro para o level criado
      */
    Level * make_level(const string& level_id);
    /** \fn release(Level *level)
      * \public
      * \brief Método detruir um level criado
      * \param level Level* Ponteiro para o level que ira ser destruido
      * \return void
      */
    void release(Level *level);

private:
};

#endif
