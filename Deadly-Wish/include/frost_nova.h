/** \file frost_nova.h
  * \brief Este é o arquivo header da classe FrostNova, uma
  * habilidade do Character Mage, com herança da classe Skill
  */
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

/** \class FrostNova frost_nova.h "include/frost_nova.h"
  * \brief Cria o GameObject FrostNova, controla sua posição e colisão, atualiza o sprite e o tempo
  */
class FrostNova : public Skill {
public:
    FrostNova(GameObject *parent, unsigned mage_id, double xp, double yp,
        double dx, double dy);
    ~FrostNova();

    // Metodos virtual de Collidable
    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    pair<double, double> direction() const;
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);

protected:

    // Metodos virtual de GameObject
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned, unsigned);

    // Metodos de FrostNova
    void update_sprite_state();
    void update_time(unsigned now);
    string choose_sprite_path(unsigned player_id);

    unsigned frost_character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { CASTING, MOVING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    State frost_state;
    SpriteState frost_sprite_state;
    double frost_axis_x_direction, frost_axis_y_direction;
    int frost_damage;
    double frost_speed;
    int frost_frame;
    string frost_sprite_path;
    unsigned frost_start;
    unsigned frost_current_time;
    shared_ptr<Texture> frost_texture;
    Rectangle frost_bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif
