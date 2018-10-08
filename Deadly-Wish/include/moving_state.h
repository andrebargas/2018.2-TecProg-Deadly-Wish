/**\file moving_state.h
  *\brief Esta é o arquivo da classe MovingState, que é ativado quando
  *...tem a uma entrada de movimentação do player.
  */

#ifndef MOVING_STATE_H
#define MOVING_STATE_H

//Incluindo arquivo da classe CharacterState
#include "character_state.h"

/**\class MovingState moving_state.h "include/moving_state.h"
 *\brief Classe usada para definir o estado de movimentação de um
 *players quando é invocado.
 */
class MovingState : public CharacterState {
public:
      /**\fn MovingState()
      *\public
      *\brief Método construtor
      *Não recebe parâmetros.
      *Atualiza o estado do player para movimentação 
      *e seu respectivo tempo de duração para 100 milissegundos.
      */
    MovingState();

    /**\fn ~MovingState()
      *\public
      *\brief Método destrutor
      */
    ~MovingState();
};

#endif