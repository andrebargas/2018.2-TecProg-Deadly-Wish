/** \file skill.h
  * \brief Este é o arquivo header da classe Skill, de habilidade dos personagens no jogo, 
  * com herança de GameObject e Collidable da endige do jogo.
  */
#ifndef SKILL_H
#define SKILL_H

//! Inclui os arquivos da engine do jogo
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>
#include <assert.h>

using namespace ijengine;

/** \class Skill skill.h "include/skill.h"
 *  \brief Classe que herda de GameObject e Collidable
 *  que calcula o dano recebido pelos personagens.
 * \breif Método Construtor Skill
 * \param *parent Ponteiro para o GameObject
 * \param x_posiotion double posição no eixo X
 * \param y_posiotion double posição no eixo y
 * \param damage int dano da habilidade
 * \param character_id int identificador do personagem
 */
class Skill : public GameObject, public Collidable
{
  public:
    /** \fn Skill(GameObject *parent, double x_posiotion, double y_posiotion, int damage,
        int character_id)
     * \public
     * \brief Método construtor
     */
    Skill(GameObject *parent, double x_posiotion, double y_posiotion, int damage,
          int character_id);

    /** \fn ~Skill()
      * \public
      * \brief Método destrutor
      */
    ~Skill();

    //! Método que retorna a habilidade de um personagem
    unsigned get_character_id() const
    {
        assert(skill_character_id >= 1 && skill_character_id <=4);
        return skill_character_id;
    }

    //! Método que retorna a skill_damage
    int get_damage() const
    {
        assert(skill_damage > 0);
        return skill_damage;
    }

    //! Método que retorna a colisão
    int get_collided() const 
    { 
        assert(skill_collided > 0);
        return skill_collided; 
    }

    //! Métodos virtuais de colisão
    virtual bool active() const = 0;
    virtual const Rectangle &bounding_box() const = 0;
    virtual const list<Rectangle> &hit_boxes() const = 0;
    virtual pair<double, double> direction() const = 0;
    virtual void on_collision(const Collidable *who, const Rectangle &where, unsigned now, unsigned last);

  protected:
    //! Variável que indica o character_id skill
    unsigned skill_character_id;
    //! Variável que indica o dano do skill
    int skill_damage;
    //! Variável que indica a velocidade do skill
    double skill_speed;
    //! Variável que indica a colisão do skill
    int skill_collided;
};

#endif
