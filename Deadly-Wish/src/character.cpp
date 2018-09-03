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

#define BOUNDING_BOX_SIZE 24
#define SPEED = 80.00
#define CHARACTER_WIDTH 32
#define RESPAWN_TIME 10000

using std::cout;
using std::endl;
using std::min;
using std::max;


Character::Character(const vector<string> sprite_paths, unsigned new_character_id,
                     double position_axis_x, double position_axis_y, int max_life,
                     int character_code)
:  id(id), max_life(max_life), frame(0), start(-1), axis_x_speed(0.00),
   axis_y_speed(0.00), character_code(character_code)
{
    for(int i = 0; i < min((int) sprite_paths.size(), (int) NUMBER_OF_STATES); i++) {
        textures.push_back(resources::get_texture(sprite_paths[i]));
    }

    state = nullptr;
    respawn_time = RESPAWN_TIME;
    last_sound_played = -(RESPAWN_TIME);
    active = true;

    bounding_box = Rectangle(position_axis_x, position_axis_y, BOUNDING_BOX_SIZE, BOUNDING_BOX_SIZE);


    /*
    *m_x and m_y are atributes from GameObject that are protected by the project scope
    */

    m_x = position_axis_x;
    m_y = position_axis_y;

    width = CHARACTER_WIDTH;
    height = CHARACTER_WIDTH;

    if(game_mode::choosen_mode == "deathmatch-mode") {
        number_of_lives = 5;
    }

    respawn_character();
}

Character::~Character()
{
    physics::unregister_object(this);
    event::unregister_listener(this);
}

