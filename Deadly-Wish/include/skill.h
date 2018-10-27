/** \file skill.h
  * \brief Este é o arquivo header da classe Skill, de habilidade dos personagens no jogo, 
  * com herança de GameObject e Collidable da endige do jogo.
  */
#ifndef SKILL_H
#define SKILL_H

//! Include game engine files
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>
#include <assert.h>

using namespace ijengine;

/** \class Skill skill.h "include/skill.h"
 *  \brief Class that inherits from GameObject and Collidable that 
 *  calculates the damage received by the characters.
 * \breif Skill builder method
 * \param parent Pointer to GameObject
 * \param xp position in x
 * \param yp position in y
 * \param damage int skill damage
 * \param character_id int character identifier
 */
class Skill : public GameObject, public Collidable
{
  public:
    /** \fn Skill(GameObject *parent, double x_posiotion, double y_posiotion, int damage,
        int character_id)
     * \public
     * \brief builder method
     */
    Skill(GameObject *parent, double x_posiotion, double y_posiotion, int damage,
          int character_id);

    /** \fn ~Skill()
      * \public
      * \brief Destructor Method
      */
    ~Skill();

    //! Method that returns a character's ability
    unsigned get_character_id() const
    {
        assert(skill_character_id >= 1 && skill_character_id <=4);
        return skill_character_id;
    }

    //! Method that returns skill_damage
    int get_damage() const
    {
        assert(skill_damage > 0);
        return skill_damage;
    }

    //! Method that returns the collision
    int get_collided() const 
    { 
        assert(skill_collided > 0);
        return skill_collided; 
    }

    //! Virtual Collision Methods
    virtual bool active() const = 0;
    virtual const Rectangle &bounding_box() const = 0;
    virtual const list<Rectangle> &hit_boxes() const = 0;
    virtual pair<double, double> direction() const = 0;
    virtual void on_collision(const Collidable *who, const Rectangle &where, unsigned now, unsigned last);

  protected:
    //! Variable that indicates the character_id skill
    unsigned skill_character_id;
    //! Variable indicating skill damage
    int skill_damage;
    //! Variable that indicates the speed of the skill
    double skill_speed;
    //! Variable that indicates the skill collision
    int skill_collided;
};

#endif
