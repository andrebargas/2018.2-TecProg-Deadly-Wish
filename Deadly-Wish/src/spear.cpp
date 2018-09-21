/** \file spear.h
  * \brief Este é o arquivo da classe Spear que exibe a spear(lança) do soldier, com herança da classe Skill
  */
#include "spear.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

//! Valor Dano do SPEAR_BASE_DAMAGE
#define SPEAR_BASE_DAMAGE 20
//! Largurado SPEAR(lança)
#define SPEAR_WIDTH 32

using namespace std;
using namespace ijengine;

/** fn LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp)
 * \public
 * \breif Método Construtor LightAttack
 * \param *parent Ponteiro para o GameObject
 * \param soldier_id identificador do personagem soldier
 * \param xp double posição no eixo X
 * \param yp double posição no eixo y
 */
Spear::Spear(GameObject *parent, unsigned soldier_id, double xp, double yp, double dx,
             double dy)
    : Skill(parent, xp, yp, SPEAR_BASE_DAMAGE, soldier_id), spear_character_id(soldier_id),
      spear_axis_x_direction(dx / hypot(dx, dy)), spear_axis_y_direction(dy / hypot(dx, dy)),
      spear_speed(100.0)
{
    spear_frame = 0;
    spear_start = 0;
    spear_sprite_path = choose_sprite_path(soldier_id);
    spear_texture = ijengine::resources::get_texture(spear_sprite_path);
    spear_bounding_box = Rectangle(m_x, m_y, 20, 20);

    //Game object atribute
    m_x = xp;
    m_y = yp;

    if (spear_axis_x_direction > 0)
    {
        spear_state = MOVING_LEFT;
    }
    else
    {
        spear_state = MOVING_RIGHT;
    }
}

//! Destrutor da Classe LightAttack
Spear::~Spear()
{
}

//! Métodos virtual de gameobject
void Spear::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect{(double)SPEAR_WIDTH * spear_frame, (double)SPEAR_WIDTH * spear_state,
                   (double)SPEAR_WIDTH, (double)SPEAR_WIDTH};
    canvas->draw(spear_texture.get(), rect, x(), y());
}

//! Método que indica atualizar o Spear
/*!
\param now indica atualização agora
\param las indica a última atualizção
*/
void Spear::update_self(unsigned now, unsigned last)
{
    update_time(now);
    if (spear_current_time - spear_start > 70)
    {
        double new_y = y() + spear_axis_y_direction * spear_speed * (now - last) / 1000.0;
        double new_x = x() + spear_axis_x_direction * spear_speed * (now - last) / 1000.0;
        set_position(new_x, new_y);

        spear_bounding_box.set_position(x(), y());
    }
}

//! Spear ativo
bool Spear::active() const
{
    return true;
}

//! Delimitação da Spear
const Rectangle &
Spear::bounding_box() const
{
    return spear_bounding_box;
}

const list<Rectangle> &
Spear::hit_boxes() const
{
    static list<Rectangle> boxes{spear_bounding_box};
    return boxes;
}

//! Direção da Spear
pair<double, double>
Spear::direction() const
{
    return pair<double, double>(spear_axis_x_direction, spear_axis_y_direction);
}

/** \fn string update_sprite_state()
  * \protected
  * \brief Função atualiza o sprite_state utilizando o SPEAR_WIDTH.
  */
void Spear::update_sprite_state()
{
    if (spear_current_time - spear_start < 70)
    {
        spear_frame = (spear_frame + 1) % (spear_texture->w() / SPEAR_WIDTH);
    }

    else if (spear_current_time - spear_start > 70)
    {
        spear_frame = 3;
    }
}

/** \fn string update_time()
  * \protected
  * \brief Função atualiza o tempo do spear.
  */
void Spear::update_time(unsigned now)
{
    if (spear_start == 0)
    {
        spear_start = now;
        spear_current_time = now;
    }

    if (now - spear_current_time > 35)
    {
        spear_current_time += 35;
        update_sprite_state();
    }

    if ((spear_current_time - spear_start) > 2000)
    {
        invalidate();
    }
}

/** \fn string choose_sprite_path(unsigned player_id)
  * \protected
  * \brief Função que escolhe qual sera o caminho para o sprite de cada um dos jogadores e
  *  personagem, ja as cores e densenhos de cada um são diferentes.
  * \param player unsigned Código de para o player
  * \return o sprite_path com o caminho das imagens.
  */
string
Spear::choose_sprite_path(unsigned player_id)
{
    string directory = "Green";
    string sprite_path;

    // Switch atribuir a variavel directory a partir da variavel player_id
    switch (player_id)
    {
    case PLAYER_1:
        directory = "Green";
        break;

    case PLAYER_2:
        directory = "Blue";
        break;

    case PLAYER_3:
        directory = "Yellow";
        break;

    case PLAYER_4:
        directory = "Red";
        break;

    default:
        printf("Valor inválido na Spear\n");
        break;
    }

    sprite_path = "Spritesheets/" + directory + "/ObjectSpear" + directory + ".png";

    return sprite_path;
}
