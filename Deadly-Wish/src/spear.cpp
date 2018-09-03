#include "spear.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define SPEAR_BASE_DAMAGE 20

using namespace std;
using namespace ijengine;


Spear::Spear(GameObject *parent, unsigned soldier_id, double xp, double yp, double dx,
    double dy)
    : Skill(parent, xp, yp, SPEAR_BASE_DAMAGE, soldier_id), character_id(soldier_id), m_dx(dx/hypot(dx, dy)),
        m_dy(dy/hypot(dx, dy)), speed(100.0) 
{
    frame = 0;
    start = 0;
    sprite_path = ChooseSpritePath(soldier_id);
    texture = ijengine::resources::get_texture(sprite_path);
    m_x = xp;
    m_y = yp;
    bounding_box = Rectangle(m_x, m_y, 20, 20);


    if(m_dx > 0) {
        state = MOVING_LEFT;
    }
    else {
        state = MOVING_RIGHT;
    }
}

Spear::~Spear() {//M1
}

void Spear::DrawSelf(Canvas *canvas, unsigned, unsigned) {//M1
    Rectangle rect {(double) 32 * frame, (double) 32 * state, 32.00, 32.00};
    canvas->draw(texture.get(),rect, x(), y()); 
}

void
Spear::UpdateSelf(unsigned now, unsigned last)
{
    UpdateTime(now);
    if(current_time - start > 70){
        double new_y = y() + m_dy *  speed * (now - last) / 1000.0;
        double new_x = x() + m_dx *  speed * (now - last) / 1000.0;
        set_position(new_x, new_y);

        bounding_box.set_position(x(), y());
    }
}

bool
Spear::active() const
{
    return true;
}

const Rectangle& 
Spear::BoundingBox() const
{
    return bounding_box;
}

const list<Rectangle>&
Spear::hit_boxes() const {
    static list<Rectangle> boxes {bounding_box};
    return boxes;
}

pair<double, double>
Spear::direction() const
{
    return pair<double, double>(m_dx, m_dy);
}

void
Spear::UpdateSpriteState()
{
    if(current_time - start < 70) {
        frame = (frame + 1) % (texture->w() / 32);
    }

    else if(current_time - start > 70 ) {
        frame = 3;
    }
}

void
Spear::UpdateTime(unsigned now) 
{
    if(start == 0) {
        start = now;
        current_time = now;
    }

    if (now - current_time > 35)
    {
        current_time += 35;
        UpdateSpriteState();
    }

    if((current_time - start) > 2000) {
        invalidate();
    }

}

string
Spear::ChooseSpritePath(unsigned player_id)
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