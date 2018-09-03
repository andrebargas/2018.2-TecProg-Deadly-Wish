#ifndef SPEAR_H
#define SPEAR_H

#include "skill.h"

#include <cmath>
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/color.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

using namespace std;
using namespace ijengine;

class Spear : public Skill {

public:
    Spear(GameObject *parent, unsigned soldier_id, double x_position, double y_position,
        double x_direction, double y_direction);

    ~Spear();
    bool is_active() const;
    const Rectangle& get_bounding_box() const;
    const list<Rectangle>& get_hit_boxes() const;
    pair<double, double> get_direction() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned, unsigned);
    void update_sprite_state();
    void update_time(unsigned now);
    string choose_sprite_path(unsigned player_id);

    unsigned character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { THROW, MOVING, FALLING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    State state;
    SpriteState prite_state;
    double axis_x_direction, axis_y_direction;
    int damage;
    double speed;
    int frame;
    string sprite_path;
    unsigned start;
    unsigned current_time;
    shared_ptr<Texture> texture;
    Rectangle bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif
