#include "fireball.h"
#include "character.h"
#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define FIREBALL_BASE_DAMAGE 20
#define HEIGHT_RECTANGLE 20
#define WIDTH_RECTANGLE 20
#define SPEED 100.0



using namespace std;
using namespace ijengine;

Fireball::Fireball(GameObject *parent, unsigned mage_id, 
double axis_position_x, double axis_position_y, double dx, double dy)
    : Skill(parent, axis_position_x, axis_position_y, FIREBALL_BASE_DAMAGE, mage_id), 
    character_id(mage_id), m_dx(dx/hypot(dx, dy)), m_dy(dy/hypot(dx, dy)), speed(SPEED) {

    frame = 0;
    start = 0;
    sprite_path = ChooseSpritePath(mage_id);

    texture = ijengine::resources::get_texture(sprite_path);
    m_x = axis_position_x;
    m_y = axis_position_y;
    bounding_box = Rectangle(m_x, m_y, WIDTH_RECTANGLE, HEIGHT_RECTANGLE);
    if(m_dx > 0) {
        state = MOVING_LEFT;
    }
    else {
        state = MOVING_RIGHT;
    }
}

Fireball::~Fireball() {
}

void
Fireball::DrawSelf(Canvas *canvas, unsigned, unsigned) {

    Rectangle rect {(double) 32 * frame, (double) 32 * state, 32.00, 32.00};
    canvas->draw(texture.get(),rect, x(), y()); 
}

void Fireball::UpdateSelf(unsigned actual_position_time, unsigned last_position_time) {
    UpdateTime(actual_position_time);

    if(current_time - start > 300) {

        double new_y_coordinate = 
        y() + m_dy *  speed * (actual_position_time - last_position_time) / 1000.0;

        double new_x_coordinate = 
        x() + m_dx *  speed * (actual_position_time - last_position_time) / 1000.0;

        set_position(new_x_coordinate, new_y_coordinate);

        bounding_box.set_position(x(), y());
    }
}

bool Fireball::Active() const {
    return true;
}

const Rectangle& Fireball::Bounding_box() const {
    return bounding_box;
}

const list<Rectangle>& Fireball::hit_boxes() const {
    static list<Rectangle> boxes {
        bounding_box
        };
    return boxes;
}

pair<double, double> Fireball::direction() const {
    return pair<double, double>(m_dx, m_dy);
}

void Fireball::UpdateSpriteState() {

    if(current_time - start < 300) {
        frame = (frame + 1) % (texture->w() / 32);
    }

    else if(current_time - start > 300) {
        frame = (frame + 1) % (texture->w() / 32);

        if(frame >= 5){
            frame = 2;
        }
    }

  //  else if(current_time < -1) {
  //      frame = 5;
  //  }
}

void Fireball::UpdateTime(unsigned actual_position_time) {
    // if it's the first update self
    if(start == 0) {
        start = actual_position_time;
        current_time = actual_position_time;
    }

    if (actual_position_time - current_time > 150) {
        current_time += 150;
        UpdateSpriteState();
    }

    if((current_time - start) > 2000) {
        invalidate();
    }

}

string Fireball::ChooseSpritePath(unsigned player_id) {

    string color_identifier = "Green";

    switch(player_id) {
        case PLAYER_1:
            color_identifier = "Green";
        break;

        case PLAYER_2:
            color_identifier = "Blue";
        break;

        case PLAYER_3:
            color_identifier = "Yellow";
        break;

        case PLAYER_4:
            color_identifier = "Red";
        break;

        default:
            printf("Valor inválido na Spear\n");
        break;
    }

    string sprite_path;//M4
    sprite_path = "Spritesheets/" + color_identifier + "/ObjectHadouken" + color_identifier + ".png";

    return sprite_path;
}