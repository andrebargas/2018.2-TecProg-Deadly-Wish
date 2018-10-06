/** \file heavy_attack_state.h
  * \brief Este é o arquivo da classe do HeavyAttackState,que é ativado quando
  *  ...o player usa o estado de ataque forte.
  */

#ifndef HEAVY_ATTACK_STATE_H
#define HEAVY_ATTACK_STATE_H

//Incluindo arquivo da classe CharacterState
#include "character_state.h"

/**\class HeavyAttackState heavy_attack_state.h "include/heavy_attack_state.h"
 *\brief Classe usada para definir estado de ataque pesado, quando algum dos
 *players o invoca.
 */
class HeavyAttackState : public CharacterState {
public:
    /**\fn HeavyAttackState()
      *\public
      *\brief Método construtor
      *Não recebe parâmetros.
      *Atualiza o estado do player para "utilizando ataque pesado"
      *e seu respectivo tempo de duração para 100 milissegundos.
      */
    HeavyAttackState();
    
    /**\fn ~HeavyAttackState()
      *\public
      *\brief Método destrutor
      */
    ~HeavyAttackState();
};

#endif