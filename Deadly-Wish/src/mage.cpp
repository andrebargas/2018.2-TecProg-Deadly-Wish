#include "mage.h"
#include "fireball.h"
#include "frost_nova.h"
#include "ije02_game.h"
#include "skill.h"
#include "light_attack.h"

#include <vector>
#include <string>

#define MAX_LIFE 100

using std::vector;
using std::string;

Mage::Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
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
Mage::DoHeavyAttack()
{
    audio::play_sound_effect("res/sound/fx/mago_heavy.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double fireball_dx = 0.0;
    double fireball_x_pos = 0.0;

    if(moving_state == MOVING_RIGHT) {
        fireball_dx = 1.0;
        fireball_x_pos = x() + 20;
    }
    else{
        fireball_dx = -1.0;
        fireball_x_pos = x() - 20;
    }

    p->add_child(new Fireball(p, get_id(), fireball_x_pos, y(), fireball_dx, 0.0));

    ChangeCharacterState(HEAVY_ATTACK_STATE);
}

void
Mage::DoLightAttack() {
    audio::play_sound_effect("res/sound/fx/mago_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double light_attack_x_pos = 0.0;

    if(moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    else{
        light_attack_x_pos = x() - 15;
    }


    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));


    ChangeCharacterState(LIGHT_ATTACK_STATE);
}

void
Mage::DoDefense() {
    audio::play_sound_effect("res/sound/fx/mago_block.ogg", EFFECTS_VOLUME, 0);
    ChangeCharacterState(DEFENSE_STATE);
}

void
Mage::DoSpecial() {
    audio::play_sound_effect("res/sound/fx/mago_ultimate.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    p->add_child(new FrostNova(p, get_id(), x(), y(), 0.0, 0.0));

    change_character_state(SPECIAL_STATE);
}
