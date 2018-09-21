/**\file special_state.h
  *\brief Este é o arquivo da classe do SpecialState,que é ativado quando
  *...algum player utiliza sua skill especial.
  */

#ifndef SPECIAL_STATE_H
#define SPECIAL_STATE_H

//Incluindo arquivo da classe CharacterState
#include "character_state.h"

/**\class SpecialState special_state.h "include/special_state.h"
 *\brief Classe usada para definir um estado especial de um dos
 *players.
 */
class SpecialState : public CharacterState {
public:
    /**\fn SpecialState()
      *\public
      *\brief Método construtor
      *Não recebe parâmetros.
      *Atualiza o estado do player para "utilizando especial"
      *e seu respectivo tempo de duração para 100 milissegundos.
      */
    SpecialState();

    /**\fn ~SpecialState()
      *\public
      *\brief Método destrutor
      */
    ~SpecialState();
};

#endif