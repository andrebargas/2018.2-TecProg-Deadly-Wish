#include "fireball.h"
#include "character.h"
#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define FIREBALL_BASE_DAMAGE 20
#define HEIGHT_RECTANGLE 20
#define WIDTH_RECTANGLE 20
#define SPEED 100.0
#define UPDATE_SPRITE_TIME 300
#define UPDATE_SELF_TIME 1000
#define CHARACTER_WIDTH 32


using namespace std;
using namespace ijengine;

Fireball::Fireball(GameObject *parent, unsigned mage_id, double axis_position_x,
                   double axis_position_y, double direction_x, double direction_y)
: Skill(parent, axis_position_x, axis_position_y, FIREBALL_BASE_DAMAGE, mage_id),
        character_id(mage_id), direction_axis_x(direction_x/hypot(direction_x, direction_y)),
        direction_axis_y(direction_y/hypot(direction_x, direction_y)), skill_speed(SPEED) {

    frame = 0;
    start = 0;
    sprite_path = ChooseSpritePath(mage_id);
    texture = ijengine::resources::get_texture(sprite_path);

    /*
     *m_x e m_y are protected by project scope
     *
    */
    m_x = axis_position_x;
    m_y = axis_position_y;
    bounding_box = Rectangle(m_x, m_y, WIDTH_RECTANGLE, HEIGHT_RECTANGLE);
    if(direction_axis_x > 0) {
        state = MOVING_LEFT;
    }
    else {
        state = MOVING_RIGHT;
    }
}

Fireball::~Fireball() {
}

void Fireball::draw_self(Canvas *canvas, unsigned, unsigned) {

    Rectangle rect {(double) CHARACTER_WIDTH * frame, (double) CHARACTER_WIDTH * state,
                    (double) CHARACTER_WIDTH, (double) CHARACTER_WIDTH};
    canvas->draw(texture.get(),rect, x(), y());
}

void Fireball::update_self(unsigned actual_position_time, unsigned last_position_time) {
    UpdateTime(actual_position_time);

    if(current_time - start > UPDATE_SPRITE_TIME) {

        double new_y_coordinate =
        y() + direction_axis_y *  speed * (actual_position_time - last_position_time) / (double) UPDATE_SELF_TIME;

        double new_x_coordinate =
        x() + direction_axis_x *  speed * (actual_position_time - last_position_time) / (double) UPDATE_SELF_TIME;

        set_position(new_x_coordinate, new_y_coordinate);

        bounding_box.set_position(x(), y());
    }
}

bool Fireball::get_active() const {
    return true;
}

const Rectangle& Fireball::get_bounding_box() const {
    return bounding_box;
}

const list<Rectangle>& Fireball::get_hit_boxes() const {
    static list<Rectangle> boxes {
        bounding_box
        };
    return boxes;
}

pair<double, double> Fireball::get_direction() const {
    return pair<double, double>(direction_axis_x, direction_axis_y);
}

void Fireball::update_sprite_state() {

    if(current_time - start < UPDATE_SPRITE_TIME) {
        frame = (frame + 1) % (texture->w() / CHARACTER_WIDTH);
    }

    else if(current_time - start > UPDATE_SPRITE_TIME) {
        frame = (frame + 1) % (texture->w() / CHARACTER_WIDTH);

        if(frame >= 5){
            frame = 2;
        }
    }

  //  else if(current_time < -1) {
  //      frame = 5;
  //  }
}

void Fireball::update_time(unsigned actual_position_time) {
    // if it's the first update self
    if(start == 0) {
        start = actual_position_time;
        current_time = actual_position_time;
    }

    if (actual_position_time - current_time > 150) {
        current_time += 150;
        update_sprite_state();
    }

    if((current_time - start) > 2000) {
        invalidate();
    }

}

string Fireball::choose_sprite_path(unsigned player_id) {

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

    string sprite_path;
    sprite_path = "Spritesheets/" + color_identifier + "/ObjectHadouken" + color_identifier + ".png";

    return sprite_path;
}
