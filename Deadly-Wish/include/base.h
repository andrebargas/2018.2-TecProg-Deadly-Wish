#ifndef BASE_H
#define BASE_H

#include <ijengine/game_object.h>
#include <ijengine/texture.h>
#include <ijengine/collidable.h>
#include <ijengine/rectangle.h>

#include "util.h"

#include <memory>
#include <vector>
#include <string>
#include <utility>

using std::shared_ptr;
using std::vector;
using std::string;
using std::pair;

using namespace ijengine;
using namespace util;

class Base : public GameObject, public Collidable {
public:
    Base(int player_id);
    ~Base();

    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    pair<double, double> direction() const;
    unsigned base_player_id() const { return m_player_id; }
    int life() const {return m_life;}
    void set_base_status(int base_status);
    
protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    void set_base_position(unsigned player_id, double& x_pos, double& y_pos);
    void change_base_status();
    

protected:
    unsigned m_player_id;
    int m_life;
    int frame;
    int m_start;
    int m_w;
    int m_h;
    int m_base_status;
    vector <string> m_sprite_paths;
    shared_ptr<Texture> m_texture;
    Rectangle bounding_box;
    double m_x_speed;
    double m_y_speed;

};

#endif