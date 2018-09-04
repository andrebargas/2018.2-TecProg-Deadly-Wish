#include "knight.h"
#include "light_attack.h"
#include "ije02_game.h"

#define MAX_LIFE 300

Knight::Knight(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    special_cooldown = 5000;
    heavy_attack_cooldown = 2000;
    light_attack_cooldown = 300;
    defense_cooldown = 300;
    last_used_special = -special_cooldown;
    last_used_heavy_attack = -heavy_attack_cooldown;
    last_used_light_attack = -light_attack_cooldown;
    last_used_defense = -defense_cooldown;
    active = true;
}

void
Knight::DoHeavyAttack()
{
    audio::play_sound_effect("res/sound/fx/pesadao_heavy.ogg", EFFECTS_VOLUME, 0);
    ChangeCharacterState(HEAVY_ATTACK_STATE);
}

void
Knight::DoLightAttack() {
    audio::play_sound_effect("res/sound/fx/pesadao_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double light_attack_x_pos = 0.0;
    
    if(m_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    else{
        light_attack_x_pos = x() - 15;
    }

    p->add_child(new DoLightAttack(p, id(), light_attack_x_pos, y()));

    ChangeCharacterState(LIGHT_ATTACK_STATE);
}

void
Knight::DoDefense() {
    audio::play_sound_effect("res/sound/fx/pesadao_block.ogg", EFFECTS_VOLUME, 0);
    ChangeCharacterState(DEFENSE_STATE);
}

void
Knight::DoSpecial() {
    ChangeCharacterState(SPECIAL_STATE);
}