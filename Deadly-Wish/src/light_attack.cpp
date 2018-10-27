/** \file light_attack.h
  * \brief This is a file from class Light_Attack, with inheritance of class Skill
  */
#include "light_attack.h"
#include "character.h"
#include "assert.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

//! Vale of damage LIGHT_ATTACK_BASE_DAMAGE
#define LIGHT_ATTACK_BASE_DAMAGE 10
//! Width of LIGHT_ATTACK
#define LIGHT_ATTACK_WIDTH 10

using namespace std;
using namespace ijengine;

/** fn LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp)
 * \public
 * \breif Constructor method of LightAttack
 * \param *parent Pointer for GameObject
 * \param mage_id identifier of character mage
 * \param xp double posicion on axis X
 * \param yp double posicion on axis y
 */
LightAttack::LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp)
    : Skill(parent, xp, yp, LIGHT_ATTACK_BASE_DAMAGE, mage_id), light_attack_character_id(mage_id),
      light_attack_speed(100.0)
{
    assert(parent != nullptr);
    assert(mage_id >= 1 && mage_id <= 4);
    assert(xp != NULL);
    assert(yp != NULL);

    light_attack_frame = 0;
    assert(light_attack_frame != NULL);

    light_attack_start = 0;
    assert(light_attack_start != NULL);

    m_x = xp;
    m_y = yp;
    assert(m_x != NULL);
    assert(m_y != NULL);

    light_attack_bounding_box = Rectangle(m_x, m_y, (double)LIGHT_ATTACK_WIDTH, (double)LIGHT_ATTACK_WIDTH);
    light_attack_damage = LIGHT_ATTACK_BASE_DAMAGE;
}

//! Destructor of Class LightAttack
LightAttack::~LightAttack()
{
}

//! Virtual method of gameobject
void LightAttack::draw_self(Canvas *canvas, unsigned, unsigned)
{
    assert(canvas != NULL);
    assert(canvas != nullptr);

}

//! Method the indicates the update of LightAttack
/*!
\param now indicates the current update
\param las indicates the last update
*/
void LightAttack::update_self(unsigned now, unsigned last)
{
    assert(now != NULL);
    assert(last != NULL);

    update_time(now);
}

//! Activate the LightAttack
bool LightAttack::active() const
{
    return true;
}

//! Delimitation of LightAttack
const Rectangle & LightAttack::bounding_box() const
{
    return light_attack_bounding_box;
}

const list<Rectangle> & LightAttack::hit_boxes() const
{
    static list<Rectangle> boxes{light_attack_bounding_box};
    return boxes;
}

//! Direction of LightAttack
pair<double, double> LightAttack::direction() const
{
    return pair<double, double>(light_attack_axis_x_direction, light_attack_axis_y_direction);
}

//! Update of LightAttack
void LightAttack::update_time(unsigned now)
{
    // If is the first self-update
    if (light_attack_start == 0)
    {
        light_attack_start = now;
        light_attack_current_time = now;
    }
    else{
        //Nothing to do!
    }

    unsigned int time_updated = now - light_attack_start;

    if ( time_updated > 100)
    {
        invalidate();
    }
    else{
        //Nothing to do!
    }
}
