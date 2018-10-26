/**\file idle_state.h
  *\brief Este é o arquivo da classe do IdleState,que é ativado quando
  *o player está parado.
  */

#ifndef IDLE_STATE_H
#define IDLE_STATE_H

//Incluindo arquivo da classe CharacterState
#include "character_state.h"

/**\class IdleState idle_state.h "include/idle_state.h"
 *\brief Classe usada para definir estado ocioso de um
 *players.
 */
class IdleState : public CharacterState {
public:
    /**\fn IdleState()
      *\public
      *\brief Método construtor
      *Não recebe parâmetros.
      *Atualiza o estado do player para ocioso 
      *e seu respectivo tempo de duração para 275 milissegundos.
      */
    IdleState();
    /**\fn ~IdleState()
      *\public
      *\brief Método destrutor
      */
    ~IdleState();
};

#endif