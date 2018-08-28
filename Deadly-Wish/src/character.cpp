#include "character.h"
#include "ije02_game.h"
#include "main_level.h"
#include "skill.h"
#include "test_level_factory.h"

#include <ijengine/engine.h>
#include <ijengine/canvas.h>
#include <ijengine/rectangle.h>

#include <iostream>
#include <algorithm>
#include <cstdio>

using std::cout;
using std::endl;
using std::min;
using std::max;

const double SPEED = 80.00;

Character::Character(const vector<string> sprite_paths, unsigned id, double x, double y, int max_life, int character_code)
    :  m_id(id), m_max_life(max_life), m_frame(0), m_start(-1), m_x_speed(0.00), m_y_speed(0.00), m_character_code(character_code)
{
    for(int i = 0; i < min((int) sprite_paths.size(), (int) NUMBER_OF_STATES); i++) {
        m_textures.push_back(resources::get_texture(sprite_paths[i]));
    }

    m_state = nullptr;
    m_respawn_time = 10000;
    m_last_sound_played = -10000;
    m_active = true;

    m_bounding_box = Rectangle(x, y, 24, 24);

    m_x = x;
    m_y = y;

    m_w = 32;
    m_h = 32;

    if(game_mode::choosen_mode == "deathmatch-mode") {
        m_number_of_lives = 5;
    }

    respawn_character();
}

Character::~Character()
{
    physics::unregister_object(this);
    event::unregister_listener(this);
}

void
Character::update_self(unsigned now, unsigned last)
{

    handle_state();
    
    if(((game_mode::choosen_mode == "base-mode") and m_base->life() <= 0) ||
        (game_mode::choosen_mode == "deathmatch-mode") and m_number_of_lives <= 0) {
        invalidate();
    }

    if (m_start == -1)
        m_start = now;

    if((m_dead) and now - m_start > m_respawn_time) {
        m_start = now;
        m_dead = false;
        respawn_character();
    }

    if (not m_dead and now - m_start > m_state->refresh_rate())
    {
        m_start += m_state->refresh_rate();
        m_frame = (m_frame + 1) % (m_textures[m_state->current_state()]->w() / 32);
    }

    if(m_y_speed == 0.0 && m_x_speed == 0.0) {
        if(m_character_code == INFILTRATOR && m_state->current_state() == HEAVY_ATTACK_STATE) {
            update_position(now, last);
        }
        return;
    }

    if(now - m_last_sound_played > 400) {
        m_last_sound_played = now;
        switch(m_character_code) {
            case KNIGHT:
                audio::play_sound_effect("res/sound/fx/pesadao_run.ogg", 30, 0);
                break;

            case INFILTRATOR:
                audio::play_sound_effect("res/sound/fx/infiltrador_run.ogg", 30, 0);
                break;

            case MAGE:
                audio::play_sound_effect("res/sound/fx/mago_run.ogg", 30, 0);
                break;

            case SOLDIER:
                audio::play_sound_effect("res/sound/fx/soldier_run.ogg", 30, 0);
                break;
        }
    }

    update_position(now, last);

    m_bounding_box.set_position(x(), y());
}

inline void
Character::update_position(const unsigned &now, const unsigned &last, bool backwards) {
    int multiplier = (backwards) ? -1 : 1;
    double summer = 1.0;
    bool ok = m_character_code == INFILTRATOR && m_state->current_state() == HEAVY_ATTACK_STATE;
    if(ok) {
        summer *= 1.75;
    }
    if(not m_freeze || ok) {
        double new_y = y() + multiplier * m_y_speed * summer * (now - last) / 1000.0;
        new_y = min(new_y, SCREEN_HEIGHT - 32.00 - 16.00);
        new_y = max(new_y, 10.0);

        double new_x = x() + multiplier * m_x_speed * summer * (now - last) / 1000.0;
        new_x = min(new_x, SCREEN_WIDTH - 32.00);
        new_x = max(new_x, 0.0);

        set_y(new_y);
        set_x(new_x);
    }
}

