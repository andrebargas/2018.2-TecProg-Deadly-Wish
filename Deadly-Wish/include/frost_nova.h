#ifndef FROST_NOVA_H
#define FROST_NOVA_H

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

class FrostNova : public Skill {
public:
    FrostNova(GameObject *parent, unsigned hero_id, double x_position, double y_position,
        double x_direction, double y_direction);

    ~FrostNova();
    bool is_active() const;
    const Rectangle& get_bounding_box() const;
    const list<Rectangle>& get_hit_boxes() const;
    pair<double, double> get_direction() const;
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now_moment, unsigned last_moment);

protected:
    void update_self(unsigned now_moment, unsigned last_moment);
    void draw_self(Canvas *canvas, unsigned, unsigned);
    void update_sprite_state();
    void update_time(unsigned now_moment);
    string choose_sprite_path(unsigned player_id);

    unsigned character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { CASTING, MOVING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    State state;
    SpriteState sprite_state;
    double skill_x_direction, skill_y_direction;
    double x_position_frost_nova, y_position_frost_nova;
    int new_skill_damage;
    double speed_attack;
    int frame;
    string sprite_path;
    unsigned start;
    unsigned current_time;
    shared_ptr<Texture> texture;
    Rectangle bounding_box;

//    bool on_event(const GameEvent& event);
};

#endif
