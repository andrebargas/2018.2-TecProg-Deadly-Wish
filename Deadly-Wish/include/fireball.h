/** \file fireball.h
  * \brief Este é o arquivo header da classe Fireball, uma
	* habilidade do Character Mage, com herança da classe Skill
  */
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
	Fireball(GameObject *parent, unsigned mage_id, double xp, double yp,
        double dx, double dy);



    ~Fireball();
    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    pair<double, double> direction() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned, unsigned);
    void update_sprite_state();
    void update_time(unsigned now);
    string choose_sprite_path(unsigned player_id);

    unsigned fireball_character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { CASTING, MOVING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    State fireball_state;
    SpriteState fireball_sprite_state;
    double fireball_axis_x_direction, fireball_axis_y_direction;
    int fireball_damage;
    double fireball_speed;
    int fireball_frame;
    string fireball_sprite_path;
    unsigned fireball_start;
    unsigned fireball_current_time;
    shared_ptr<Texture> fireball_texture;
    Rectangle fireball_bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif
