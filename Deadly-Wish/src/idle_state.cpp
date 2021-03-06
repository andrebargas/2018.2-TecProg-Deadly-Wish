/** \file idle_state.cpp
  * \brief Este é o arquivo da classe do IdleState,que é ativado quando
  * o player está parado.
  */

//Incluindo arquivo da classe IdleState
#include "idle_state.h"

/** \fn IdleState()
      * \public
      * \brief Método construtor
      * \Não recebe parâmetros.
      * \Atualiza o estado do player para ocioso e seu respectivo tempo de duração para 275 milissegundos.
      */
IdleState::IdleState()
    :CharacterState()
{
    //Representa o estado atual do player.
    current_state = IDLE_STATE;
    //Tempo de duração de um estado em milissegundos.
    state_refresh_rate = 275;
}
