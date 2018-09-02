#include "soldier.h"
#include "spear.h"
#include "light_attack.h"
#include "ije02_game.h"

#define MAX_LIFE 120
#define RECHARGE_SPECIAL 5000
#define RECHARGE_HEAVY_ATTACK 2000
#define RECHARGE_LIGHT_ATTACK 300
#define RECHARGE_DEFENSE 300
#define MOVIMENT 15

Soldier::Soldier(vector<string> sprite_paths, unsigned id,
    double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code) {

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

void Soldier::DoHeavyAttack() {

    audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double spear_dx = 0.0;
    double spear_x_pos = 0.0;

    if(m_moving_state == MOVING_RIGHT) {
        spear_dx = 1.0;
        spear_x_pos = x() + 20;
    }
    else{
        spear_dx = -1.0;
        spear_x_pos = x() - 20;
    }

    p->add_child(new Spear(p, id(), spear_x_pos, y(), spear_dx, 0.0));
    ChangeCharacterState(HEAVY_ATTACK_STATE);
}

void Soldier::DoLightAttack() {

    audio::play_sound_effect("res/sound/fx/soldier_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double light_attack_x_pos = 0.0;
    
    if(m_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + MOVIMENT;
    }
    else{
        light_attack_x_pos = x() - MOVIMENT;
    }

    p->add_child(new DoLightAttack(p, id(), light_attack_x_pos, y()));

    ChangeCharacterState(LIGHT_ATTACK_STATE);
}

void Soldier::DoDefense() {

    audio::play_sound_effect("res/sound/fx/soldier_block.ogg", EFFECTS_VOLUME, 0);
    ChangeCharacterState(DEFENSE_STATE);
}

void Soldier::DoSpecial() {

    audio::play_sound_effect("res/sound/fx/soldier_ultimate.ogg", EFFECTS_VOLUME, 0);
    ChangeCharacterState(SPECIAL_STATE);
}