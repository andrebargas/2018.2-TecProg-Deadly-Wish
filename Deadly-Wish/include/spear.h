/** \file spear.h
  * \brief Este é o arquivo header da classe Spear que exibe a spear(lança) do soldier, com herança da classe Skill
  */
#ifndef SPEAR_H
#define SPEAR_H

#include "skill.h"
#include <cmath>

//! Include game engine files
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/color.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>

#include <memory>
#include <vector>
#include <assert.h>

using std::shared_ptr;
using std::vector;

using namespace std;
using namespace ijengine;

/** \class Spear spear.h "include/spear.h"
 *  \brief Class inheriting from GameObject and Collidable that calculates
 *  the damage received by the characters.
 * \breif Spear builder method
 * \param *parent Pointer to GameObject
 * \param soldier_id soldier character identifier
 * \param xp double X axis position
 * \param yp double Y axis position
 */
class Spear : public Skill
{
  public:
    /** \fn Spear(GameObject *parent, unsigned soldier_id, double xp, double yp,
          double dx, double dy);
     * \public
     * \brief builder method
     */
    Spear(GameObject *parent, unsigned soldier_id, double xp, double yp,
          double dx, double dy);

    /** \fn ~Spear()
      * \public
      * \brief Destructor Method
      */
    ~Spear();

    //! Virtual Collision Methods
    bool active() const;
    const Rectangle &bounding_box() const;
    const list<Rectangle> &hit_boxes() const;
    pair<double, double> direction() const;

  protected:
    /** \fn update_self(unsigned now, unsigned last)
      * \protected
      * \brief Function to update the start time of the level, and set attribute #winner_level_start. 
      *  Name can not be changed because it is a method inherited from the parent class,
      *  protected by project scope
      *  GameObjectVirtual Methods 
      * \param now unsigned current time
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

    //! enum to choose the direction of Spear
    typedef enum
    {
        MOVING_LEFT,
        MOVING_RIGHT
    } State;

    //! struct with enum for Spear SpriteState
    typedef enum
    {
        THROW,
        MOVING,
        FALLING,
        HITTING
    } SpriteState;

    //! struct enum Players
    typedef enum
    {
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4
    } Players;

    //! Variable that spear_id_character
    unsigned spear_character_id;
    //! Variable indicating the state of the spear
    State spear_state;
    //! Variable indicating the SpriteState used in the engine
    SpriteState spear_sprite_state;
    //! Variable that indicates the direction in x and y of the spear
    double spear_axis_x_direction;
    //! Variable that indicates the direction in x and y of the spear
    double spear_axis_y_direction;
    //! Variable indicating spear damage
    int spear_damage;
    //! Spear velocity variable
    double spear_speed;
    //! Variable that indicates the frame of the spear
    int spear_frame;
    //! Variable that indicates the sprite_path
    string spear_sprite_path;
    //! Variable that indicates the begining of spear(lança)
    unsigned spear_start;
    //! Variable that indicates the time of spear
    unsigned spear_current_time;
    shared_ptr<Texture> spear_texture;
    Rectangle spear_bounding_box;

    //    bool on_event(const GameEvent& event);
};

#endif
