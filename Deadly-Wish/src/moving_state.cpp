/**\file moving_state.cpp
  *\brief Esta é o arquivo da classe MovingState, que é ativado quando
  *...tem a uma entrada de movimentação do player.
  */

 //Incluindo arquivo da classe MovingState
#include "moving_state.h"
#include <assert.h>

/**\fn MovingState()
  *\public
  *\brief Método construtor
  *\não recebe parâmetros
  */
MovingState::MovingState()
    :CharacterState()
{
    //Tranforma o estado atual do player para em movimento.
    current_state = MOVING_STATE;
    assert(current_state);
    //Tempo de duração de um estado em milissegundos
    state_refresh_rate = 100;
    assert(state_refresh_rate);
}
