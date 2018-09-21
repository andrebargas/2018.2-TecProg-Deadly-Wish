/** \file special_state.cpp
  * \brief Este é o arquivo da classe do SpecialState,que é ativado quando
  *  ...algum player utiliza sua skill especial.
  */

//Incluindo arquivo da classe SpecialState
#include "special_state.h"

/** \fn SpecialState()
  * \public
  * \brief Método construtor
  * \não recebe parâmetros
  */
SpecialState::SpecialState()
    :CharacterState()
{
    //Representa o estado atual do player.
    current_state = SPECIAL_STATE;
    //Tempo de duração de um estado em milissegundos
    state_refresh_rate = 100;
}
