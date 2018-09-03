#include "light_attack.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define LIGHT_ATTACK_BASE_DAMAGE 10
#define SPEED_ATTACK 100

using namespace std;
using namespace ijengine;


LightAttack::LightAttack(GameObject *parent, unsigned hero_id, double x_position, double y_position)
    : Skill(parent, x_position, y_position, LIGHT_ATTACK_BASE_DAMAGE, hero_id), character_id(hero_id), speed_attack(SPEED_ATTACK) 
{
    frame = 0;
    start = 0;
    position_axis_x = x_position;
    position_axis_y = y_position;
    bounding_box = Rectangle(position_axis_x, position_axis_y, 10.00, 10.00);
    damage_attack = LIGHT_ATTACK_BASE_DAMAGE;
}

LightAttack::~LightAttack() {
}

void
LightAttack::DrawSelf(Canvas *canvas, unsigned, unsigned)
{
   
}

void
LightAttack::update_self(unsigned now_moment, unsigned last_moment)
{
    update_time(now_moment);
}

bool
LightAttack::is_active() const
{
    return true;
}

const Rectangle&
LightAttack::get_bounding_box() const
{
    return bounding_box;
}

const list<Rectangle>&
LightAttack::get_hit_boxes() const {
    static list<Rectangle> boxes {bounding_box};
    return boxes;
}

pair<double, double>
LightAttack::get_direction() const
{
    return pair<double, double>(x_direction, y_direction);
}

void
LightAttack::update_time(unsigned now_moment)
{
    // if it's the first update self
    if(start == 0) {
        start = now_moment;
        current_time = now_moment;
    }

    if((now_moment - start) > 100) {
        invalidate();
    }
}
