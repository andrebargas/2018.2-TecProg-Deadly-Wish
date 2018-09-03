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
	Character(const vector<string> sprite_paths, unsigned new_character_id, double position_axis_x,
		 				double position_axis_y, int max_life, int character_code);
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


    virtual bool is_active() const;
    const Rectangle& get_bounding_box() const;
    const list<Rectangle>& hit_boxes() const;

    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    pair<double, double> get_direction() const;

    unsigned get_id() const { return id; }
    int get_number_of_lives() const { return number_of_lives; }

    void set_base(Base *base);

protected:
    void UpdateSelf(unsigned now, unsigned last);
    void DrawSelf(Canvas *canvas, unsigned now, unsigned last);
    void ChangeCharacterState(State next_state, bool respawning = false);
    void handle_state();
    void set_spawn_position();
    void respawn_character();
    void kill_character();
    string ChooseSpritePath(unsigned player_id);
    bool on_event(const GameEvent& event);
    virtual void HeavyAttack() = 0;
    virtual void LightAttack() = 0;
    virtual void Defense() = 0;
    virtual void Special() = 0;

    typedef enum {MOVING_RIGHT, MOVING_LEFT} MovingState;



protected:
    MovingState moving_state;
    CharacterState* state;
    CharacterStateFactory character_state_factory;
    bool active;
    unsigned id;
    int max_life;
    int current_life;
    int number_of_lives;
    int frame;
    int start;
    int width;
    int height;
    int heavy_attack_cooldown;
    int light_attack_cooldown;
    int defense_cooldown;
    int special_cooldown;
    int last_used_heavy_attack;
    int last_used_light_attack;
    int last_used_defense;
    int last_used_special;
    int respawn_time;
    int character_code;
    int last_sound_played;
    bool freeze;
    bool dead;
    double axis_x_speed;
    double axis_y_speed;
    double speed;
    Base* base;
    vector< shared_ptr<Texture> > textures;
    unordered_map<string, pair<double, double> > speed_vector;
    Rectangle bounding_box;
    vector<string> sprite_paths;
    inline void UpdatePosition(const unsigned &now, const unsigned &last, bool backwards = false);
};

#endif
