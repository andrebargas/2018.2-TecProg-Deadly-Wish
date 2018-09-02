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
    FrostNova(GameObject *parent, unsigned mage_id, double xp, double yp,
        double dx, double dy);



    ~FrostNova();
    bool Active() const;
    const Rectangle& BoundingBox() const;
    const list<Rectangle>& HitBoxes() const;
    pair<double, double> Direction() const;
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);

protected:
    void UpdateSelf(unsigned now, unsigned last);
    void DrawSelf(Canvas *canvas, unsigned, unsigned);
    void UpdateSprite_state();
    void UpdateTime(unsigned now);
    string ChooseSpritePath(unsigned player_id);

    unsigned character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { CASTING, MOVING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    State state;
    SpriteState sprite_state;
    double attack_distance_x, attack_distance_y;
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
