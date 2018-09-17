/** \file winner_level.cpp
  * \brief Esta é o arquivo da classe do level WinnerLevel, que é ativado quando algum player ganha
  *  o jogo.
  */

#include "winner_level.h"
#include "engine.h"
#include "util.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace ijengine;
using namespace util;

/** \fn WinnerLevel(const string& next = "", int winner_player = -1)
  * \public
  * \brief Método construtor
  * \param next const string& Parametro para o proximo level. Valor constante igual " ",
  * final do jogo.
  * \param winner_player int Id do player ganhador. É iniciado com "-1" para que não o seja
  * level não seja iniciado já com um ganhador.
  */
WinnerLevel::WinnerLevel(const string& next_level, int winner_player)
    : winner_level_done(false), winner_level_next(next_level), winner_level_start(-1),
      winner_level_winner_player(winner_player)
{
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/menu.ogg", 30, 3);
    set_congratulations_string();
}

/** \fn ~WinnerLevel()
  * \public
  * \brief Método destrutor
  */
WinnerLevel::~WinnerLevel()
{

}

/** \fn update_self(unsigned now, unsigned last)
  * \protected
  * \brief Função para atualizar o tempo de inicio do level, e setar atributo
  *  #winner_level_start. Nome não pode ser mudado por ser um metodo herdado da classe pai,
  *  protegida pelo escopo do projeto
  * \param now unsigned Tempo atual do jogo
  * \return void
  */
void
WinnerLevel::update_self(unsigned now, unsigned)
{
    if (winner_level_start == -1)
        winner_level_start = now;

    if (now - winner_level_start > 3000)
        winner_level_start = true;
}

/** \fn draw_self(Canvas *canvas, unsigned now, unsigned last)
  * \protected
  * \brief Método que faz o desenho grafico do jogo. Nome não pode ser mudado por ser um
  *  metodo herdado da classe pai, protegida pelo escopo do projeto
  * \param canvas Canvas* Ponteiro para objeto da classe responsavel pela renderização do jogo.
  * \param now unsigned Tempo atual do jogo
  * \param last unsigned
  * \return void
  */
void
WinnerLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    auto font = resources::get_font("Forelle.ttf", 45);
    canvas->set_font(font);

    canvas->clear();
    canvas->draw(winner_level_congratulations, 60, 85);
}

/** \fn set_congratulations_string()
  * \protected
  * \brief Faz o 'set' da string usada na parabenização do jogador ao ganhar o jogo
  * \return void
  */
void
WinnerLevel::set_congratulations_string()
{
    // Seta uma frase diferente para cada um do players
    switch(winner_level_winner_player) {
        case PLAYER_1:
            winner_level_congratulations = "Jogador 1 venceu!";
            break;

        case PLAYER_2:
            winner_level_congratulations = "Jogador 2 venceu!";
            break;

        case PLAYER_3:
            winner_level_congratulations = "Jogador 3 venceu!";
            break;

        case PLAYER_4:
            winner_level_congratulations = "Jogador 4 venceu!";
            break;

        //UC
        default:
            printf("Error on set_congratulations_string!\n");
            printf("Valor de winner player: %d\n", winner_level_winner_player);
            winner_level_congratulations = "Houve um erro\n no jogo! :D";
            break;
    }
}

/** \fn done()
  * \public
  * \brief Retorna verdadeiro quando o level chega ao final. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return bool retorna atributo winner_level_done
  */
bool
WinnerLevel::done() const
{
    return winner_level_done;
}

/** \fn next()
  * \public
  * \brief Retorna qual sera o proximo level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string retorna atributo winner_level_next
  */
string
WinnerLevel::next() const
{
    return winner_level_next;
}

// UC
/** \fn audio()
  * \public
  * \brief Retorna qual é o audio do level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string constante "."
  */
string
WinnerLevel::audio() const {
    //NSC
    return ".";
}
