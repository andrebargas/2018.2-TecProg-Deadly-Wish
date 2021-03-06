/** \file moving_state.cpp
  * \brief Esta é o arquivo da classe MovingState, que é ativado quando
  *  ...tem a uma entrada de movimentação do player.
  */

 //Incluindo arquivo da classe MovingState
#include "moving_state.h"

/** \fn MovingState()
  * \public
  * \brief Método construtor
  * \não recebe parâmetros
  */
MovingState::MovingState()
    :CharacterState()
{
    //Representa o estado atual do player.
    current_state = MOVING_STATE;
    //Tempo de duração de um estado em milissegundos
    state_refresh_rate = 100;
}
