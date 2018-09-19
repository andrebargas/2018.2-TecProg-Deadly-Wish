/** \file infiltrator.h
  * \brief Este é o arquivo header da classe Infiltrator que é filha da classe Character.
  */

#ifndef INFILTRATOR_H
#define INFILTRATOR_H

#include "character.h"

using namespace ijengine;

/** \class Infiltrator infiltrator.h "include/infiltrator.h"
  * \brief Permite que o assassino tenha poderes de defesa e ataque, personagem ativo ou não e suas posições nos eixos x e y.
  */
class Infiltrator : public Character {

public:
    /** \fn Knight(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
      * \public
      * \brief Método Construtor
      * \param sprite_paths - desenha personagem
      * \param id - identificador do personagem
      * \param x - posição no eixo x
      * \param y - posição no eixo y
      * \param character_code - codigo do personagem
      */
    Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);

    /** \fn active()
      * \public
      * \brief Retorna verdadeiro se o personagem está ativo.
      * \return bool
      */
    bool active() const;

//! Métodos Protegidos
protected:

    /** \var bool m_active
      * \protected
      * \brief Guarda o estado do personagem, se ele está ativo ou não.
      */
    bool m_active;
    
    /** \fn do_heavy_attack()
      * \protected
      * \brief Método que executa um ataque pesado
      */
    void do_heavy_attack();
 
    /** \fn do_light_attack()
      * \protected
      * \brief Método que executa um ataque leve
      */
    void do_light_attack();
    
    /** \fn do_defense()
      * \protected
      * \brief Método que executa uma defesa
      */
    void do_defense();

    /** \fn do_special()
      * \protected
      * \brief Método que executa um ataque especial
      */
    void do_special();
};

#endif
