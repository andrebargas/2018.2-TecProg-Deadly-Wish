#include "base.h"
#include "ije02_game.h"
#include "skill.h"
#include "test_level_factory.h"

#include <ijengine/canvas.h>

#define MAX_LIFE 4000
Base::Base(int player_id)
    :m_player_id(player_id), m_frame(0), m_start(-1)
{
    m_sprite_paths.push_back("Spritesheets/Green/SpritesheetGreenBase.png");
    m_sprite_paths.push_back("Spritesheets/Blue/SpritesheetBlueBase.png");
    m_sprite_paths.push_back("Spritesheets/Yellow/SpritesheetYellowBase.png");
    m_sprite_paths.push_back("Spritesheets/Red/SpritesheetRedBase.png");

    m_texture = resources::get_texture(m_sprite_paths[player_id]);

    m_w = 32;
    m_h = 32;
    m_life = MAX_LIFE;

    set_base_position(player_id, m_x, m_y);

    if(game_mode::choosen_mode == "base-mode"){
        
        m_bounding_box = Rectangle(m_x, m_y, 20, 12);
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
    if(m_start == -1) {
        m_start = now;
    }
    if(game_mode::choosen_mode == "base-mode") {
        change_base_status();
    }

    if(now - m_start > 400) {
        m_start += 400;
        m_frame = (m_frame + 1) % (m_texture->w() / 32);
    }
}

void
Base::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) m_w * m_frame, (double) m_h * m_base_status, (double) m_w, (double) m_h};
    canvas->draw(m_texture.get(), rect, x(), y());
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
            x_pos = (double) SCREEN_WIDTH - 32.0 - BASE_X_ADJUSTMENT;
            y_pos = BASE_Y_ADJUSTMENT;
            break;

        case PLAYER_3:
            x_pos = BASE_X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - 32.0 - BASE_Y_ADJUSTMENT;
            break;

        case PLAYER_4:
            x_pos = (double) SCREEN_WIDTH - 32.0 - BASE_X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - 32.0 - BASE_Y_ADJUSTMENT;
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
    return m_bounding_box;
}

const list<Rectangle>&
Base::hit_boxes() const 
{
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

void
Base::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last)
{
    if(game_mode::choosen_mode == "base-mode"){
        const Skill *s = dynamic_cast<const Skill *>(who);

        if(s and s->character_id() != m_player_id and s->valid() and (((1 << (m_player_id + 4)) & s->collided()) == 0)) {
            m_life -= s->damage();
            printf("BASE HP: %d\n", m_life);
            printf("Vida da base: %d\n", m_life);
        }

        change_base_status();
    }
}

pair<double, double>
Base::direction() const
{
    return pair<double, double>(m_x_speed, m_y_speed);
}

void
Base::change_base_status()
{
    if(m_life > 3500) {
        m_base_status = BALLS_8;
    }
    else if(3500 >= m_life and m_life > 3000) {
        m_base_status = BALLS_7;
    }
    else if(3000 >= m_life and m_life > 2500) {
        m_base_status = BALLS_6;
    }
    else if(2500 >= m_life and m_life > 2000) {
        m_base_status = BALLS_5;
    }
    else if(2000 >= m_life and m_life > 1500) {
        m_base_status = BALLS_4;
    }
    else if(1500 >= m_life and m_life > 1000) {
        m_base_status = BALLS_3;
    }
    else if(1000 >= m_life and m_life > 500) {
        m_base_status = BALLS_2;
    }
    else if(500 >= m_life and m_life > 1) {
        m_base_status = BALLS_1;
    }
    else {
        m_base_status = DESTROYED;
    }
}

void
Base::set_base_status(int base_status)
{
    m_base_status = base_status;
}