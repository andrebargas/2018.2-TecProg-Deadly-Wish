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

#define RESPAWN_TIME 10000
#define CHARACTER_WIDTH 32

using std::cout;
using std::endl;
using std::min;
using std::max;

const double SPEED = 80.00;

Character::Character(const vector<string> sprite_paths, unsigned id, double x, double y,
                     int max_life, int character_code)
    :  character_id(id), character_max_life(max_life), character_frame(0), character_start(-1),
       character_axis_x_speed(0.00), character_axis_y_speed(0.00),
       character_code(character_code)
{
    for(int i = 0; i < min((int) sprite_paths.size(), (int) NUMBER_OF_STATES); i++) {
        character_textures.push_back(resources::get_texture(sprite_paths[i]));
    }

    character_state = nullptr;
    character_respawn_time = RESPAWN_TIME;
    character_last_sound_played = -RESPAWN_TIME;
    character_active = true;

    character_bounding_box = Rectangle(x, y, 24, 24);

    m_x = x;
    m_y = y;

    character_width = CHARACTER_WIDTH;
    character_height = CHARACTER_WIDTH;

    if(game_mode::choosen_mode == "deathmatch-mode") {
        character_number_of_lives = 5;
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

    if(((game_mode::choosen_mode == "base-mode") and character_base->get_base_life() <= 0) ||
        (game_mode::choosen_mode == "deathmatch-mode") and character_number_of_lives <= 0) {
        invalidate();
    }

    if (character_start == -1)
        character_start = now;

    if((character_dead) and now - character_start > character_respawn_time) {
        character_start = now;
        character_dead = false;
        respawn_character();
    }

    if (not character_dead and now - character_start > character_state->get_refresh_rate())
    {
        character_start += character_state->get_refresh_rate();
        character_frame = (character_frame + 1) % (character_textures[character_state->get_current_state()]->w() / CHARACTER_WIDTH);
    }

    if(character_axis_y_speed == 0.0 && character_axis_x_speed == 0.0) {
        if(character_code == INFILTRATOR && character_state->get_current_state() == HEAVY_ATTACK_STATE) {
            update_position(now, last);
        }
        return;
    }

    if(now - character_last_sound_played > 400) {
        character_last_sound_played = now;
        switch(character_code) {
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

    character_bounding_box.set_position(x(), y());
}

inline void
Character::update_position(const unsigned &now, const unsigned &last, bool backwards) {
    int multiplier = (backwards) ? -1 : 1;
    double summer = 1.0;
    bool ok = character_code == INFILTRATOR && character_state->get_current_state() == HEAVY_ATTACK_STATE;
    if(ok) {
        summer *= 1.75;
    }
    if(not character_freeze || ok) {
        double new_y = y() + multiplier * character_axis_y_speed * summer * (now - last) / 1000.0;
        new_y = min(new_y, SCREEN_HEIGHT - (double)CHARACTER_WIDTH - 16.00);
        new_y = max(new_y, 10.0);

        double new_x = x() + multiplier * character_axis_x_speed * summer * (now - last) / 1000.0;
        new_x = min(new_x, SCREEN_WIDTH - (double)CHARACTER_WIDTH);
        new_x = max(new_x, 0.0);

        set_y(new_y);
        set_x(new_x);
    }
}

void
Character::draw_self(Canvas *canvas, unsigned, unsigned)
{
    if(not character_dead) {
        Rectangle rect {(double) character_width * character_frame,
                        (double) character_height * character_moving_state,
                        (double) character_width, (double) character_height};
        canvas->draw(character_textures[character_state->get_current_state()].get(), rect, x(), y());
    }
}

bool
Character::on_event(const GameEvent& event)
{
    bool p1_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P1 && get_id() == 0;
    bool p2_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P2 && get_id() == 1;
    bool p3_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P3 && get_id() == 2;
    bool p4_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P4 && get_id() == 3;

    bool p1_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P1 && get_id() == 0;
    bool p2_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P2 && get_id() == 1;
    bool p3_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P3 && get_id() == 2;
    bool p4_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P4 && get_id() == 3;

    bool p1_defense_validation = event.id() == game_event::DEFENSE_P1 && get_id() == 0;
    bool p2_defense_validation = event.id() == game_event::DEFENSE_P2 && get_id() == 1;
    bool p3_defense_validation = event.id() == game_event::DEFENSE_P3 && get_id() == 2;
    bool p4_defense_validation = event.id() == game_event::DEFENSE_P4 && get_id() == 3;

    bool p1_special_validation = event.id() == game_event::SPECIAL_P1 && get_id() == 0;
    bool p2_special_validation = event.id() == game_event::SPECIAL_P2 && get_id() == 1;
    bool p3_special_validation = event.id() == game_event::SPECIAL_P3 && get_id() == 2;
    bool p4_special_validation = event.id() == game_event::SPECIAL_P4 && get_id() == 3;

    printf("EVENT ID: %d\n", (int) event.id());
    if((event.id() == game_event::MOVEMENT_P1 && character_id == 0) ||
       (event.id() == game_event::MOVEMENT_P2 && character_id == 1) ||
       (event.id() == game_event::MOVEMENT_P3 && character_id == 2) ||
       (event.id() == game_event::MOVEMENT_P4 && character_id == 3)) {
        string axis = event.get_property<string>("axis");
        int value = event.get_property<int>("value");

        if(axis == "X") {
            character_axis_x_speed = SPEED * ((double) value / 32768);
            if(value > 0) {
                character_moving_state = MOVING_RIGHT;
            }
            else if(value < 0) {
                character_moving_state = MOVING_LEFT;
            }
        }
        else if(axis == "Y") {
            character_axis_y_speed = SPEED * ((double) value / 32768);
        }

        return true;
    }
    else if((p1_heavy_attack_validation || p2_heavy_attack_validation || p3_heavy_attack_validation || p4_heavy_attack_validation) &&
        (character_start - character_last_used_heavy_attack > character_heavy_attack_cooldown))
    {
        character_last_used_heavy_attack = character_start;
        do_heavy_attack();
        return true;
    }
    else if((p1_light_attack_validation || p2_light_attack_validation || p3_light_attack_validation || p4_light_attack_validation) &&
        (character_start - character_last_used_light_attack > character_light_attack_cooldown))
    {
        character_last_used_light_attack = character_start;
        do_light_attack();
        return true;
    }
    else if((p1_defense_validation || p2_defense_validation || p3_defense_validation || p4_defense_validation) &&
        (character_start - character_last_used_defense > character_defense_cooldown))
    {
        character_last_used_defense = character_start;
        do_defense();
        return true;
    }
    else if((p1_special_validation || p2_special_validation || p3_special_validation || p4_special_validation) &&
        (character_start - character_last_used_special > character_special_cooldown))
    {
        character_last_used_special = character_start;
        do_special();
        return true;
    }

    return false;
}

pair<double, double>
Character::direction() const
{
    return pair<double, double>(character_axis_x_speed, character_axis_y_speed);
}

bool
Character::active() const
{
    return character_active;
}

const Rectangle&
Character::bounding_box() const
{
    return character_bounding_box;
}

const list<Rectangle>&
Character::hit_boxes() const
{
    static list<Rectangle> boxes {character_bounding_box};
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
    else if(character_state->get_current_state() != DEFENSE_STATE and s->get_character_id() != character_id and
            s->valid() and (((1 << character_id) & s->get_collided()) == 0)) {
        character_current_life -= s->get_damage();
        printf("Sofreu dano! Vida atual: %d\n", character_current_life);
    }
}

void
Character::change_character_state(State next_state, bool respawning )
{
    if(respawning) {
        printf("respawnando");
        character_state = new_character_state_factory.change_character_state(next_state);
        return;
    }
    if((character_state != nullptr and character_state->get_current_state() == DEATH_STATE) and not respawning) {
        return;
    }
    if(character_state != nullptr and next_state == character_state->get_current_state()) {
        return;
    }
    if(not character_freeze) {
        character_state = new_character_state_factory.change_character_state(next_state);
        character_frame = 0;
    }
}

void Character::handle_state()
{
    if((character_current_life <= 0) || (character_base->get_base_life() <= 0 and game_mode::choosen_mode == "base-mode")) {
        change_character_state(DEATH_STATE);
    }

    if(character_state->get_current_state() == HEAVY_ATTACK_STATE) {
        character_freeze = true;
    }
    else {
        character_freeze = false;
        character_active = true;
    }

    if(character_state->get_current_state() == DEATH_STATE and
        (character_frame + 1) % (character_textures[character_state->get_current_state()]->w() / CHARACTER_WIDTH) == 0) {
        kill_character();
        return;
    }

    if(character_state->get_current_state() != DEATH_STATE && character_state->get_current_state() != MOVING_STATE and
        (character_frame + 1) % (character_textures[character_state->get_current_state()]->w() / CHARACTER_WIDTH) == 0) {
        character_freeze = false;
        change_character_state(IDLE_STATE);
    }

    if(character_axis_x_speed == 0.0 && character_axis_y_speed == 0.0) {
        if(character_state->get_current_state() == MOVING_STATE ||
          (character_state->get_current_state() == IDLE_STATE && ((character_frame + 1) % (character_textures[IDLE_STATE]->w() / CHARACTER_WIDTH)) == 0)) {
            change_character_state(IDLE_STATE);
        }
    }
    else if(character_state->get_current_state() == IDLE_STATE) {
        change_character_state(MOVING_STATE);
    }
}

void
Character::set_spawn_position()
{
    switch(character_id) {
        case PLAYER_1:
            m_x = X_ADJUSTMENT;
            m_y = Y_ADJUSTMENT;
            break;

        case PLAYER_2:
            m_x = (double) SCREEN_WIDTH - (double)CHARACTER_WIDTH - X_ADJUSTMENT;
            m_y = Y_ADJUSTMENT;
            break;

        case PLAYER_3:
            m_x = X_ADJUSTMENT;
            m_y = (double) SCREEN_HEIGHT - (double)CHARACTER_WIDTH - Y_ADJUSTMENT;
            break;

        case PLAYER_4:
            m_x = (double) SCREEN_WIDTH - (double)CHARACTER_WIDTH - X_ADJUSTMENT;
            m_y = (double) SCREEN_HEIGHT - (double)CHARACTER_WIDTH - Y_ADJUSTMENT;
            break;

        default:
            printf("Valor errado no set_spawn_position!\n");
            printf("m_id: %d", character_id);
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
    character_bounding_box.set_position(x(), y());

    character_frame = 0;
    character_current_life = character_max_life;

    character_freeze = false;
    character_dead = false;

    if(character_id %2 == 0) {
        character_moving_state = MOVING_RIGHT;
    }
    else {
        character_moving_state = MOVING_LEFT;
    }

    printf("Vida atual: %d\n", character_current_life);
}

void
Character::kill_character()
{
    m_x = -12.0;
    m_y = -12.0;
    character_bounding_box.set_position(x(), y());
    character_frame = 0;
    printf("Personagem morreu!\n");
    physics::unregister_object(this);
    event::unregister_listener(this);
    character_dead = true;
    if(game_mode::choosen_mode == "deathmatch-mode") {
        character_number_of_lives--;
        character_base->set_base_status(8 - character_number_of_lives);
    }
}

void
Character::set_base(Base *base) {
    character_base = base;
}
