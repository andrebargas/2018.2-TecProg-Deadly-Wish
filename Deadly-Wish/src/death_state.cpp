/**\file death_state.cpp
  *\brief Este é o arquivo da classe do DeathState,
  *...que é ativado quando algum player morre no jogo.
  */
 
//Incluindo arquivo da classe DeathState
#include "death_state.h"
#include <assert.h>

/**\fn DeathState()
  *\public
  *\brief Método construtor
  *Não recebe parâmetros.
  *Atualiza o estado do player para morto e seu respectivo tempo de duração para 275 milissegundos.
  */
DeathState::DeathState()
    :CharacterState()
{
    //Representa o estado atual do player.
    current_state = DEATH_STATE;
    assert(current_state);

    //Tempo de duração de um estado em milissegundos.
    state_refresh_rate = 275;
    assert(state_refresh_rate);
}