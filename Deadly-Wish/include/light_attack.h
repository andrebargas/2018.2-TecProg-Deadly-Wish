#ifndef LIGHT_ATTACK_H
#define LIGHT_ATTACK_H

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

class LightAttack : public Skill {
public:
    LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp);

    ~LightAttack();
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

    unsigned m_character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { CASTING, MOVING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    State m_state;
    SpriteState m_sprite_state;
    double m_dx, m_dy;
    int m_damage;
    double m_speed;
    int m_frame;
    string m_sprite_path;
    unsigned m_start;
    unsigned m_current_time;
    shared_ptr<Texture> m_texture;
    Rectangle m_bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif
