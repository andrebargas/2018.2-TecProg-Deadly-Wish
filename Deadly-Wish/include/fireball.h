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
	Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx, double dy);



    ~Fireball();
    bool Active() const;
    const Rectangle& Bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    pair<double, double> direction() const;

protected:
    void UpdateSelf(unsigned actual_position_time, unsigned last_position_time);
    void DrawSelf(Canvas *canvas, unsigned, unsigned);
    void UpdateSpriteState();
    void UpdateTime(unsigned now);
    string ChooseSpritePath(unsigned player_id);
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
    double m_dx, m_dy;
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
