#include "fireball.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define FIREBALL_BASE_DAMAGE 20


using namespace std;
using namespace ijengine;


Fireball::Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx,
    double dy)
    : Skill(parent, xp, yp, FIREBALL_BASE_DAMAGE, mage_id), m_character_id(mage_id), m_dx(dx/hypot(dx, dy)),
        m_dy(dy/hypot(dx, dy)), m_speed(100.0) 
{
    m_frame = 0;
    m_start = 0;
    m_sprite_path = choose_sprite_path(mage_id);

    m_texture = ijengine::resources::get_texture(m_sprite_path);
    m_x = xp;
    m_y = yp;
    m_bounding_box = Rectangle(m_x, m_y, 20, 20);

    if(m_dx > 0) {
        m_state = MOVING_LEFT;
    }
    else {
        m_state = MOVING_RIGHT;
    }
}

Fireball::~Fireball()
{

}

void
Fireball::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) 32 * m_frame, (double) 32 * m_state, 32.00, 32.00};
    canvas->draw(m_texture.get(),rect, x(), y()); 
}

void
Fireball::update_self(unsigned now, unsigned last)
{
    update_time(now);

    if(m_current_time - m_start > 300) {
        double new_y = y() + m_dy *  m_speed * (now - last) / 1000.0;
        double new_x = x() + m_dx *  m_speed * (now - last) / 1000.0;
        set_position(new_x, new_y);

        m_bounding_box.set_position(x(), y());
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
    return m_bounding_box;
}

const list<Rectangle>&
Fireball::hit_boxes() const {
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

pair<double, double>
Fireball::direction() const
{
    return pair<double, double>(m_dx, m_dy);
}

void
Fireball::update_sprite_state()
{
    if(m_current_time - m_start < 300) {
        m_frame = (m_frame + 1) % (m_texture->w() / 32);
    }

    else if(m_current_time - m_start > 300) {
        m_frame = (m_frame + 1) % (m_texture->w() / 32);

        if(m_frame >= 5){
            m_frame = 2;
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
    if(m_start == 0) {
        m_start = now;
        m_current_time = now;
    }

    if (now - m_current_time > 150)
    {
        m_current_time += 150;
        update_sprite_state();
    }

    if((m_current_time - m_start) > 2000) {
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