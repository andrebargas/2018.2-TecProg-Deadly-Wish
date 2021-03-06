/** \file defense_state.cpp
  * \brief Este é o arquivo da classe do DefenseState,que é ativado quando
  *  algum player usa defesa.
  */

 //Incluindo arquivo da classe DefenseState
#include "defense_state.h"

/** \fn DefenseState()
  * \public
  * \brief Método construtor
  * \não recebe parâmetros
  */
DefenseState::DefenseState()
    :CharacterState()
{
    //Representa o estado atual do player.
    current_state = DEFENSE_STATE;
    //Tempo de duração de um estado em milissegundos.
    state_refresh_rate = 100;
}
