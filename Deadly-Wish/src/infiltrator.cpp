#include "infiltrator.h"
#include "ije02_game.h"
#include "light_attack.h"

#define MAX_LIFE 100
#define INFILTRATOR_SPECIAL_COOLDOWN 5000
#define INFILTRATOR_HEAVY_ATTACK_COOLDOWN 2000
#define INFILTRATOR_LIGHT_ATTACK_COOLDOWN 300
#define INFILTRATOR_DEFENSE_COOLDOWN 300

Infiltrator::Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    character_special_cooldown = INFILTRATOR_SPECIAL_COOLDOWN;
    character_heavy_attack_cooldown = INFILTRATOR_HEAVY_ATTACK_COOLDOWN;
    character_light_attack_cooldown = INFILTRATOR_LIGHT_ATTACK_COOLDOWN;
    character_defense_cooldown = INFILTRATOR_DEFENSE_COOLDOWN;
    character_last_used_special = -character_special_cooldown;
    character_last_used_heavy_attack = -character_heavy_attack_cooldown;
    character_last_used_light_attack = -character_light_attack_cooldown;
    character_last_used_defense = -character_defense_cooldown;
    character_active = true;
}

void
Infiltrator::do_heavy_attack()
{
    audio::play_sound_effect("res/sound/fx/infiltrador_heavy.ogg", EFFECTS_VOLUME, 0);
    character_active = false;
    Character::character_active = false;
    change_character_state(HEAVY_ATTACK_STATE);
}

void
Infiltrator::do_light_attack() {
    audio::play_sound_effect("res/sound/fx/infiltrador_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double light_attack_x_pos = 0.0;

    if(character_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    else{
        light_attack_x_pos = x() - 15;
    }

    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));

    change_character_state(LIGHT_ATTACK_STATE);
}

void
Infiltrator::do_defense() {
    audio::play_sound_effect("res/sound/fx/infiltrador_block.ogg", EFFECTS_VOLUME, 0);
    change_character_state(DEFENSE_STATE);
}

void
Infiltrator::do_special() {
    audio::play_sound_effect("res/sound/fx/infiltrador_ultimate.ogg", EFFECTS_VOLUME, 0);
    change_character_state(SPECIAL_STATE);
}

bool
Infiltrator::active() const {
    return Character::character_active;
}
