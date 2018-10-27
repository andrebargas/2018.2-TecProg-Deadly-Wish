/**\file base.h
  * \brief This is the base class file that is the 'strength' base of the player in the game.
  */
#ifndef BASE_H
#define BASE_H

//! Including file of class GameObject
#include <ijengine/game_object.h>

//! Including file from class Texture
#include <ijengine/texture.h>

//! Including Collidable class file
#include <ijengine/collidable.h>

//! Including Rectangle class file
#include <ijengine/rectangle.h>

//! Including Enum's file
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

/**\class Base base.h "include / base.h"
* \brief Class used to define the 'strength' basis of a
* player in the game.
*/
class Base : public GameObject, public Collidable {
public:

    /**\fn Base ()
    * \public
    * \brief constructor method
    * \param player_id int Player Id. Not initialized.
    */
    Base(int player_id);

    /**\fn ~Base ()
    * \public
    * \brief destructor method
    * \param player_id int id of a character
    */
    ~Base ();

    /**\fn get_base_player_id ()
    * \public
    * \brief get method
    * \return unsigned int returns the base of the player
    */
    unsigned get_base_player_id() const { return base_player_id; }

    /**\fn get_base_life ()
    * \public
    * \brief get method
    * \return int returns the life of the base
    */
    int get_base_life() const {return base_life;}

    /**\fn set_base_status ()
    * \public
    * \brief Method set
    * \param base_status int states of a base in the game
    * \return void
    */
    void set_base_status(int base_status);

    //! Collidable virtual methods
    /**\fn active ()
    * \public
    * \brief Collidable virtual method that returns True if base is active
    * \return bool returns base status if active = True
    */
    bool active() const;
    
    /**\fn bounding_box ()
    * \public
    * \brief Method that delimits the bounds of the base
    * \return const Rectangle &
    */
    const Rectangle& bounding_box() const;

    /**\fn hit_boxs ()
    * \public
    * \brief Method that delimits base contact points
    * \return const list <Rectangle> &
    */
    const list<Rectangle>& hit_boxes() const;

    /**\fn on_collision ()
    * \public
    * \brief Method that acts when there is collision
    * \return void
    */
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    
    /**\fn direction ()
    * \public
    * \brief Method that returns base speed in certain direction
    * \return pair <double, double> returns the velocity of the base in the position x and y
    */
    pair<double, double> direction() const;


    protected:
    
        /**\fn set_base_position ()
        * \protected
        * \brief Method set for location of base in given position
        * \param player_id unsigned character id
        * \param x_pos double & position on x-axis
        * \param y_pos double & position on y-axis
        * \return void
        */
        void set_base_position(unsigned player_id, double& x_pos, double& y_pos);
        
        /**\fn change_base_status ()
        * \protected
        * \brief Method that changes the base status (number of spheres in the drawing)
        * \return void
        */
        void change_base_status();

        /**\fn update_self ()
        * \protected
        * \brief GameObject Virtual Method
        * \param now unsigned current situation
        * \param last unsigned last situation past
        * \return void
        */
        void update_self(unsigned now, unsigned last);
        
        /**\fn draw_self (()
        * \protected
        * \brief function that draws the base
        * \param now unsigned
        * \param last unsigned
        * \return void
        */
        void draw_self(Canvas *canvas, unsigned now, unsigned last);


    protected:
    
        /*\var base_player_id
         * \brief gets the value of player_id
         */
        unsigned base_player_id;

        /*\var base_life
         * \brief represents the life value of the base = 4000
         */
        int base_life;

        /*\var base_frame
         * \brief represents the base frame at the moment
         */
        int base_frame;

        /*\var base_start
        * \brief that initializes the base of the player
        * ...starts with -1
        */
        int base_start;

        /*\var base_width
        * \brief base width in pixels
        */
        int base_width;

        /*\var base_height
        * \brief basic base height in pixels
        */
        int base_height;

        /*\var base_status
        * \brief base brief status, number of spheres present in base
        * ...goes from '8' to '0', if it reaches '0' it changes the status to destroyed
        */
        int base_status;

        /*\var base_sprite_paths
        * \vector
        * \brief with PNG images
        */
        vector <string> base_sprite_paths;

        /*\var base_texture
        * \brief contains base texture
        */
        shared_ptr <Texture> base_texture;

        /*\var base_bounding_box
        * \brief delimits the bounds of the base
        */
        Rectangle base_bounding_box;

        /*\var base_axis_x_speed
        * \brief speed on x-axis
        */
        double base_axis_x_speed;

        /*\\var base_axis_y_speed
        * \brief speed on y-axis
        */
        double base_axis_y_speed;

};

#endif