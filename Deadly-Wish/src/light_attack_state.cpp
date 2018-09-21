/**\file light_attack_state.cpp
  *\brief Este é o arquivo da classe do LightAttackState,que é ativado quando
  *o player realiza um ataque fraco.
  */
 //Incluindo arquivo da classe LightAttackState
#include "light_attack_state.h"

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
    //Tempo de duração de um estado em milissegundos.
    state_refresh_rate = 100;
}
