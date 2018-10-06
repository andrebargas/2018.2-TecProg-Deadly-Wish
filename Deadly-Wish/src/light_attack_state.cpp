
/**\file light_attack_state.cpp
  *\brief Este é o arquivo da classe do LightAttackState,que é ativado quando
  *o player realiza um ataque fraco.
  */
 //Incluindo arquivo da classe LightAttackState
#include "light_attack_state.h"
#include <assert.h>

/**\fn LightAttackState()
  *\public
  *\brief Método construtor
  *\não recebe parâmetros
  */
LightAttackState::LightAttackState()
    :CharacterState()
{
    //Representa o estado atual do player.
    current_state = LIGHT_ATTACK_STATE;
    assert(LIGHT_ATTACK_STATE == 3);
    //Tempo de duração de um estado em milissegundos.
    state_refresh_rate = 100;
    assert(state_refresh_rate == 100);
}
