#include "skill.h"
#include "character.h"
#include "base.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>


Skill::Skill(GameObject *parent, double xp, double yp, int damage, int character_id)
    : GameObject(parent, xp, yp), m_character_id(character_id)
{
    m_collided = 0;
    printf("registrando skill nas fisica\n");
    m_damage = damage;
    physics::register_object(this);
}

Skill::~Skill()
{
    printf("desregistrando skill nas fisica\n");
    physics::unregister_object(this);
}

void
Skill::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last)
{
    const Character *c = dynamic_cast<const Character *>(who);
    const Base *b = dynamic_cast<const Base *>(who);


    if ((c and c->id() != m_character_id) || (b and b->get_base_player_id() != m_character_id))
    {
        printf("OI\n");
        invalidate();
    }
}
