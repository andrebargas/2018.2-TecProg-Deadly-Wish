#include "light_attack.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define LIGHT_ATTACK_BASE_DAMAGE 10


using namespace std;
using namespace ijengine;


LightAttack::LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp)
    : Skill(parent, xp, yp, LIGHT_ATTACK_BASE_DAMAGE, mage_id), m_character_id(mage_id), m_speed(100.0) 
{
    m_frame = 0;
    m_start = 0;
    m_x = xp;
    m_y = yp;
    m_bounding_box = Rectangle(m_x, m_y, 10.00, 10.00);
    m_damage = LIGHT_ATTACK_BASE_DAMAGE;
}

LightAttack::~LightAttack()
{

}

void
LightAttack::draw_self(Canvas *canvas, unsigned, unsigned)
{
   
}

void
LightAttack::update_self(unsigned now, unsigned last)
{
    update_time(now);
}

bool
LightAttack::active() const
{
    return true;
}

const Rectangle& 
LightAttack::bounding_box() const
{
    return m_bounding_box;
}

const list<Rectangle>&
LightAttack::hit_boxes() const {
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

pair<double, double>
LightAttack::direction() const
{
    return pair<double, double>(m_dx, m_dy);
}

void
LightAttack::update_time(unsigned now)
{
    // if it's the first update self
    if(m_start == 0) {
        m_start = now;
        m_current_time = now;
    }

    if((now - m_start) > 100) {
        invalidate();
    }
}
