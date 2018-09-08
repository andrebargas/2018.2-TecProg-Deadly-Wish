#include "knight.h"
#include "light_attack.h"
#include "ije02_game.h"

#define MAX_LIFE 300
#define KNIGHT_SPECIAL_COOLDOWN 5000
#define KNIGHT_HEAVY_ATTACK_COOLDOWN 2000
#define KNIGHT_LIGHT_ATTACK_COOLDOWN 300
#define KNIGHT_DEFENSE_COOLDOWN 300

Knight::Knight(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    character_special_cooldown = KNIGHT_SPECIAL_COOLDOWN;
    character_heavy_attack_cooldown = KNIGHT_HEAVY_ATTACK_COOLDOWN;
    character_light_attack_cooldown = KNIGHT_LIGHT_ATTACK_COOLDOWN;
    character_defense_cooldown = KNIGHT_DEFENSE_COOLDOWN;
    character_last_used_special = -character_special_cooldown;
    character_last_used_heavy_attack = -character_heavy_attack_cooldown;
    character_last_used_light_attack = -character_light_attack_cooldown;
    character_last_used_defense = -character_defense_cooldown;
    character_active = true;
}

void
Knight::do_heavy_attack()
{
    audio::play_sound_effect("res/sound/fx/pesadao_heavy.ogg", EFFECTS_VOLUME, 0);
    change_character_state(HEAVY_ATTACK_STATE);
}

void
Knight::do_light_attack() {
    audio::play_sound_effect("res/sound/fx/pesadao_light.ogg", EFFECTS_VOLUME, 0);
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
Knight::do_defense() {
    audio::play_sound_effect("res/sound/fx/pesadao_block.ogg", EFFECTS_VOLUME, 0);
    change_character_state(DEFENSE_STATE);
}

void
Knight::do_special() {
    change_character_state(SPECIAL_STATE);
}
