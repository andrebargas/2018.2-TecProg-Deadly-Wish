#ifndef BASE_H
#define BASE_H

#include <ijengine/game_object.h>
#include <ijengine/texture.h>
#include <ijengine/collidable.h>
#include <ijengine/rectangle.h>

#include "util.h"

#include <memory>
#include <vector>
#include <string>
#include <utility>

using std::shared_ptr;
using std::vector;
using std::string;
using std::pair;

using namespace ijengine;
using namespace util;

class Base : public GameObject, public Collidable {
public:
    //contrutor e destrutor de Base
    Base(int player_id);
    ~Base();

    unsigned get_base_player_id() const { return base_player_id; }
    int get_base_life() const {return base_life;}
    void set_base_status(int base_status);

    //metodos virtual de Collidable
    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    pair<double, double> direction() const;


protected:
    void set_base_position(unsigned player_id, double& x_pos, double& y_pos);
    void change_base_status();

    //metodos virtual de GameObject
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);


protected:
    unsigned base_player_id;
    int base_life;
    int base_frame;
    int base_start;
    int base_width;
    int base_height;
    int base_status;
    vector <string> base_sprite_paths;
    shared_ptr<Texture> base_texture;
    Rectangle base_bounding_box;
    double base_axis_x_speed;
    double base_axis_y_speed;

};

#endif
