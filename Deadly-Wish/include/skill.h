#ifndef SKILL_H
#define SKILL_H

#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>

using namespace ijengine;

class Skill : public GameObject, public Collidable  {
public:
    Skill(GameObject *parent, double axis_position_x, double axis_position_y, int damage, int character_id);
    ~Skill();

    virtual bool active() const = 0;
    virtual const Rectangle& get_bounding_box() const = 0;
    virtual const list<Rectangle>& get_hit_boxes() const = 0;
    virtual pair<double, double> direction() const = 0;

    virtual void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    unsigned get_character_id() const { return character_id; }
    int get_damage() const { return damage; }
    int get_collided() const {return skill_collided;}
protected:
    unsigned character_id;
    int damage;
    double skill_speed;
    int skill_collided;

};

#endif
