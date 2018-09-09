#include "mage.h"
#include "fireball.h"
#include "frost_nova.h"
#include "ije02_game.h"
#include "skill.h"
#include "light_attack.h"

#include <vector>
#include <string>

#define MAX_LIFE 100
#define MAGE_SPECIAL_COOLDOWN 5000
#define MAGE_HEAVY_ATTACK_COOLDOWN 2000
#define MAGE_LIGHT_ATTACK_COOLDOWN 300

using std::vector;
using std::string;

Mage::Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    character_special_cooldown = MAGE_SPECIAL_COOLDOWN;
    character_heavy_attack_cooldown = MAGE_HEAVY_ATTACK_COOLDOWN;
    character_light_attack_cooldown = MAGE_LIGHT_ATTACK_COOLDOWN;
    character_defense_cooldown = MAGE_LIGHT_ATTACK_COOLDOWN;
    character_last_used_special = -character_special_cooldown;
    character_last_used_heavy_attack = -character_heavy_attack_cooldown;
    character_last_used_light_attack = -character_light_attack_cooldown;
    character_last_used_defense = -character_defense_cooldown;
    character_active = true;
}

void
Mage::do_heavy_attack()
{
    audio::play_sound_effect("res/sound/fx/mago_heavy.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double fireball_dx = 0.0;
    double fireball_x_pos = 0.0;

    if(character_moving_state == MOVING_RIGHT) {
        fireball_dx = 1.0;
        fireball_x_pos = x() + 20;
    }
    else{
        fireball_dx = -1.0;
        fireball_x_pos = x() - 20;
    }

    p->add_child(new Fireball(p, get_id(), fireball_x_pos, y(), fireball_dx, 0.0));

    change_character_state(HEAVY_ATTACK_STATE);
}

void
Mage::do_light_attack() {
    audio::play_sound_effect("res/sound/fx/mago_light.ogg", EFFECTS_VOLUME, 0);
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
Mage::do_defense() {
    audio::play_sound_effect("res/sound/fx/mago_block.ogg", EFFECTS_VOLUME, 0);
    change_character_state(DEFENSE_STATE);
}

void
Mage::do_special() {
    audio::play_sound_effect("res/sound/fx/mago_ultimate.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    p->add_child(new FrostNova(p, get_id(), x(), y(), 0.0, 0.0));

    change_character_state(SPECIAL_STATE);
}
