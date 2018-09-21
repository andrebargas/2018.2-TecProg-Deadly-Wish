/** \file light_attack_state.h
  * \brief Este é o arquivo da classe do CharacterState,que é ativado quando
  *  ...algum player assume um estado no jogo.
  */
//impede que um arquivo de cabeçalho seja incluído várias vezes.
#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

#include <memory>
#include <vector>

//Incluindo arquivo util.h que contém constantes enumeradas 
#include "util.h"

using std::shared_ptr;
using std::vector;

using namespace ijengine;
using namespace util;

/** \class CharacterState character_state.h "include/character_state.h"
 *  \brief Classe usada para definir o estado de um player no jogo.
 */
class CharacterState {
public:
    /** \fn CharacterState()
      * \public
      * \brief Método construtor
      * \não recebe parâmetros
      */
    CharacterState();
    /** \fn ~CharacterState()
      * \public
      * \brief Método destrutor
      * \não recebe parâmetros
      */
    ~CharacterState();

    /** \fn get_current_state()
      * \public
      * \brief Método get
      * \return State retorna o estado do player 
      */
    State get_current_state() const { return current_state; }
    /** \fn get_refresh_rate()
      * \public
      * \brief Método get
      * \return unsigned retorna a duração de um estado do player
      */
    unsigned get_refresh_rate() const { return state_refresh_rate; }

protected:
    //Representa o estado atual do player.
    State current_state;
    //Tempo de duração de um estado em milissegundos
    unsigned state_refresh_rate;

};

#endif
