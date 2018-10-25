/** \file spear.h
  * \brief This is a Spear class, which displays the spear (spear) of the soldier character, inherits from the Skill class.
  */
#include "spear.h"
#include "character.h"
#include "assert.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

//! Damage Value SPEAR_BASE_DAMAGE
#define SPEAR_BASE_DAMAGE 20
//! Width SPEAR
#define SPEAR_WIDTH 32

using namespace std;
using namespace ijengine;

/** fn LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp)
 * \public
 * \breif Builder Method LightAttack
 * \param *parent Pointer to GameObject
 * \param soldier_id soldier character identifier
 * \param xp double X axis position
 * \param yp double Y axis position
 */
Spear::Spear(GameObject *parent, unsigned soldier_id, double xp, double yp, double dx,
             double dy)
    : Skill(parent, xp, yp, SPEAR_BASE_DAMAGE, soldier_id), spear_character_id(soldier_id),
      spear_axis_x_direction(dx / hypot(dx, dy)), spear_axis_y_direction(dy / hypot(dx, dy)),
      spear_speed(100.0)
{
    assert(parent != nullptr);
    assert(soldier_id >= 1 && soldier_id <= 4);
    assert(xp != NULL);
    assert(yp != NULL);
    assert(dx != NULL);
    assert(dy != NULL);
    spear_frame = 0;
    assert(spear_frame != NULL);
    spear_start = 0;
    assert(spear_frame != NULL);
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

//! LightAttack Class Destructor
Spear::~Spear()
{
}

//! gameobject Virtual methods
void Spear::draw_self(Canvas *canvas, unsigned, unsigned)
{
    assert(canvas != NULL);
    assert(SPEAR_WIDTH == 32);
    Rectangle rect{(double)SPEAR_WIDTH * spear_frame, (double)SPEAR_WIDTH * spear_state,
                   (double)SPEAR_WIDTH, (double)SPEAR_WIDTH};
    canvas->draw(spear_texture.get(), rect, x(), y());
}

//! Spear update methods
/*!
\param update now(now update)
\param update last(last update)
*/
void Spear::update_self(unsigned now, unsigned last)
{
    assert(now != NULL);
    assert(last != NULL);

    update_time(now);
    if (spear_current_time - spear_start > 70)
    {
        double new_y = y() + spear_axis_y_direction * spear_speed * (now - last) / 1000.0;
        double new_x = x() + spear_axis_x_direction * spear_speed * (now - last) / 1000.0;
        assert(new_y !=NULL);
        assert(new_x !=NULL);
        set_position(new_x, new_y);
        

        spear_bounding_box.set_position(x(), y());
    }
}

//! Spear active
bool Spear::active() const
{
    return true;
}

//! Spear Delimitation
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

//! Spear direction
pair<double, double>
Spear::direction() const
{
    return pair<double, double>(spear_axis_x_direction, spear_axis_y_direction);
}

/** \fn string update_sprite_state()
  * \protected
  * \brief Function updates sprite_state using SPEAR_WIDTH.
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
  * \brief Spear time update.
  */
void Spear::update_time(unsigned now)
{
    assert(now > 0);
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
  * \Function that chooses which will be the way to the sprite of 
  * each of the players and character.
  * \param player unsigned player ID.
  * \return sprite_path images path.
  */
string
Spear::choose_sprite_path(unsigned player_id)
{
    string directory = "Green";
    string sprite_path;

    // Switch aassign the variable directory using variable player_id
    assert(player_id == PLAYER_1 || player_id == PLAYER_2 || player_id == PLAYER_3 || player_id == PLAYER_4);
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
