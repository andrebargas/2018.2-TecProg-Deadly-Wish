#include "spear.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define SPEAR_BASE_DAMAGE 20
#define SPEAR_WIDTH 32

using namespace std;
using namespace ijengine;


Spear::Spear(GameObject *parent, unsigned soldier_id, double xp, double yp, double dx,
    double dy)
    : Skill(parent, xp, yp, SPEAR_BASE_DAMAGE, soldier_id), spear_character_id(soldier_id),
            spear_axis_x_direction(dx/hypot(dx, dy)), spear_axis_y_direction(dy/hypot(dx, dy)),
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



    if(spear_axis_x_direction > 0) {
        spear_state = MOVING_LEFT;
    }
    else {
        spear_state = MOVING_RIGHT;
    }
}

Spear::~Spear()
{

}

void
Spear::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) SPEAR_WIDTH * spear_frame, (double) SPEAR_WIDTH * spear_state,
                    (double) SPEAR_WIDTH, (double) SPEAR_WIDTH};
    canvas->draw(spear_texture.get(),rect, x(), y());
}

void
Spear::update_self(unsigned now, unsigned last)
{
    update_time(now);
    if(spear_current_time - spear_start > 70){
        double new_y = y() + spear_axis_y_direction *  spear_speed * (now - last) / 1000.0;
        double new_x = x() + spear_axis_x_direction *  spear_speed * (now - last) / 1000.0;
        set_position(new_x, new_y);

        spear_bounding_box.set_position(x(), y());
    }
}

bool
Spear::active() const
{
    return true;
}

const Rectangle&
Spear::bounding_box() const
{
    return spear_bounding_box;
}

const list<Rectangle>&
Spear::hit_boxes() const {
    static list<Rectangle> boxes {spear_bounding_box};
    return boxes;
}

pair<double, double>
Spear::direction() const
{
    return pair<double, double>(spear_axis_x_direction, spear_axis_y_direction);
}

void
Spear::update_sprite_state()
{
    if(spear_current_time - spear_start < 70) {
        spear_frame = (spear_frame + 1) % (spear_texture->w() / SPEAR_WIDTH);
    }

    else if(spear_current_time - spear_start > 70 ) {
        spear_frame = 3;
    }
}

void
Spear::update_time(unsigned now)
{
    if(spear_start == 0) {
        spear_start = now;
        spear_current_time = now;
    }

    if (now - spear_current_time > 35)
    {
        spear_current_time += 35;
        update_sprite_state();
    }

    if((spear_current_time - spear_start) > 2000) {
        invalidate();
    }

}

string
Spear::choose_sprite_path(unsigned player_id)
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

    sprite_path = "Spritesheets/" + directory + "/ObjectSpear" + directory + ".png";

    return sprite_path;
}