void Character::update_self(unsigned now, unsigned last){

    handle_state();

    if(((game_mode::choosen_mode == "base-mode") and base->life() <= 0) ||
        (game_mode::choosen_mode == "deathmatch-mode") and number_of_lives <= 0) {
        invalidate();
    }

    if (start == -1){
      start = now;
    }

    if((dead) and now - start > respawn_time) {
        start = now;
        dead = false;
        respawn_character();
    }

    if (not dead and now - start > state->refresh_rate())
    {
        start += state->refresh_rate();
        frame = (frame + 1) % (textures[state->current_state()]->w() / CHARACTER_WIDTH);
    }

    if(axis_y_speed == 0.0 && axis_x_speed == 0.0) {
        if(character_code == INFILTRATOR && state->current_state() == HEAVY_ATTACK_STATE) {
            update_position(now, last);
        }
        return;
    }

    if(now - last_sound_played > 400) {
        last_sound_played = now;
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

    bounding_box.set_position(x(), y());
}

inline void Character::update_position(const unsigned &now, const unsigned &last,
                                       bool backwards) {

    int multiplier = (backwards) ? -1 : 1;
    double summer = 1.0;
    bool ok = character_code == INFILTRATOR && state->current_state() == HEAVY_ATTACK_STATE;
    if(ok) {
        summer *= 1.75;
    }
    if(not freeze || ok) {
        double new_y = y() + multiplier * axis_y_speed * summer * (now - last) / 1000.0;
        new_y = min(new_y, SCREEN_HEIGHT - 32.00 - 16.00);
        new_y = max(new_y, 10.0);

        double new_x = x() + multiplier * axis_x_speed * summer * (now - last) / 1000.0;
        new_x = min(new_x, SCREEN_WIDTH - 32.00);
        new_x = max(new_x, 0.0);

        set_y(new_y);
        set_x(new_x);
    }
}

void Character::draw_self(Canvas *canvas, unsigned, unsigned){

    if(not dead) {
        Rectangle rect {(double) width * frame, (double) height * moving_state, (double) width, (double) height};
        canvas->draw(textures[state->current_state()].get(), rect, x(), y());
    }
}

bool Character::on_event(const GameEvent& event){

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
    if((event.id() == game_event::MOVEMENT_P1 && id == 0) ||
       (event.id() == game_event::MOVEMENT_P2 && id == 1) ||
       (event.id() == game_event::MOVEMENT_P3 && id == 2) ||
       (event.id() == game_event::MOVEMENT_P4 && id == 3)) {
        string axis = event.get_property<string>("axis");
        int value = event.get_property<int>("value");

        if(axis == "X") {
            axis_x_speed = SPEED * ((double) value / 32768);
            if(value > 0) {
                moving_state = MOVING_RIGHT;
            }
            else if(value < 0) {
                moving_state = MOVING_LEFT;
            }
        }
        else if(axis == "Y") {
            axis_y_speed = SPEED * ((double) value / 32768);
        }

        return true;
    }
    else if((p1_heavy_attack_validation || p2_heavy_attack_validation || p3_heavy_attack_validation || p4_heavy_attack_validation) &&
        (start - last_used_heavy_attack > heavy_attack_cooldown))
    {
        last_used_heavy_attack = start;
        heavy_attack();
        return true;
    }
    else if((p1_light_attack_validation || p2_light_attack_validation || p3_light_attack_validation || p4_light_attack_validation) &&
        (start - last_used_light_attack > light_attack_cooldown))
    {
        last_used_light_attack = start;
        light_attack();
        return true;
    }
    else if((p1_defense_validation || p2_defense_validation || p3_defense_validation || p4_defense_validation) &&
        (start - last_used_defense > defense_cooldown))
    {
        last_used_defense = start;
        defense();
        return true;
    }
    else if((p1_special_validation || p2_special_validation || p3_special_validation || p4_special_validation) &&
        (start - last_used_special > special_cooldown))
    {
        last_used_special = start;
        special();
        return true;
    }

    return false;
}

pair<double, double> Character::direction() const{
    return pair<double, double>(axis_x_speed, axis_y_speed);
}

bool Character::active() const{
    return active;
}

const Rectangle& Character::get_bounding_box() const {
    return bounding_box;
}

const list<Rectangle>& Character::hit_boxes() const {
    static list<Rectangle> boxes {bounding_box};
    return boxes;
}

void Character::on_collision(const Collidable *who, const Rectangle& where, unsigned now,
                             unsigned last){
    const Skill *s = dynamic_cast<const Skill *>(who);
    const Character *c = dynamic_cast<const Character *>(who);
    const Base *b = dynamic_cast<const Base *>(who);

    if(c or b) {
        update_position(now, last, true);
    }
    else if(state->current_state() != DEFENSE_STATE and s->character_id() != id and s->valid() and (((1 << id) & s->collided()) == 0)) {
        current_life -= s->damage();
        printf("Sofreu dano! Vida atual: %d\n", current_life);
    }
}


void Character::change_character_state(State next_state, bool respawning ){

    if(respawning) {
        printf("respawnando");
        state = character_state_factory.change_character_state(next_state);
        return;
    }
    if((state != nullptr and state->current_state() == DEATH_STATE) and not respawning) {
        return;
    }
    if(state != nullptr and next_state == state->current_state()) {
        return;
    }
    if(not freeze) {
        state = character_state_factory.change_character_state(next_state);
        frame = 0;
    }
}

void Character::handle_state(){

    if((current_life <= 0) || (base->life() <= 0 and game_mode::choosen_mode == "base-mode")) {
        change_character_state(DEATH_STATE);
    }

    if(state->current_state() == HEAVY_ATTACK_STATE) {
        freeze = true;
    }
    else {
        freeze = false;
        active = true;
    }

    if(state->current_state() == DEATH_STATE and
        (frame + 1) % textures[state->current_state()]->w() / 32) == 0) {
        kill_character();
        return;
    }

    if(state->current_state() != DEATH_STATE && state->current_state() != MOVING_STATE and
        (frame + 1) % (textures[state->current_state()]->w() / 32) == 0) {
        freeze = false;
        change_character_state(IDLE_STATE);
    }

    if(axis_x_speed == 0.0 && axis_y_speed == 0.0) {
        if(state->current_state() == MOVING_STATE ||
          (state->current_state() == IDLE_STATE && ((frame + 1) % (textures[IDLE_STATE]->w() / 32)) == 0)) {
            change_character_state(IDLE_STATE);
        }
    }
    else if(state->current_state() == IDLE_STATE) {
        change_character_state(MOVING_STATE);
    }
}

void Character::set_spawn_position(){

    switch(id) {
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
            printf("id: %d", id);
            break;
    }
}

void Character::respawn_character(){

    physics::register_object(this);
    event::register_listener(this);

    change_character_state(IDLE_STATE, true);
    set_spawn_position();
    bounding_box.set_position(x(), y());

    frame = 0;
    current_life = max_life;

    freeze = false;
    dead = false;

    if(id %2 == 0) {
        moving_state = MOVING_RIGHT;
    }
    else {
        moving_state = MOVING_LEFT;
    }

    printf("Vida atual: %d\n", current_life);
}

void Character::kill_character(){

    m_x = -12.0;
    m_y = -12.0;
    bounding_box.set_position(x(), y());
    frame = 0;
    printf("Personagem morreu!\n");
    physics::unregister_object(this);
    event::unregister_listener(this);
    dead = true;
    if(game_mode::choosen_mode == "deathmatch-mode") {
        number_of_lives--;
        base->set_base_status(8 - number_of_lives);
    }
}

void Character::set_base(Base *new_base) {

    base = new_base;
}