void
Character::draw_self(Canvas *canvas, unsigned, unsigned)
{
    if(not m_dead) {
        Rectangle rect {(double) m_w * m_frame, (double) m_h * m_moving_state, (double) m_w, (double) m_h};
        canvas->draw(m_textures[m_state->current_state()].get(), rect, x(), y());
    }
}

bool
Character::on_event(const GameEvent& event)
{
    bool p1_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P1 && id() == 0;
    bool p2_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P2 && id() == 1;
    bool p3_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P3 && id() == 2;
    bool p4_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P4 && id() == 3;

    bool p1_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P1 && id() == 0;
    bool p2_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P2 && id() == 1;
    bool p3_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P3 && id() == 2;
    bool p4_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P4 && id() == 3;

    bool p1_defense_validation = event.id() == game_event::DEFENSE_P1 && id() == 0;
    bool p2_defense_validation = event.id() == game_event::DEFENSE_P2 && id() == 1;
    bool p3_defense_validation = event.id() == game_event::DEFENSE_P3 && id() == 2;
    bool p4_defense_validation = event.id() == game_event::DEFENSE_P4 && id() == 3;

    bool p1_special_validation = event.id() == game_event::SPECIAL_P1 && id() == 0;
    bool p2_special_validation = event.id() == game_event::SPECIAL_P2 && id() == 1;
    bool p3_special_validation = event.id() == game_event::SPECIAL_P3 && id() == 2;
    bool p4_special_validation = event.id() == game_event::SPECIAL_P4 && id() == 3;

    printf("EVENT ID: %d\n", (int) event.id());
    if((event.id() == game_event::MOVEMENT_P1 && m_id == 0) ||
       (event.id() == game_event::MOVEMENT_P2 && m_id == 1) ||
       (event.id() == game_event::MOVEMENT_P3 && m_id == 2) ||
       (event.id() == game_event::MOVEMENT_P4 && m_id == 3)) {
        string axis = event.get_property<string>("axis");
        int value = event.get_property<int>("value");

        if(axis == "X") {
            m_x_speed = SPEED * ((double) value / 32768);
            if(value > 0) {
                m_moving_state = MOVING_RIGHT;
            }
            else if(value < 0) {
                m_moving_state = MOVING_LEFT;
            }
        } 
        else if(axis == "Y") {
            m_y_speed = SPEED * ((double) value / 32768);
        }

        return true;
    }
    else if((p1_heavy_attack_validation || p2_heavy_attack_validation || p3_heavy_attack_validation || p4_heavy_attack_validation) &&
        (m_start - m_last_used_heavy_attack > m_heavy_attack_cooldown))
    {
        m_last_used_heavy_attack = m_start;
        heavy_attack();
        return true;
    }
    else if((p1_light_attack_validation || p2_light_attack_validation || p3_light_attack_validation || p4_light_attack_validation) &&
        (m_start - m_last_used_light_attack > m_light_attack_cooldown))
    {
        m_last_used_light_attack = m_start;
        light_attack();
        return true;
    }
    else if((p1_defense_validation || p2_defense_validation || p3_defense_validation || p4_defense_validation) &&
        (m_start - m_last_used_defense > m_defense_cooldown))
    {   
        m_last_used_defense = m_start;
        defense();
        return true;
    }
    else if((p1_special_validation || p2_special_validation || p3_special_validation || p4_special_validation) &&
        (m_start - m_last_used_special > m_special_cooldown))
    {
        m_last_used_special = m_start;
        special();
        return true;
    }

    return false;
}

pair<double, double>
Character::direction() const
{
    return pair<double, double>(m_x_speed, m_y_speed);
}

bool
Character::active() const 
{
    return m_active;
}

const Rectangle&
Character::bounding_box() const 
{
    return m_bounding_box;
}

const list<Rectangle>&
Character::hit_boxes() const 
{
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

void
Character::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last) 
{
    const Skill *s = dynamic_cast<const Skill *>(who);
    const Character *c = dynamic_cast<const Character *>(who);
    const Base *b = dynamic_cast<const Base *>(who);

    if(c or b) {
        update_position(now, last, true);
    }
    else if(m_state->current_state() != DEFENSE_STATE and s->character_id() != m_id and s->valid() and (((1 << m_id) & s->collided()) == 0)) {
        m_current_life -= s->damage();
        printf("Sofreu dano! Vida atual: %d\n", m_current_life);
    }
}

