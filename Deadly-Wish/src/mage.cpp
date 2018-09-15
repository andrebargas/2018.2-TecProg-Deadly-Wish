#include "mage.h"
#include "fireball.h"
#include "frost_nova.h"
#include "ije02_game.h"
#include "skill.h"
#include "light_attack.h"

#include <vector>
#include <string>

// vida total do personagem
#define MAX_LIFE 100
// poder especial
#define MAGE_SPECIAL_COOLDOWN 5000
// poder pesado
#define MAGE_HEAVY_ATTACK_COOLDOWN 2000
// poder de ataque leve
#define MAGE_LIGHT_ATTACK_COOLDOWN 300
// poder de defesa
#define MAGE_DEFENSE_COOLDOWN 300

using std::vector;
using std::string;


Mage::Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    // poder de ataque 5000
    character_special_cooldown = MAGE_SPECIAL_COOLDOWN;
    // poder de ataque: 2000
    character_heavy_attack_cooldown = MAGE_HEAVY_ATTACK_COOLDOWN;
    // poder de ataque: 300
    character_light_attack_cooldown = MAGE_LIGHT_ATTACK_COOLDOWN;
    // poder de defesa: 300
    character_defense_cooldown = MAGE_DEFENSE_COOLDOWN;
    // ultimo uso do poder especial
    character_last_used_special = -character_special_cooldown;
    // ultimo uso do poder pesado   
    character_last_used_heavy_attack = -character_heavy_attack_cooldown;
    // ultimo uso do poder leve
    character_last_used_light_attack = -character_light_attack_cooldown;
    // ultimo uso da defesa
    character_last_used_defense = -character_defense_cooldown;
    // personagem ativo 
    character_active = true;
}

// método do poder pesado
void
Mage::do_heavy_attack()
{
    // som do poder
    audio::play_sound_effect("res/sound/fx/mago_heavy.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    // direção e posição a fireball (eixo x)
    double fireball_dx = 0.0;
    double fireball_x_pos = 0.0;

    // se o personagem estiver para direita
    if(character_moving_state == MOVING_RIGHT) {
        fireball_dx = 1.0;
        fireball_x_pos = x() + 20;
    }
    else{
        fireball_dx = -1.0;
        fireball_x_pos = x() - 20;
    }

    p->add_child(new Fireball(p, get_id(), fireball_x_pos, y(), fireball_dx, 0.0));

    // muda o estado do personagem
    change_character_state(HEAVY_ATTACK_STATE);
}

// método do poder leve de ataque
void
Mage::do_light_attack() {
    // som do poder
    audio::play_sound_effect("res/sound/fx/mago_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    // posicao do ataque no eixo x
    double light_attack_x_pos = 0.0;

    // se o personagem estiver para direita 
    if(character_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    else{
        light_attack_x_pos = x() - 15;
    }

    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));

    // muda o estado do personagem
    change_character_state(LIGHT_ATTACK_STATE);
}

// método para defesa do personagem
void
Mage::do_defense() {
    //som da defesa
    audio::play_sound_effect("res/sound/fx/mago_block.ogg", EFFECTS_VOLUME, 0);
    // muda o estado do personagem
    change_character_state(DEFENSE_STATE);
}

// método para poder espaicl do mago
void
Mage::do_special() {
    // som do poder especial
    audio::play_sound_effect("res/sound/fx/mago_ultimate.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    p->add_child(new FrostNova(p, get_id(), x(), y(), 0.0, 0.0));

    // muda o estado do personagem
    change_character_state(SPECIAL_STATE);
}
