/** \file fireball.cpp
  * \brief Este é o arquivo da classe Fireball, uma habilidade
  * do Character Mage, com herança da classe Skill
  */
#include "fireball.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define FIREBALL_BASE_DAMAGE 20
#define FIREBALL_WIDTH 32


using namespace std;
using namespace ijengine;


Fireball::Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx,
    double dy)
    : Skill(parent, xp, yp, FIREBALL_BASE_DAMAGE, mage_id), fireball_character_id(mage_id),
            fireball_axis_x_direction(dx/hypot(dx, dy)),
            fireball_axis_y_direction(dy/hypot(dx, dy)), fireball_speed(100.0)
{
    fireball_frame = 0;
    fireball_start = 0;
    fireball_sprite_path = choose_sprite_path(mage_id);
    fireball_texture = ijengine::resources::get_texture(fireball_sprite_path);
    fireball_bounding_box = Rectangle(m_x, m_y, 20, 20);

    //Atributos de GameObject
    fireball_axis_x_direction = xp;
    fireball_axis_y_direction = yp;

    if(fireball_axis_x_direction > 0) {
        fireball_state = MOVING_LEFT;
    }
    else {
        fireball_state = MOVING_RIGHT;
    }
}

Fireball::~Fireball()
{

}

void
Fireball::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double)FIREBALL_WIDTH * fireball_frame,
                    (double)FIREBALL_WIDTH * fireball_state,
                    (double)FIREBALL_WIDTH, (double)FIREBALL_WIDTH};

    canvas->draw(fireball_texture.get(),rect, x(), y());
}

void
Fireball::update_self(unsigned now, unsigned last)
{
    update_time(now);

    if(fireball_current_time - fireball_start > 300) {
        double new_y = y() + fireball_axis_y_direction *  fireball_speed * (now - last) / 1000.0;
        double new_x = x() + fireball_axis_x_direction *  fireball_speed * (now - last) / 1000.0;
        set_position(new_x, new_y);

        fireball_bounding_box.set_position(x(), y());
    }
}

bool
Fireball::active() const
{
    return true;
}

const Rectangle&
Fireball::bounding_box() const
{
    return fireball_bounding_box;
}

const list<Rectangle>&
Fireball::hit_boxes() const {
    static list<Rectangle> boxes {fireball_bounding_box};
    return boxes;
}

pair<double, double>
Fireball::direction() const
{
    return pair<double, double>(fireball_axis_x_direction, fireball_axis_y_direction);
}

void
Fireball::update_sprite_state()
{
    if(fireball_current_time - fireball_start < 300) {
        fireball_frame = (fireball_frame + 1) % (fireball_texture->w() / FIREBALL_WIDTH);
    }

    else if(fireball_current_time - fireball_start > 300) {
        fireball_frame = (fireball_frame + 1) % (fireball_texture->w() / FIREBALL_WIDTH);

        if(fireball_frame >= 5){
            fireball_frame = 2;
        }
    }

  //  else if(m_current_time < -1) {
  //      m_frame = 5;
  //  }
}

void
Fireball::update_time(unsigned now)
{
    // if it's the first update self
    if(fireball_start == 0) {
        fireball_start = now;
        fireball_current_time = now;
    }

    if (now - fireball_current_time > 150)
    {
        fireball_current_time += 150;
        update_sprite_state();
    }

    if((fireball_current_time - fireball_start) > 2000) {
        invalidate();
    }

}

string
Fireball::choose_sprite_path(unsigned player_id)
{
    string directory = "Green";
    string sprite_path;

    switch(player_id) {
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

    sprite_path = "Spritesheets/" + directory + "/ObjectHadouken" + directory + ".png";

    return sprite_path;
}
