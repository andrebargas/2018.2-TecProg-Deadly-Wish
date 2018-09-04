#include "knight.h"
#include "light_attack.h"
#include "ije02_game.h"

#define MAX_LIFE 300
#define SPECIAL_COOLDOWN 5000
#define HEAVY_ATTACK_COOLDOWN 2000
#define LIGHT_ATTACK_COOLDOWN 300
#define DEFENSE_COOLDOWN 300

Knight::Knight(vector<string> sprite_paths, unsigned player_id, double x_position, double y_position, int character_id)
    : Character(sprite_paths, player_id, x_position, y_position, MAX_LIFE, character_id)
{
    last_used_special = -SPECIAL_COOLDOWN;
    last_used_heavy_attack = -HEAVY_ATTACK_COOLDOWN;
    last_used_light_attack = -LIGHT_ATTACK_COOLDOWN;
    last_used_defense = -DEFENSE_COOLDOWN;
    active = true;
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

    double light_attack_x_position = 0.0;
    
    if(moving_state == MOVING_RIGHT) {
        light_attack_x_position = x_position() + 15;
    }
    else{
        light_attack_x_position = x_position() - 15;
    }

    p->add_child(new LightAttack(p, player_id(), light_attack_x_position, y_position()));

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