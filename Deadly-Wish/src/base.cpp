//aplicar modulo 5
/** \file base.cpp
  * \brief This is the file with the methods of the Base Class, that is the
  *'Fortress' of the player in game.
  */

#include<bits/stdc++.h>
 //Including file of Base class
#include "base.h"
//Including file of GameObject class
#include "ije02_game.h"
//Including file of Skill class
#include "skill.h"
//Including file of TestLevelFactory class
#include "test_level_factory.h"

#include <ijengine/canvas.h>

#define BASE_WIDTH 32
#define MAX_LIFE 4000
/**\fn Base()
*\public
*\brief Constructor method
*\param player_id int Id of player.Not initialized.
*/
Base::Base(int player_id)
    :base_player_id(player_id), base_frame(0), base_start(-1)
{
    /**\fn push_back()
    *\public
    *\brief function that retrieves the Base`s Sprite to be showed
    *\param string path of the Base`s image
    */
    base_sprite_paths.push_back("Spritesheets/Green/SpritesheetGreenBase.png");
    base_sprite_paths.push_back("Spritesheets/Blue/SpritesheetBlueBase.png");
    base_sprite_paths.push_back("Spritesheets/Yellow/SpritesheetYellowBase.png");
    base_sprite_paths.push_back("Spritesheets/Red/SpritesheetRedBase.png");

    base_texture = resources::get_texture(base_sprite_paths[player_id]);

    base_width = BASE_WIDTH;
    base_height = BASE_WIDTH;
    base_life = MAX_LIFE;

    set_base_position(player_id, m_x, m_y);

    //The base is showed in game if it`s Base mode
    if(game_mode::choosen_mode == "base-mode"){
        base_bounding_box = Rectangle(m_x, m_y, 20, 12);
        physics::register_object(this);
    }
    else{
      //do nothing
    }
}
/**\fn ~Base()
*\public
*\brief Destructor method
*/
Base::~Base()
{
    //The base must be destroied only if it`s Base Mode
    if(game_mode::choosen_mode == "base-mode"){
        physics::unregister_object(this);
    }
    else{
      //do nothing
    }
}

/**\fn update_self()
*\protected
*\brief Virtual method of GameObject
*\param now unsigned actual state
*\param last unsigned last state
*\return void
*/
void
Base::update_self(unsigned now, unsigned last)
{
    //if base isn`t initialized, it will be initialized with the actual time
    if(base_start == -1) {
        base_start = now;
    }
    else{
      //do nothing
    }

    //If the game mode is Base mode, the base status must be changed based in the base life
    if(game_mode::choosen_mode == "base-mode"){
        change_base_status();
    }
    else{
      //do nothing
    }

    // Update the base frame
    if(now - base_start > 400) {
        base_start += 400;
        base_frame = (base_frame + 1) % (base_texture->w() / BASE_WIDTH);
    }
    else{
      //do nothing
    }
}
//PBS
/**\fn draw_self(()
*\protected
*\brief Draw the base
*\param *canvas Canvas
*\param unsigned
*\param unsigned
*\return void
*/
void Base::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) base_width * base_frame, (double) base_height * base_status, (double) base_width, (double) base_height};
    canvas->draw(base_texture.get(), rect, x(), y());
}

//PBS
/**\fn set_base_position()
*\protected
*\brief Set method for put the base in the right position
*\param player_id unsigned id of the player
*\param x_pos double& x_axys_position
*\param y_pos double& y_axys_position
*\return void
*/
void
Base::set_base_position(unsigned player_id, double& x_pos, double& y_pos)
{
    switch(player_id) {
        case PLAYER_1:
            x_pos = BASE_X_ADJUSTMENT;
            y_pos = BASE_Y_ADJUSTMENT;
            break;

        case PLAYER_2:
            x_pos = (double) SCREEN_WIDTH - (double)BASE_WIDTH - BASE_X_ADJUSTMENT;
            y_pos = BASE_Y_ADJUSTMENT;
            break;

        case PLAYER_3:
            x_pos = BASE_X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - (double)BASE_WIDTH - BASE_Y_ADJUSTMENT;
            break;

        case PLAYER_4:
            x_pos = (double) SCREEN_WIDTH - (double)BASE_WIDTH - BASE_X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - (double)BASE_WIDTH - BASE_Y_ADJUSTMENT;
            break;

        default:
            cout << "Wrong value in set_base_position_position!\n";
            cout << "player_id: " << player_id << "\n";
            break;
    }
}

//Collidable virtual method
/**\fn active()
*\public
*\brief Collidable virtual method that return True if the base is active
*\return bool return the base status, it`s active if True
*/
bool Base::active() const
{
    return true;
}

//PBS
/**\fn bounding_box()
*\public
*\brief Method that delimeters the base`s limits
*\return const Rectangle&
*/
const Rectangle&
Base::bounding_box() const
{
    return base_bounding_box;
}

/**\fn hit_boxs()
*\public
*\brief Method that delimeters the base`s contact points
*\return const list<Rectangle>&
*/
const list<Rectangle>& Base::hit_boxes() const
{
    static list<Rectangle> boxes {base_bounding_box};
    return boxes;
}

/**\fn on_collision()
*\public
*\brief Method that acts if was a colision
*\return void
*/
void Base::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last)
{
    //This block is to do damage to a Enemy base
    if(game_mode::choosen_mode == "base-mode"){
        const Skill *s = dynamic_cast<const Skill *>(who);

        if(s and s->get_character_id() != base_player_id and s->valid() and
          (((1 << (base_player_id + 4)) & s->get_collided()) == 0)) {

            base_life -= s->get_damage();
            cout << "BASE HP: " << base_life << "\n";
        }
        else{
          //do nothing
        }

        change_base_status();
    }
    else{
      //do nothing
    }
}

/**\fn direction()
*\public
*\brief Method that returns the speed of the base in a direction
*\return pair<double,double> returns the velocity of the base in x and y position
*/
pair<double, double>
Base::direction() const
{
    return pair<double, double>(base_axis_x_speed, base_axis_y_speed);
}

//PBS
/**\fn change_base_status()
*\protected
*\brief Mehotd that change the base`s status (number of balls)
*\return void
*/
void Base::change_base_status()
{
    if(base_life > 3500) {
        base_status = BALLS_8;
    }
    else if(3500 >= base_life and base_life > 3000) {
        base_status = BALLS_7;
    }
    else if(3000 >= base_life and base_life > 2500) {
        base_status = BALLS_6;
    }
    else if(2500 >= base_life and base_life > 2000) {
        base_status = BALLS_5;
    }
    else if(2000 >= base_life and base_life > 1500) {
        base_status = BALLS_4;
    }
    else if(1500 >= base_life and base_life > 1000) {
        base_status = BALLS_3;
    }
    else if(1000 >= base_life and base_life > 500) {
        base_status = BALLS_2;
    }
    else if(500 >= base_life and base_life > 1) {
        base_status = BALLS_1;
    }
    else {
        base_status = DESTROYED;
    }
}

/**\fn set_base_status()
*\public
*\brief Set method
*\param new_base_status int new state of a base in the game
*\return void
*/
void Base::set_base_status(int new_base_status)
{
    base_status = new_base_status;
}
