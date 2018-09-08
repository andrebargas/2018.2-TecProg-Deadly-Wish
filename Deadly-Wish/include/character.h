#ifndef CHARACTER_H
#define CHARACTER_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/collidable.h>
#include <ijengine/rectangle.h>
#include <ijengine/event.h>

#include "character_state.h"
#include "character_state_factory.h"
#include "util.h"
#include "base.h"

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::vector;
using std::pair;
using std::string;
using std::unordered_map;
using namespace ijengine;
using namespace util;


class Character : public GameObject, public GameEventsListener, public Collidable {
public:
	Character(const vector<string> sprite_paths, unsigned id, double x, double y, int max_life, int character_code);
	~Character();

    enum {
        KNIGHT,
        SOLDIER,
        MAGE,
        INFILTRATOR
    };

    enum {
        START_MOVING_DOWN,
        START_MOVING_LEFT,
        START_MOVING_RIGHT,
        START_MOVING_UP,
        STOP_MOVING_DOWN,
        STOP_MOVING_LEFT,
        STOP_MOVING_RIGHT,
        STOP_MOVING_UP,
        LIGHT_ATTACK,
        HEAVY_ATTACK,
        DEFENSE,
        SPECIAL,
        NUMBER_OF_CHARACTER_EVENTS
    };

		//metodos de collidable
    virtual bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
		void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
		pair<double, double> direction() const;


    unsigned get_id() const { return character_id; }
    int get_number_of_lives() const { return character_number_of_lives; }
    void set_base(Base *base);

protected:
    void change_character_state(State next_state, bool respawning = false);
    void handle_state();
    void set_spawn_position();
    void respawn_character();
    void kill_character();
    string choose_sprite_path(unsigned player_id);
    bool on_event(const GameEvent& event);
    virtual void do_heavy_attack() = 0;
    virtual void do_light_attack() = 0;
    virtual void do_defense() = 0;
    virtual void do_special() = 0;

    typedef enum {MOVING_RIGHT, MOVING_LEFT} MovingState;
		//metodos virtual de gameobject
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);


protected:
    MovingState character_moving_state;
    CharacterState* character_state;
    CharacterStateFactory new_character_state_factory;
    bool character_active;
    unsigned character_id;
    int character_max_life;
    int character_current_life;
    int character_number_of_lives;
    int character_frame;
    int character_start;
    int character_width;
    int character_height;
    int character_heavy_attack_cooldown;
    int character_light_attack_cooldown;
    int character_defense_cooldown;
    int character_special_cooldown;
    int character_last_used_heavy_attack;
    int character_last_used_light_attack;
    int character_last_used_defense;
    int character_last_used_special;
    int character_respawn_time;
    int character_code;
    int character_last_sound_played;
    bool character_freeze;
    bool character_dead;
    double character_axis_x_speed;
    double character_axis_y_speed;
    double character_speed;
    Base* character_base;
    vector< shared_ptr<Texture> > character_textures;
    unordered_map<string, pair<double, double> > character_speed_vector;
    Rectangle character_bounding_box;
    vector<string> character_sprite_paths;

    inline void update_position(const unsigned &now, const unsigned &last, bool backwards = false);
};

#endif
