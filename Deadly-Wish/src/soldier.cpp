#include "soldier.h"
#include "spear.h"
#include "light_attack.h"
#include "ije02_game.h"

#define MAX_LIFE 150
#define RECHARGE_SPECIAL 5000
#define RECHARGE_HEAVY_ATTACK 2000
#define RECHARGE_LIGHT_ATTACK 300
#define RECHARGE_DEFENSE 300
#define LIGHT_MOVIMENT 15
#define HEAVY_MOVIMENT 20
#define VARIATION_DIRECTION_HEAVY_ATTACK 1.0

Soldier::Soldier(vector<string> sprite_paths, unsigned new_character_id,
                 double position_axis_x, double position_axis_y, int character_code)
: Character(sprite_paths, new_character_id, position_axis_x, position_axis_y, MAX_LIFE, character_code) {

    special_cooldown = RECHARGE_SPECIAL;
    heavy_attack_cooldown = RECHARGE_HEAVY_ATTACK;
    light_attack_cooldown = RECHARGE_LIGHT_ATTACK;
    defense_cooldown = RECHARGE_DEFENSE;
    last_used_special = -special_cooldown;
    last_used_heavy_attack = -heavy_attack_cooldown;
    last_used_light_attack = -light_attack_cooldown;
    last_used_defense = -defense_cooldown;
    active = true;
}

void Soldier::do_heavy_attack() {

    audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double spear_direction_x = 0.0;
    double spear_x_position = 0.0;

    if(moving_state == MOVING_RIGHT) {
        spear_direction_x = VARIATION_DIRECTION_HEAVY_ATTACK;
        spear_x_position = x() + HEAVY_MOVIMENT;
    }
    else{
        spear_direction_x = -(VARIATION_DIRECTION_HEAVY_ATTACK);
        spear_x_position = x() - HEAVY_MOVIMENT;
    }

    p->add_child(new Spear(p, get_id(), spear_x_position, y(), spear_dx, 0.0));
    change_character_state(HEAVY_ATTACK_STATE);
}

void Soldier::do_light_attack() {

    audio::play_sound_effect("res/sound/fx/soldier_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double light_attack_x_position = 0.0;

    if(moving_state == MOVING_RIGHT) {
        light_attack_x_position = x() + LIGHT_MOVIMENT;
    }
    else{
        light_attack_x_position = x() - LIGHT_MOVIMENT;
    }

    p->add_child(new LightAttack(p, get_id(), light_attack_x_position, y()));

    change_character_state(LIGHT_ATTACK_STATE);
}

void Soldier::do_defense() {

    audio::play_sound_effect("res/sound/fx/soldier_block.ogg", EFFECTS_VOLUME, 0);
    change_character_state(DEFENSE_STATE);
}

void Soldier::do_special() {

    audio::play_sound_effect("res/sound/fx/soldier_ultimate.ogg", EFFECTS_VOLUME, 0);
    change_character_state(SPECIAL_STATE);
}
