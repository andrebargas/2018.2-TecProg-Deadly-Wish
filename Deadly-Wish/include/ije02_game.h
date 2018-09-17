/** /file ije02_game.h
  * /brief Esta é a classe que instacia o jogo a partir da ijengine.
  */

#ifndef IJE02_GAME_H
#define IJE02_GAME_H

// Incluindo aquivo da classes Translator responsavel por receber os eventos do input
// e TestLevelFactory que faz os leveis do jogo.
#include "translator.h"


//Incluindo aquivos das classes da IJEngine que montam o jogo.
//PBS
#include <ijengine/game.h>
#include <ijengine/engine.h>
#include <ijengine/mouse_event.h>
#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/events_translator.h>
#include <ijengine/joystick_event.h>

#include "test_level_factory.h"

#include <iostream>
#include <vector>

using namespace ijengine;
using namespace std;


//Name space para cada um dos inputs de cada um dos players
namespace ijengine
{
    namespace game_event
    {
        extern unsigned HEAVY_ATTACK_P1;
        extern unsigned HEAVY_ATTACK_P2;
        extern unsigned HEAVY_ATTACK_P3;
        extern unsigned HEAVY_ATTACK_P4;
        extern unsigned LIGHT_ATTACK_P1;
        extern unsigned LIGHT_ATTACK_P2;
        extern unsigned LIGHT_ATTACK_P3;
        extern unsigned LIGHT_ATTACK_P4;
        extern unsigned DEFENSE_P1;
        extern unsigned DEFENSE_P2;
        extern unsigned DEFENSE_P3;
        extern unsigned DEFENSE_P4;
        extern unsigned SPECIAL_P1;
        extern unsigned SPECIAL_P2;
        extern unsigned SPECIAL_P3;
        extern unsigned SPECIAL_P4;
        extern unsigned MOVEMENT_P1;
        extern unsigned MOVEMENT_P2;
        extern unsigned MOVEMENT_P3;
        extern unsigned MOVEMENT_P4;
        extern unsigned MOTION;
        extern unsigned CLICK;
        extern unsigned ENTER_GAME;
        extern unsigned CHOOSE_CHARACTER;
        extern unsigned UP;
        extern unsigned DOWN;
        extern unsigned LEFT;
        extern unsigned RIGHT;
    }
}

// Constantes para setar o tamanho e proporção da tela
const int SCREEN_WIDTH_PROPORTION = 4;
const int SCREEN_HEIGHT_PROPORTION = 3;
const int SCREEN_BASE_SIZE = 80;
const int GAME_SCALE = 3;
const int SCREEN_WIDTH = SCREEN_WIDTH_PROPORTION * SCREEN_BASE_SIZE;
const int SCREEN_HEIGHT = SCREEN_HEIGHT_PROPORTION * SCREEN_BASE_SIZE;
const int SCREEN_SCALED_WIDTH = SCREEN_WIDTH * GAME_SCALE;
const int SCREEN_SCALED_HEIGHT = SCREEN_HEIGHT * GAME_SCALE;


/** \class Ije02Game ije02_game.h "include/ije02_game.h"
 *  \brief Classe usada para instanciar objetos da ijengine essenciais para montar o jogo.
 */
class Ije02Game {

public:

  /** \fn Ije02Game(const string& title, int weigth, int height, double scale)
    * \public
    * \brief Método construtor
    * \param title string& Titulo do jogo. Valor constante == "Deadly Wish".
    * \param weigth int Altura da tela do jogo.
    * \param height int Altura da tela do jogo.
    * \param scale double Escala da tela do jogo.
    */
    Ije02Game(const string& title, int weigth, int height, double scale);

    /** \fn ~Ije02Game()
      * \public
      * \brief Método destrutor
      */
    ~Ije02Game();

    /** \fn run(const string& level_id)
      * \public
      * \brief Método para rodar o jogo após crialo.
      * \param level_id string& Recebe o level que ira começar o jogo. Por default sera o \ref MenuLevel.
      */
    int run(const string& level_id);

private:
  /** \var Game ije_game
    *  \brief Variavel para instanciar jogo através da classe da IjEngine
    */
	Game ije_game;
  /** \var Engine ije_engine
    *  \brief Variavel para instanciar a engine através da classe da Engine
    */
	Engine ije_engine;
  /** \var Translator ije_translator
    * \brief Variavel para instanciar translator do jogo que é reponsavel por capturar
    * os eventos da entrada.
    */
	Translator ije_translator;
  /** \var TestLevelFactory ije_level_factory
    *  \brief Variavel para instanciar a TesteLevelFactory que por sua vez instancia os outros
    * possives leveis.
    */
	TestLevelFactory ije_level_factory;

};

#endif
