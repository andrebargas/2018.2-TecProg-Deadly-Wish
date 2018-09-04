#include "mage.h"
#include "fireball.h"
#include "frost_nova.h"
#include "ije02_game.h"
#include "skill.h"
#include "light_attack.h"

#include <vector>
#include <string>

#define MAX_LIFE 100
#define LIGHT_ATTACK_POSITION_VAR 15
#define HEAVY_ATTACK_POSITION_VAR 20
#define LEFT_DIRECTION -1.0
#define RIGHT_DIRECTION 1.0

using std::vector;
using std::string;

Mage::Mage(vector<string> sprite_paths, unsigned character_id, double x_position, double y_position, int character_code)
    : Character(sprite_paths, character_id, x_position, y_position, MAX_LIFE, character_code)
{

    //nao ira usar #define por ja estar explicito
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

void Mage::do_heavy_attack() {
    audio::play_sound_effect("res/sound/fx/mago_heavy.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);
    double fireball_x_direction = 0.0;
    double fireball_x_position = 0.0;

    if(moving_state == MOVING_RIGHT) {
        fireball_x_direction = RIGHT_DIRECTION;
        fireball_x_position = x() + HEAVY_ATTACK_POSITION_VAR;
    }
    else{
        fireball_x_direction = LEFT_DIRECTION;
        fireball_x_position = x() - HEAVY_ATTACK_POSITION_VAR;
    }


    p->add_child(new Fireball(p, get_id(), fireball_x_position, y(), fireball_x_direction, 0.0));

    ChangeCharacterState(HEAVY_ATTACK_STATE);
}

void Mage::do_light_attack() {

    audio::play_sound_effect("res/sound/fx/mago_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);
    double light_attack_x_position = 0.0;

    if(moving_state == MOVING_RIGHT) {
        light_attack_x_position = x() + LIGHT_ATTACK_POSITION_VAR;
    }
    else{
        light_attack_x_position = x() - LIGHT_ATTACK_POSITION_VAR;
    }


    p->add_child(new LightAttack(p, get_id(), light_attack_x_position, y()));


    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));


    ChangeCharacterState(LIGHT_ATTACK_STATE);
}

void Mage::do_defense() {

    audio::play_sound_effect("res/sound/fx/mago_block.ogg", EFFECTS_VOLUME, 0);
    ChangeCharacterState(DEFENSE_STATE);
}

void Mage::do_special() {

    audio::play_sound_effect("res/sound/fx/mago_ultimate.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    p->add_child(new FrostNova(p, get_id(), x(), y(), 0.0, 0.0));

    change_character_state(SPECIAL_STATE);
}
