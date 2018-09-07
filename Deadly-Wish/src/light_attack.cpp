#include "light_attack.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define LIGHT_ATTACK_BASE_DAMAGE 10
#define LIGHT_ATTACK_WIDTH 10


using namespace std;
using namespace ijengine;


LightAttack::LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp)
    : Skill(parent, xp, yp, LIGHT_ATTACK_BASE_DAMAGE, mage_id), light_attack_character_id(mage_id),
            light_attack_speed(100.0)
{
    light_attack_frame = 0;
    light_attack_start = 0;
    m_x = xp;
    m_y = yp;
    light_attack_bounding_box = Rectangle(m_x, m_y, (double)LIGHT_ATTACK_WIDTH, (double)LIGHT_ATTACK_WIDTH);
    light_attack_damage = LIGHT_ATTACK_BASE_DAMAGE;
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
    return light_attack_bounding_box;
}

const list<Rectangle>&
LightAttack::hit_boxes() const {
    static list<Rectangle> boxes {light_attack_bounding_box};
    return boxes;
}

pair<double, double>
LightAttack::direction() const
{
    return pair<double, double>(light_attack_axis_x_direction, light_attack_axis_y_direction);
}

void
LightAttack::update_time(unsigned now)
{
    // if it's the first update self
    if(light_attack_start == 0) {
      light_attack_start = now;
      light_attack_current_time = now;
    }

    if((now - light_attack_start) > 100) {
        invalidate();
    }
}
