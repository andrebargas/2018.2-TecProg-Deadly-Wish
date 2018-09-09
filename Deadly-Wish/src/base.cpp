#include "base.h"
#include "ije02_game.h"
#include "skill.h"
#include "test_level_factory.h"

#include <ijengine/canvas.h>

#define BASE_WIDTH 32
#define MAX_LIFE 4000

Base::Base(int player_id)
    :base_player_id(player_id), base_frame(0), base_start(-1)
{
    base_sprite_paths.push_back("Spritesheets/Green/SpritesheetGreenBase.png");
    base_sprite_paths.push_back("Spritesheets/Blue/SpritesheetBlueBase.png");
    base_sprite_paths.push_back("Spritesheets/Yellow/SpritesheetYellowBase.png");
    base_sprite_paths.push_back("Spritesheets/Red/SpritesheetRedBase.png");

    base_texture = resources::get_texture(base_sprite_paths[player_id]);

    base_width = BASE_WIDTH;
    base_height = BASE_WIDTH;
    base_life = MAX_LIFE;

    set_base_position(player_id, m_x, m_y);

    if(game_mode::choosen_mode == "base-mode"){
        base_bounding_box = Rectangle(m_x, m_y, 20, 12);
        physics::register_object(this);
    }
}

Base::~Base()
{
    if(game_mode::choosen_mode == "base-mode"){
        physics::unregister_object(this);
    }
}

void
Base::update_self(unsigned now, unsigned last)
{
    if(base_start == -1) {
        base_start = now;
    }
    if(game_mode::choosen_mode == "base-mode"){
        change_base_status();
    }

    if(now - base_start > 400) {
        base_start += 400;
        base_frame = (base_frame + 1) % (base_texture->w() / BASE_WIDTH);
    }
}

void
Base::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) base_width * base_frame, (double) base_height * base_status, (double) base_width, (double) base_height};
    canvas->draw(base_texture.get(), rect, x(), y());
}

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
            printf("Valor errado no set_base_position_position!\n");
            printf("player_id: %d", player_id);
            break;
    }
}

bool
Base::active() const
{
    return true;
}

const Rectangle&
Base::bounding_box() const
{
    return base_bounding_box;
}

const list<Rectangle>&
Base::hit_boxes() const
{
    static list<Rectangle> boxes {base_bounding_box};
    return boxes;
}

void
Base::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last)
{
    if(game_mode::choosen_mode == "base-mode"){
        const Skill *s = dynamic_cast<const Skill *>(who);

        if(s and s->get_character_id() != base_player_id and s->valid() and
          (((1 << (base_player_id + 4)) & s->get_collided()) == 0)) {

            base_life -= s->get_damage();
            printf("BASE HP: %d\n", base_life);
            printf("Vida da base: %d\n", base_life);
        }

        change_base_status();
    }
}

pair<double, double>
Base::direction() const
{
    return pair<double, double>(base_axis_x_speed, base_axis_y_speed);
}

void
Base::change_base_status()
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

void
Base::set_base_status(int new_base_status)
{
    base_status = new_base_status;
}
