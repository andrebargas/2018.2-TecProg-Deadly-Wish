#include "skill.h"
#include "character.h"
#include "base.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>


Skill::Skill(GameObject *parent, double axis_position_x, double axis_position_y, int new_skill_damage, int character_id)
    : GameObject(parent, xp, yp), m_character_id(character_id)
{
    skill_collided = 0;
    printf("registrando skill nas fisica\n");
    damage = new_skill_damage;
    physics::register_object(this);
}

Skill::~Skill()
{
    printf("desregistrando skill nas fisica\n");
    physics::unregister_object(this);
}

void
Skill::on_collision(const Collidable *who, const Rectangle& where, unsigned moment_now, unsigned moment_last)
{
    const Character *c = dynamic_cast<const Character *>(who);
    const Base *b = dynamic_cast<const Base *>(who);


    if ((c and c->id() != character_id) || (b and b->base_player_id() != character_id))
    {
        // Printf with "OI" have no meaning
        // printf("OI\n");
        invalidate();
    }
}
