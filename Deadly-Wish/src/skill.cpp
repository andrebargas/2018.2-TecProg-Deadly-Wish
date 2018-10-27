/** \file skill.cpp
  * \brief This is the character class file of the characters in the game, skill damage size..
  */
#include "skill.h"
#include "character.h"
#include "base.h"
#include "assert.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>

/** fn Skill(GameObject *parent, double x_posiotion, double y_posiotion, int damage, int character_id)
 * \public
 * \breif Skill buider method
 * \param *parent Pointer to GameObject
 * \param x_posiotion double X position axis
 * \param y_posiotion double y position axis
 * \param damage int skill damage
 * \param character_id int
 */
Skill::Skill(GameObject *parent, double x_posiotion, double y_posiotion, int damage, int character_id)
    : GameObject(parent, x_posiotion, y_posiotion), skill_character_id(character_id)
{
    assert(parent != nullptr);
    assert(x_posiotion !=NULL);
    assert(y_posiotion !=NULL);
    assert(damage > 0);
    assert(character_id >= 1 && character_id <= 4);
    
    skill_collided = 0;
    cout << "registrando skill nas fisica\n" << endl;
    skill_damage = damage;
    physics::register_object(this);
}
//! Destructor method
Skill::~Skill()
{
    cout << "desregistrando skill nas fisica" << endl;
    physics::unregister_object(this);
}

/** fn on_collision(const Collidable *who, const Rectangle &where, unsigned now, unsigned last)
 * \public
 * \brief Builder on_collision
 * \param *who Character choose
 * \param &where endereço onde a habilidade será usada
 * \param now Current state
 * \param last - last moment skill was used
 */
void Skill::on_collision(const Collidable *who, const Rectangle &where, unsigned now, unsigned last)
{
    assert(who != nullptr);
    assert(now > 0);
    assert(last > 0);

    const Character *c = dynamic_cast<const Character *>(who);
    const Base *b = dynamic_cast<const Base *>(who);

    if ((c and c->get_id() != skill_character_id) || (b and b->get_base_player_id() != skill_character_id))
        {
        cout << "Character invalidete!" << endl;
        invalidate();
        }
    else
    {
        //Nothing to do!
    }
}
