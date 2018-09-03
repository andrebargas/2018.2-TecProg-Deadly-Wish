#include "light_attack.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define LIGHT_ATTACK_BASE_DAMAGE 10
#define SPEED

using namespace std;
using namespace ijengine;


LightAttack::LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp)
    : Skill(parent, xp, yp, LIGHT_ATTACK_BASE_DAMAGE, mage_id), character_id(mage_id), speed(SPEED) 
{
    frame = 0;
    start = 0;
    m_x = xp;
    m_y = yp;
    bounding_box = Rectangle(m_x, m_y, 10.00, 10.00);
    damage = LIGHT_ATTACK_BASE_DAMAGE;
}

LightAttack::~LightAttack() {
}

void
LightAttack::DrawSelf(Canvas *canvas, unsigned, unsigned)
{
   
}

void
LightAttack::UpdateSelf(unsigned now, unsigned last)
{
    UpdateTime(now);
}

bool
LightAttack::Active() const
{
    return true;
}

const Rectangle& 
LightAttack::BoundingBox() const
{
    return bounding_box;
}

const list<Rectangle>&
LightAttack::HitBoxes() const {
    static list<Rectangle> boxes {bounding_box};
    return boxes;
}

pair<double, double>
LightAttack::Direction() const
{
    return pair<double, double>(m_dx, m_dy);
}

void
LightAttack::UpdateTime(unsigned now)
{
    // if it's the first update self
    if(start == 0) {
        start = now;
        current_time = now;
    }

    if((now - start) > 100) {
        invalidate();
    }
}
