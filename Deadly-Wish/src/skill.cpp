/** \file skill.cpp
  * \brief Este é o arquivo da classe de habilidade dos personagens no jogo, tamanho do dano da habilidade.
  */
#include "skill.h"
#include "character.h"
#include "base.h"
#include "assert.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>

/** fn Skill(GameObject *parent, double x_posiotion, double y_posiotion, int damage, int character_id)
 * \public
 * \breif Método Construtor Skill
 * \param *parent Ponteiro para o GameObject
 * \param x_posiotion double posição no eixo X
 * \param y_posiotion double posição no eixo y
 * \param damage int dano da habilidade
 * \param character_id int identificador do personagem
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
    printf("registrando skill nas fisica\n");
    skill_damage = damage;
    physics::register_object(this);
}
//! Método destrutor
Skill::~Skill()
{
    printf("desregistrando skill nas fisica\n");
    physics::unregister_object(this);
}

/** fn on_collision(const Collidable *who, const Rectangle &where, unsigned now, unsigned last)
 * \public
 * \brief Construtor on_collision
 * \param *who qual personagem está usando
 * \param &where endereço onde a habilidade será usada
 * \param now momento atual
 * \param last ultimo momento que a habilidade foi usada
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
        printf("OI\n");
        invalidate();
    }
}
