/** \file defense_state.h
  * \brief Este é o arquivo da classe do DefenseState,que é ativado quando
  *  ...algum player usa defesa.
  */
 
#ifndef DEFENSE_STATE_H
#define DEFENSE_STATE_H

//Incluindo arquivo da classe CharacterState
#include "character_state.h"

/** \class DefenseState defense_state.h "include/defense_state.h"
 *  \brief Classe usada para definir estado de defesa de um
 *  players no jogo.
 */
class DefenseState : public CharacterState {
public:
    /**\fn DefenseState()
      *\public
      *\brief Método construtor
      *Não recebe parâmetros.
      *Atualiza o estado do player para "utilizando defesa" 
      *e seu respectivo tempo de duração para 100 milissegundos.
      */
    DefenseState();
    
    /**\fn ~DefenseState()
      *\public
      *\brief Método destrutor
      */
    ~DefenseState();
};

#endif