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
    bool Active() const;
    const Rectangle& BoundingBox() const;
    const list<Rectangle>& HitBoxes() const;
    pair<double, double> Direction() const;

protected:
    void UpdateSelf(unsigned now, unsigned last);
    void DrawSelf(Canvas *canvas, unsigned, unsigned);
    void UpdateSprite_state();
    void UpdateTime(unsigned now);
    string choose_sprite_path(unsigned player_id);

    unsigned character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { CASTING, MOVING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    State m_state;
    SpriteState sprite_state;
    double m_dx, m_dy;
    int damage;
    double speed;
    int frame;
    string sprite_path;
    unsigned start;
    unsigned current_time;
    shared_ptr<Texture> m_texture;
    Rectangle bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif
