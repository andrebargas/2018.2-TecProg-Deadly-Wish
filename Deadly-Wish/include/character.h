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
#include <assert.h>

using std::shared_ptr;
using std::vector;
using std::pair;
using std::string;
using std::unordered_map;
using namespace ijengine;
using namespace util;

//! Class that describes the character in general
/*! Allows the character to have defense and attack powers,
active character or not and their positions in the x and y axes
\param sprite paths indicates the vector that detaches the character
\param id indicates the identified character
\param x indicates the x position of the character
\param and indicates the y position of the character
\param max_life indicates the maximum life of the character
\param character_Code indicates the character code
*/
class Character : public GameObject, public GameEventsListener, public Collidable {
public:
	Character(const vector<string> sprite_paths, unsigned id, double x, double y, int max_life, int character_code);
	~Character();

//! Enumerated with the possible characters
    enum 
    {
        KNIGHT, 
        SOLDIER,
        MAGE,
        INFILTRATOR
    };

//! Listed with possible events
    enum 
    {
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


    //! Virtual Collision Methods
    virtual bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    pair<double, double> direction() const;


    //! Method that returns the character identifier
    unsigned get_id() const { 
        assert(character_id >= 1 && character_id <= 4);
        return character_id; 
    }


    //! Method that returns the number of lives of the character
    int get_number_of_lives() const { 
        assert(character_number_of_lives >= 0);
        return character_number_of_lives; 
    }

    //! Method that puts the bases with their proper characters
    void set_base(Base *base);


//!Protected methods
protected:

//! Method that changes character status
    /*
     \param next_state is an object that indicates the next state of the character
     \param bool respawing is a variable that indicates the reappearance of the character
     */
    void change_character_state(State next_state, bool respawning = false);
    //! Method that handles the state
    void handle_state();
    //! Method that defines where the character will be "spawned"
    void set_spawn_position();
    //! Method that allows the reappearance of the character
    void respawn_character();
    //! Method that defines whether the character was killed
    void kill_character();
     //! Package that draws the character
     /*
     \ param player_id show the identifier of each character
     */
    string choose_sprite_path(unsigned player_id);
    //! Method that returns the events in general
    bool on_event(const GameEvent& event);
    //! Virtual Attack Special Method
    virtual void do_heavy_attack() = 0;
    //! Virtual attack method ligth_atack
    virtual void do_light_attack() = 0;
    //! Virtual defense method
    virtual void do_defense() = 0;
    //! Virtual Attack Special Method
    virtual void do_special() = 0;

    //! Enuemrado that defines the type of movement
    typedef enum 
    {
        MOVING_RIGHT, 
        MOVING_LEFT

    } MovingState;

		//! virtual methods of gameobject
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);


protected:
    //! Character movement status
    MovingState character_moving_state;
    //! State of character
    CharacterState* character_state;
    //! Building the character
    CharacterStateFactory new_character_state_factory;
    //! variable that indicates whether the character is active
    bool character_active;
    //! variable that serves to identify the character
    unsigned character_id;
    //! variable that indicates the maximum life of each character
    int character_max_life;
    //! variable that indicates the current life of each character
    int character_current_life;
    //! variable that indicates the number of lives
    int character_number_of_lives;
    //! variable that indicates character frame
    int character_frame;
    //! variable that indicates that the character has been started
    int character_start;
    //! variable that indicates the width of the character
    int character_width;
    //! variable that indicates the height of the character
    int character_height;
    //! variable that indicates the character's heavy attack
    int character_heavy_attack_cooldown;
    //! variable indicating light character attack
    int character_light_attack_cooldown;
    //! variable that indicates character defense
    int character_defense_cooldown;
    //! variable that indicates the character's special attack
    int character_special_cooldown;
    //! variables that indicate the last use of the attacks and defenses
    int character_last_used_heavy_attack;
    int character_last_used_light_attack;
    int character_last_used_defense;
    int character_last_used_special;
    //! variable indicating the reappearance time
    int character_respawn_time;
    //! variable that indicates character code
    int character_code;
    //! variable that indicates the last sound that was played
    int character_last_sound_played;
    //! variable that indicates the freezing of the character
    bool character_freeze;
    //! dead or alive character
    bool character_dead;
    //! speed on the x axis
    double character_axis_x_speed;
    //! speed on the y-axis
    double character_axis_y_speed;
    //! variable that indicates the speed of the character
    double character_speed;
    //! variable indicating base of character
    Base* character_base;
    vector< shared_ptr<Texture> > character_textures;
    unordered_map<string, pair<double, double> > character_speed_vector;
    Rectangle character_bounding_box;
    vector<string> character_sprite_paths;

// Method that indicates that character update will update
/*
\param now indicates the current time
\param last indicates the last event
\param backwards indicates the previous position
*/ 

    inline void update_position(const unsigned &now, const unsigned &last, bool backwards = false);
};

#endif
