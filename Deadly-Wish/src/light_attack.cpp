/** \file light_attack.h
  * \brief Este é o arquivo da classe Light_Attack, com herança da classe Skill
  */
#include "light_attack.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

//! Valor Dano do LIGHT_ATTACK_BASE_DAMAGE
#define LIGHT_ATTACK_BASE_DAMAGE 10
//! Largurado LIGHT_ATTACK
#define LIGHT_ATTACK_WIDTH 10

using namespace std;
using namespace ijengine;

/** fn LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp)
 * \public
 * \breif Método Construtor LightAttack
 * \param *parent Ponteiro para o GameObject
 * \param mage_id
 * \param xp double posição no eixo X
 * \param yp double posição no eixo y
 */
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

//! Destrutor da Classe LightAttack
LightAttack::~LightAttack()
{
}

//! Métodos virtual de gameobject
void LightAttack::draw_self(Canvas *canvas, unsigned, unsigned)
{
}

//! Método que indica atualizar o LightAttack
/*!
\param now indica atualização agora
\param las indica a última atualizção
*/
void LightAttack::update_self(unsigned now, unsigned last)
{
    update_time(now);
}

//! LightAttack ativo
bool LightAttack::active() const
{
    return true;
}

//! Delimitação LightAttack
const Rectangle &
LightAttack::bounding_box() const
{
    return light_attack_bounding_box;
}

const list<Rectangle> &
LightAttack::hit_boxes() const
{
    static list<Rectangle> boxes{light_attack_bounding_box};
    return boxes;
}

//! Direção do LightAttack
pair<double, double>
LightAttack::direction() const
{
    return pair<double, double>(light_attack_axis_x_direction, light_attack_axis_y_direction);
}

//! Atualiza o LightAttack
void LightAttack::update_time(unsigned now)
{
    // Se for a primeira auto-atualização
    if (light_attack_start == 0)
    {
        light_attack_start = now;
        light_attack_current_time = now;
    }

    if ((now - light_attack_start) > 100)
    {
        invalidate();
    }
}
