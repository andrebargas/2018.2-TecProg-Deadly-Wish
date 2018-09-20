/** \file skill.h
  * \brief Este é o arquivo da classe de habilidade dos personagens no jogo, com herança de 
  * GameObject e Collidable da endige do jogo.
  */
#ifndef SKILL_H
#define SKILL_H

//!
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>

using namespace ijengine;

class Skill : public GameObject, public Collidable
{
  public:
    Skill(GameObject *parent, double x_posiotion, double y_posiotion, int damage,
          int character_id);
    ~Skill();

    unsigned get_character_id() const { return skill_character_id; }
    int get_damage() const { return skill_damage; }
    int get_collided() const { return skill_collided; }

    //metodos virtual Colidable
    virtual bool active() const = 0;
    virtual const Rectangle &bounding_box() const = 0;
    virtual const list<Rectangle> &hit_boxes() const = 0;
    virtual pair<double, double> direction() const = 0;
    virtual void on_collision(const Collidable *who, const Rectangle &where, unsigned now, unsigned last);

  protected:
    unsigned skill_character_id;
    int skill_damage;
    double skill_speed;
    int skill_collided;
};

#endif