void
Character::change_character_state(State next_state, bool respawning ) 
{
    if(respawning) {
        printf("respawnando");
        m_state = m_character_state_factory.change_character_state(next_state);
        return;
    }
    if((m_state != nullptr and m_state->current_state() == DEATH_STATE) and not respawning) {
        return;
    }
    if(m_state != nullptr and next_state == m_state->current_state()) {
        return;
    }
    if(not m_freeze) {
        m_state = m_character_state_factory.change_character_state(next_state);
        m_frame = 0;
    }
}

void Character::handle_state()
{
    if((m_current_life <= 0) || (m_base->life() <= 0 and game_mode::choosen_mode == "base-mode")) {
        change_character_state(DEATH_STATE);
    }

    if(m_state->current_state() == HEAVY_ATTACK_STATE) {
        m_freeze = true;
    }
    else {
        m_freeze = false;
        m_active = true;
    }

    if(m_state->current_state() == DEATH_STATE and 
        (m_frame + 1) % (m_textures[m_state->current_state()]->w() / 32) == 0) {
        kill_character();
        return;
    }

    if(m_state->current_state() != DEATH_STATE && m_state->current_state() != MOVING_STATE and
        (m_frame + 1) % (m_textures[m_state->current_state()]->w() / 32) == 0) {
        m_freeze = false;
        change_character_state(IDLE_STATE);
    }

    if(m_x_speed == 0.0 && m_y_speed == 0.0) {
        if(m_state->current_state() == MOVING_STATE || 
          (m_state->current_state() == IDLE_STATE && ((m_frame + 1) % (m_textures[IDLE_STATE]->w() / 32)) == 0)) {
            change_character_state(IDLE_STATE);
        }
    }
    else if(m_state->current_state() == IDLE_STATE) {
        change_character_state(MOVING_STATE);
    }
}

void
Character::set_spawn_position()
{
    switch(m_id) {
        case PLAYER_1:
            m_x = X_ADJUSTMENT;
            m_y = Y_ADJUSTMENT;
            break;

        case PLAYER_2:
            m_x = (double) SCREEN_WIDTH - 32.0 - X_ADJUSTMENT;
            m_y = Y_ADJUSTMENT;
            break;

        case PLAYER_3:
            m_x = X_ADJUSTMENT;
            m_y = (double) SCREEN_HEIGHT - 32.0 - Y_ADJUSTMENT;
            break;

        case PLAYER_4:
            m_x = (double) SCREEN_WIDTH - 32.0 - X_ADJUSTMENT;
            m_y = (double) SCREEN_HEIGHT - 32.0 - Y_ADJUSTMENT;
            break;

        default:
            printf("Valor errado no set_spawn_position!\n");
            printf("m_id: %d", m_id);
            break;
    }
}

void
Character::respawn_character()
{
    physics::register_object(this);
    event::register_listener(this);

    change_character_state(IDLE_STATE, true);
    set_spawn_position();
    m_bounding_box.set_position(x(), y());

    m_frame = 0;
    m_current_life = m_max_life;

    m_freeze = false;
    m_dead = false;

    if(m_id %2 == 0) {
        m_moving_state = MOVING_RIGHT;
    }
    else {
        m_moving_state = MOVING_LEFT;
    }

    printf("Vida atual: %d\n", m_current_life);
}

void
Character::kill_character()
{
    m_x = -12.0;
    m_y = -12.0;
    m_bounding_box.set_position(x(), y());
    m_frame = 0;
    printf("Personagem morreu!\n");
    physics::unregister_object(this);
    event::unregister_listener(this);
    m_dead = true;
    if(game_mode::choosen_mode == "deathmatch-mode") {
        m_number_of_lives--;
        m_base->set_base_status(8 - m_number_of_lives);
    }
}

void
Character::set_base(Base *base) {
    m_base = base;
}
