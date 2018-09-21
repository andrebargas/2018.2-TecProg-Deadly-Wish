/** \file light_attack_state.h
  * \brief Este é o arquivo da classe do LightAttackState,que é ativado quando
  *  o player realiza um ataque fraco.
  */

#ifndef LIGHT_ATTACK_STATE_H
#define LIGHT_ATTACK_STATE_H

//Incluindo arquivo da classe CharacterState
#include "character_state.h"

/** \class LightAttackState light_attack_state.h "include/light_attack_state.h"
 *  \brief Classe usada para definir o estado de ataque fraco, quando algum dos
 *  players o invoca.
 */
class LightAttackState : public CharacterState {
public:
    /** \fn LightAttackState()
      * \public
      * \brief Método construtor
      * \Não recebe parâmetros.
      * \Atualiza o estado do player para ataque fraco e seu respectivo tempo de duração para 100 milissegundos.
      */
    LightAttackState();
    
    /** \fn ~LightAttackState()
      * \public
      * \brief Método destrutor
      */
    ~LightAttackState();
};

#endif