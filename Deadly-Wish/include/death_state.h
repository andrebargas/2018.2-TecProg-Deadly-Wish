/** \file death_state.h
  * \brief Este é o arquivo da classe do DeathState,
  *  ...que é ativado quando algum player morre no jogo.
  */
 
#ifndef DEATH_STATE_H
#define DEATH_STATE_H

//Incluindo arquivo da classe CharacterState
#include "character_state.h"

/** \class DeathState death_state.h "include/death_state.h"
 *  \brief Classe usada para definir se um player morreu no jogo.
 */
class DeathState : public CharacterState {
public:
    /** \fn DeathState()
      * \public
      * \brief Método construtor
      * \Não recebe parâmetros.
      * \Atualiza o estado do player para morto e seu respectivo tempo de duração para 275 milissegundos.
      */
    DeathState();
    
    /** \fn ~DeathState()
      * \public
      * \brief Método destrutor
      */
    ~DeathState();
};

#endif