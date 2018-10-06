/**\file heavy_attack_state.cpp
  *\brief Este é o arquivo da classe do HeavyAttackState,que é ativado quando
  *...o player usa o estado de ataque forte.
  */

//Incluindo arquivo da classe HeavyAttackState
#include "heavy_attack_state.h"
#include <assert.h>

/**\fn HeavyAttackState()
  *\public
  *\brief Método construtor
  *não recebe parâmetros
  */
HeavyAttackState::HeavyAttackState()
    :CharacterState()
{
    //Representa o estado atual do player.
    current_state = HEAVY_ATTACK_STATE;
    assert(HEAVY_ATTACK_STATE == 4);
    //Tempo de duração de um estado em milissegundos.
    state_refresh_rate = 100;
    assert(state_refresh_rate == 100);
}
