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
    Spear(GameObject *parent, unsigned soldier_id, double xp, double yp,
          double dx, double dy);

    ~Spear();

    //metodos virtual de Collidable
    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    pair<double, double> direction() const;

protected:
    //metodos virtual de GameObject
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned, unsigned);

    //Metodo de Spear
    void update_sprite_state();
    void update_time(unsigned now);
    string choose_sprite_path(unsigned player_id);

    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { THROW, MOVING, FALLING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;

    unsigned spear_character_id;
    State spear_state;
    SpriteState spear_sprite_state;
    double spear_axis_x_direction;
    double spear_axis_y_direction;
    int spear_damage;
    double spear_speed;
    int spear_frame;
    string spear_sprite_path;
    unsigned spear_start;
    unsigned spear_current_time;
    shared_ptr<Texture> spear_texture;
    Rectangle spear_bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif
