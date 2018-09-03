#include "spear.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define SPEAR_BASE_DAMAGE 20

using namespace std;
using namespace ijengine;


Spear::Spear(GameObject *parent, unsigned soldier_id, double x_position, double y_position,
             double x_direction, double y_direction)
: Skill(parent, x_position, y_position, SPEAR_BASE_DAMAGE, soldier_id), character_id(soldier_id),
        axis_x_direction(x_direction/hypot(x_direction, y_direction)),
        axis_y_direction(y_direction/hypot(x_direction, y_direction)), speed(100.0) {

    frame = 0;
    start = 0;
    sprite_path = choose_sprite_path(soldier_id);
    texture = ijengine::resources::get_texture(m_sprite_path);
    // m_x e m_y nao podem ser mudadas por serem protegidas pelo scopo do projeto
    m_x = x_position;
    m_y = y_position;
    get_bounding_box = Rectangle(m_x, m_y, 20, 20);


    if(asis_x_direction > 0) {
        state = MOVING_LEFT;
    }
    else {
        state = MOVING_RIGHT;
    }
}

Spear::~Spear()
{

}

void Spear::draw_self(Canvas *canvas, unsigned, unsigned) {

    Rectangle rect {(double) 32 * frame, (double) 32 * state, 32.00, 32.00};
    canvas->draw(m_texture.get(),rect, x(), y());
}

void Spear::update_self(unsigned now, unsigned last) {

    update_time(now);
    if(current_time - start > 70){
        double new_y = y() + axis_y_direction *  speed * (now - last) / 1000.0;
        double new_x = x() + axis_x_direction *  speed * (now - last) / 1000.0;
        set_position(new_x, new_y);

        bounding_box.set_position(x(), y());
    }
}

bool Spear::is_active() const {

    return true;
}

const Rectangle& Spear::get_bounding_box() const {

    return bounding_box;
}

const list<Rectangle>& Spear::get_hit_boxes() const {

    static list<Rectangle> boxes {bounding_box};
    return boxes;
}

pair<double, double> Spear::get_direction() const{

    return pair<double, double>(axis_x_direction, axis_y_direction);
}

void Spear::update_sprite_state(){

    if(current_time - start < 70) {
        frame = (frame + 1) % (texture->w() / 32);
    }

    else if(current_time - start > 70 ) {
        frame = 3;
    }
}

void Spear::update_time(unsigned now) {

    if(start == 0) {
        start = now;
        current_time = now;
    }

    if (now - current_time > 35)
    {
        current_time += 35;
        update_sprite_state();
    }

    if((current_time - start) > 2000) {
        invalidate();
    }

}

string Spear::choose_sprite_path(unsigned player_id) {
  
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
