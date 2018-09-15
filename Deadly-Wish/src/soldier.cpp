#include "soldier.h"
#include "spear.h"
#include "light_attack.h"
#include "ije02_game.h"

//! Vida total do personagem
#define MAX_LIFE 120
//! Poder de ataque (special) do cavaleiro
#define KNIGHT_SPECIAL_COOLDOWN 5000
//! Poder de ataque (heavy_atack) do cavaleiro
#define KNIGHT_HEAVY_ATTACK_COOLDOWN 2000
//! Poder de ataque (light_atack) do cavaleiro
#define KNIGHT_LIGHT_ATTACK_COOLDOWN 300
//! Poder de defesa do cavaleiro
#define KNIGHT_DEFENSE_COOLDOWN 300

    
//! Método Construtor - público
/*!
\param sprite_paths - desenha personagem
\param id - identificador do personagem
\param x - posição no eixo x
\param y - posição no eixo y
\param character_code - codigo do personagem
*/
Soldier::Soldier(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    //! poder de ataque - 5000
    character_special_cooldown = SOLDIER_SPECIAL_COOLDOWN;
    //! poder de ataque - 2000
    character_heavy_attack_cooldown = SOLDIER_HEAVY_ATTACK_COOLDOWN;
    //! poder de ataque - 300
    character_light_attack_cooldown = SOLDIER_LIGHT_ATTACK_COOLDOWN;
    //! poder de defesa - 300
    character_defense_cooldown = SOLDIER_DEFENSE_COOLDOWN;
    //! ultimo uso do poder especial
    character_last_used_special = -character_special_cooldown;
    //! ultimo uso do poder pesado   
    character_last_used_heavy_attack = -character_heavy_attack_cooldown;
    //! ultimo uso do poder leve
    character_last_used_light_attack = -character_light_attack_cooldown;
    //! ultimo uso da defesa
    character_last_used_defense = -character_defense_cooldown;
    //! personagem ativo 
    character_active = true;
}

//! método que da o ataque pesado com poder de: 2000
void
Soldier::do_heavy_attack()
{
    //! som do poder heavy_atack
    audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    //! lança na direçâo x
    double spear_dx = 0.0;
    //! lança na posição x
    double spear_x_pos = 0.0;

    //! soldado virado para direita
    if(character_moving_state == MOVING_RIGHT) {
        spear_dx = 1.0;
        spear_x_pos = x() + 20;
    }
    //! soldado virado para esquerda
    else{
        spear_dx = -1.0;
        spear_x_pos = x() - 20;
    }
    p->add_child(new Spear(p, get_id(), spear_x_pos, y(), spear_dx, 0.0));

    //!  muda o estado do personagem para o ataque
    change_character_state(HEAVY_ATTACK_STATE);
}

//! método que da o ataque leve com poder de: 300
void
Soldier::do_light_attack() {
    //! som do poder
    audio::play_sound_effect("res/sound/fx/soldier_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    //! posicao do ataque
    double light_attack_x_pos = 0.0;

    //! personagem virado para direita
    if(character_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    //! personagem em outras direções
    else{
        light_attack_x_pos = x() - 15;
    }

    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));

    //! muda o estado do personagem para o ataque
    change_character_state(LIGHT_ATTACK_STATE);
}


//! Método que aplica a defesa do personagem
void
Soldier::do_defense() {
    //! som da defesa
    audio::play_sound_effect("res/sound/fx/soldier_block.ogg", EFFECTS_VOLUME, 0);
    //! muda o estado para defesa
    change_character_state(DEFENSE_STATE);
}

//! Método que da o ataque especial de poder: 5000
void
Soldier::do_special() {
    //! som do ataque especial
    audio::play_sound_effect("res/sound/fx/soldier_ultimate.ogg", EFFECTS_VOLUME, 0);
    //! muda o estado do personagem para o ataque especial
    change_character_state(SPECIAL_STATE);
}
