#include "base.h"
#include "ije02_game.h"
#include "skill.h"
#include "test_level_factory.h"

#include <ijengine/canvas.h>

#define MAX_LIFE 4000
#define CHARACTER_WIDTH 32
#define CHARACTER_HEIGHT 32
#define GREEN_BASE "Spritesheets/Green/SpritesheetGreenBase.png"
#define BLUE_BASE "Spritesheets/Blue/SpritesheetBlueBase.png"
#define YELLOW_BASE "Spritesheets/Yellow/SpritesheetYellowBase.png"
#define RED_BASE "Spritesheets/Red/SpritesheetRedBase.png"

Base::Base(int player_id) 
    :m_player_id(player_id), frame(0), start(-1) {
    sprite_paths.push_back(GREEN_BASE);
    sprite_paths.push_back(BLUE_BASE);
    sprite_paths.push_back(YELLOW_BASE);
    sprite_paths.push_back(RED_BASE);

    m_texture = resources::get_texture(sprite_paths[player_id]);

    width = CHARACTER_WIDTH;
    height = CHARACTER_HEIGHT;
    get_life = MAX_LIFE;

    set_base_position(player_id, m_x, m_y);

    if(game_mode::choosen_mode == "base-mode") {
        bounding_box = Rectangle(m_x, m_y, 20, 12);
        physics::register_object(this);
    }
}

Base::~Base() {
    if(game_mode::choosen_mode == "base-mode"){
        physics::unregister_object(this);
    }
}

void Base::update_self(unsigned now, unsigned last) {
    if(start == -1) {
        start = now;
    }
    if(game_mode::choosen_mode == "base-mode") {
        change_base_status();
    }
    if(now - start > 400) {
        start += 400;
        frame = (frame + 1) % (m_texture->w() / 32);
    }
}

void Base::draw_self(Canvas *canvas, unsigned, unsigned) {
    Rectangle rect {(double) width * frame, (double) height * base_status, (double) width, (double) height};
    canvas->draw(m_texture.get(), rect, x(), y());
}

void Base::set_base_position(unsigned player_id, double& x_pos, double& y_pos) {
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

bool Base::is_active() const {
    return true;
}

const Rectangle& Base::get_bounding_box() const {
    return bounding_box;
}

const list<Rectangle>& Base::hit_boxes() const {
    static list<Rectangle> boxes {bounding_box};
    return boxes;
}

void Base::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last) {
    if(game_mode::choosen_mode == "base-mode"){
        const Skill *s = dynamic_cast<const Skill *>(who);

        if(s and s->character_id() != m_player_id and s->valid() and (((1 << (m_player_id + 4)) & s->collided()) == 0)) {
            get_life -= s->damage();
            printf("BASE HP: %d\n", get_life);
            printf("Vida da base: %d\n", get_life);
        }

        change_base_status();
    }
}

pair<double, double> Base::get_direction() const {
    return pair<double, double>(axis_x_speed, axis_y_speed);
}

void Base::change_base_status() {
    if(get_life > 3500) {
        base_status = BALLS_8;
    }
    else if(3500 >= get_life and get_life > 3000) {
        base_status = BALLS_7;
    }
    else if(3000 >= get_life and get_life > 2500) {
        base_status = BALLS_6;
    }
    else if(2500 >= get_life and get_life > 2000) {
        base_status = BALLS_5;
    }
    else if(2000 >= get_life and get_life > 1500) {
        base_status = BALLS_4;
    }
    else if(1500 >= get_life and get_life > 1000) {
        base_status = BALLS_3;
    }
    else if(1000 >= get_life and get_life > 500) {
        base_status = BALLS_2;
    }
    else if(500 >= get_life and get_life > 1) {
        base_status = BALLS_1;
    }
    else {
        base_status = DESTROYED;
    }
}

void Base::set_base_status(int base_status) {
    base_status = base_status;
}