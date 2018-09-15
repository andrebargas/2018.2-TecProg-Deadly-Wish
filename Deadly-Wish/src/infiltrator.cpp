#include "infiltrator.h"
#include "ije02_game.h"
#include "light_attack.h"

// vida total do personagem
#define MAX_LIFE 100
// poder de ataque
#define SOLDIER_SPECIAL_COOLDOWN 5000
// poder de ataque
#define SOLDIER_HEAVY_ATTACK_COOLDOWN 2000
// poder de ataque
#define SOLDIER_LIGHT_ATTACK_COOLDOWN 300
// poder de ataque
#define SOLDIER_DEFENSE_COOLDOWN 300


Infiltrator::Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    // poder de ataque - 5000
    character_special_cooldown = INFILTRATOR_SPECIAL_COOLDOWN;
    // poder de ataque - 2000
    character_heavy_attack_cooldown = INFILTRATOR_HEAVY_ATTACK_COOLDOWN;
    // poder de ataque - 300
    character_light_attack_cooldown = INFILTRATOR_LIGHT_ATTACK_COOLDOWN;
    // poder de defesa - 300
    character_defense_cooldown = INFILTRATOR_DEFENSE_COOLDOWN;
    // ultimo uso do poder especial
    character_last_used_special = -INFILTRATOR_SPECIAL_COOLDOWN;
    // ultimo uso do poder pesado   
    character_last_used_heavy_attack = -INFILTRATOR_HEAVY_ATTACK_COOLDOWN;
    // ultimo uso do poder leve
    character_last_used_light_attack = -INFILTRATOR_LIGHT_ATTACK_COOLDOWN;
    // ultimo uso da defesa
    character_last_used_defense = -INFILTRATOR_DEFENSE_COOLDOWN;
    // personagem ativo 
    character_active = true;
}

void
Infiltrator::do_heavy_attack()
{
    // som do poder pesado
    audio::play_sound_effect("res/sound/fx/infiltrador_heavy.ogg", EFFECTS_VOLUME, 0);
    // nao entendi
    character_active = false;
    Character::character_active = false;
    // muda o estado do personagem
    change_character_state(HEAVY_ATTACK_STATE);
}

void
Infiltrator::do_light_attack() {
    // som do poder leve
    audio::play_sound_effect("res/sound/fx/infiltrador_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    // posicao do ataque no eixo x
    double light_attack_x_pos = 0.0;

    // personagem se movimentando para direita
    if(character_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    // personagem se movimentando para esquerda ou outros
    else{
        light_attack_x_pos = x() - 15;
    }

    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));

    // muda o estado do personagem
    change_character_state(LIGHT_ATTACK_STATE);
}

void
Infiltrator::do_defense() {
    // som da defesa
    audio::play_sound_effect("res/sound/fx/infiltrador_block.ogg", EFFECTS_VOLUME, 0);
    // muda o estado do personagem
    change_character_state(DEFENSE_STATE);
}

void
Infiltrator::do_special() {
    // som do ataque especial
    audio::play_sound_effect("res/sound/fx/infiltrador_ultimate.ogg", EFFECTS_VOLUME, 0);
    // muda o estado do personagem
    change_character_state(SPECIAL_STATE);
}

// método que retorna o personagem ativo
bool
Infiltrator::active() const {
    return Character::character_active;
}
