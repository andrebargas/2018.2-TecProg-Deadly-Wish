/**\file character_state.h
  *\brief Este é o arquivo da classe do CharacterState,que é ativado quando
  *...algum player assume um estado no jogo.
  */

#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

#include <memory>
#include <vector>
#include <assert.h>

//Incluindo arquivo util.h que contém constantes enumeradas 
#include "util.h"

using std::shared_ptr;
using std::vector;

using namespace ijengine;
using namespace util;

/**\class CharacterState character_state.h "include/character_state.h"
 *\brief Classe usada para definir o estado de um player no jogo.
 */
class CharacterState {
public:
    /**\fn CharacterState()
      *\public
      *\brief Método construtor
      *não recebe parâmetros
      */
    CharacterState();
    /**\fn ~CharacterState()
      *\public
      *\brief Método destrutor
      *\não recebe parâmetros
      */
    ~CharacterState();

    /**\fn get_current_state()
      *\public
      *\brief Método get
      *\return State retorna o estado do player 
      */
  
    State get_current_state() 
    const { return current_state;
     assert(current_state >= 0 && current_state <= 7 ); }

    /**\fn get_refresh_rate()
      *\public
      *\brief Método get
      *\return unsigned retorna a duração de um estado do player
      */
    unsigned get_refresh_rate() 
    const { return state_refresh_rate;
    assert(state_refresh_rate != NULL);}

protected:
    /*\var current_state
     *\brief Representa o estado atual do player.
     */
    State current_state;

    /*\var state_refresh_rate
     *\brief Tempo de duração de um estado em milissegundos
     */
    unsigned state_refresh_rate;

};

#endif
