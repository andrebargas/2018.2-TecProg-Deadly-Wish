#ifndef FIREBALL_H
#define FIREBALL_H

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

class Fireball : public Skill {

public:
		Fireball(GameObject *parent, unsigned mage_id, double axis_position_x, double axis_position_y, double direction_x, double direction_y);
    ~Fireball();
    bool get_active() const;
    const Rectangle& get_bounding_box() const;
    const list<Rectangle>& get_hit_boxes() const;
    pair<double, double> get_direction() const;

protected:
    void update_self(unsigned actual_position_time, unsigned last_position_time);
    void draw_self(Canvas *canvas, unsigned, unsigned);
    void update_sprite_state();
    void update_time(unsigned now);
    string choose_sprite_path(unsigned player_id);
    unsigned character_id;

    typedef enum {
        MOVING_LEFT,
        MOVING_RIGHT
    } State;

    typedef enum {
        CASTING,
        MOVING,
        HITTING
    } SpriteState;

    typedef enum {
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4
    } Players;

    State state;
    SpriteState sprite_state;
    double direction_axis_x, direction_axis_y;

		// Damage desnecessario pois classe possui atributo igual
    int damage;
    double skill_speed;
    int frame;
    string sprite_path;
    unsigned start;
    unsigned current_time;
    shared_ptr<Texture> texture;
    Rectangle bounding_box;

//    bool on_event(const GameEvent& event);
};

#endif
