/**\file light_attack.h
  * \brief This is the header file of the Light_Attack class, inherited from the Skill class
  */
#ifndef LIGHT_ATTACK_H
#define LIGHT_ATTACK_H

#include "skill.h"

#include <cmath>

//! Includes game engine files
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

/**\class LightAttack light_attack.h "include / light_attack.h"
 * \brief Class that controls LightAttack indicates direction, speed, player,
 * with Skill class inheritance
 * \param * parent Pointer to GameObject
 * \param mage_id
 * \param xp position in x
 * \param yp position in y
 */
class LightAttack : public Skill
{
  public:
    /**\fn LightAttack (GameObject * parent, unsigned mage_id, double xp, double yp);
       * \public
       * \brief constructor method
       */
    LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp);

    /**\fn ~ LightAttack ()
      * \public
      * \brief destructor method
      */
    ~LightAttack();

    //! Virtual Collision Methods
    bool active() const;
    const Rectangle &bounding_box() const;
    const list<Rectangle> &hit_boxes() const;
    pair<double, double> direction() const;

  protected:
    /**\fn update_self (unsigned now, unsigned last)
      * \protected
      * \brief Function to update level start time, and set attribute
      * #winner_level_start. Name can not be changed because it is a method inherited from the parent class,
      * protected by project scope
      * \param now unsigned Current game time
      * \param last unsigned
      * \return void
      */
    void update_self(unsigned now, unsigned last);

    /**\fn draw_self (Canvas * canvas, unsigned now, unsigned last)
      * \protected
      * \brief Method that makes the graphic design of the game. Name can not be changed because it is a
      * method inherited from parent class, protected by project scope
      * \param canvas Canvas * Pointer to class object responsible for rendering the game.
      * \param now unsigned Current game time
      * \param last unsigned
      * \return void
      */
    void draw_self(Canvas *canvas, unsigned, unsigned);

    void update_sprite_state();
    void update_time(unsigned now);
    string choose_sprite_path(unsigned player_id);

    unsigned light_attack_character_id;

    //! enum to chose the LightAttack direction
    typedef enum
    {
      MOVING_LEFT,
      MOVING_RIGHT
    } State;

    //! struct with enum for SpriteState from LightAttack
    typedef enum
    {
      CASTING,
      MOVING,
      HITTING
    } SpriteState;

    //! struct with enum for Players
    typedef enum
    {
      PLAYER_1,
      PLAYER_2,
      PLAYER_3,
      PLAYER_4
    } Players;

    //! Variable that indicates the state used in engine
    State m_state;

    //! Variable that indicates the SpriteState used in engine
    SpriteState m_sprite_state;

    //! Variable that indicates the direction in x and y from light_attack
    double light_attack_axis_x_direction, light_attack_axis_y_direction;

    //! Variable that indicates the damage of light_attack
    int light_attack_damage;

    //! Variable that indicates the speed of light_attack
    double light_attack_speed;

    //! Variable that indicates the frame of light_attack
    int light_attack_frame;

    //! Variable of light_attack_sprite_path
    string light_attack_sprite_path;

    //! Variable that indicates the begining of light_attack
    unsigned light_attack_start;

    //! Variable that indicates the time of light_attack
    unsigned light_attack_current_time;

    shared_ptr<Texture> light_attack_texture;

    Rectangle light_attack_bounding_box;

    //bool on_event(const GameEvent& event);
};

#endif
