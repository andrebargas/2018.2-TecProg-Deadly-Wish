#include "soldier.h"
#include "spear.h"
#include "light_attack.h"
#include "ije02_game.h"

//! Vida total do personagem
#define MAX_LIFE 120
//! Intervalo de tempo de uso da Knight_special
#define KNIGHT_SPECIAL_COOLDOWN 5000
//! Intervalo de tempo de uso da heavy_atack
#define KNIGHT_HEAVY_ATTACK_COOLDOWN 2000
//! Intervalo de tempo de uso da light_atack
#define KNIGHT_LIGHT_ATTACK_COOLDOWN 300
//! Intervalo de tempo de uso da defense_cooldown
#define KNIGHT_DEFENSE_COOLDOWN 300

    
/** \fn Soldier(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
  * \public
  * \brief Método Construtor
  * \param sprite_paths - desenha personagem
  * \param id - identificador do personagem
  * \param x - posição no eixo x
  * \param y - posição no eixo y
  *\param character_code - codigo do personagem
*/
Soldier::Soldier(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    //! tempo de uso de ataque - 5000
    character_special_cooldown = SOLDIER_SPECIAL_COOLDOWN;
    //! tempo de uso de ataque - 2000
    character_heavy_attack_cooldown = SOLDIER_HEAVY_ATTACK_COOLDOWN;
    //! tempo de uso de ataque - 300
    character_light_attack_cooldown = SOLDIER_LIGHT_ATTACK_COOLDOWN;
    //! tempo de uso de defesa - 300
    character_defense_cooldown = SOLDIER_DEFENSE_COOLDOWN;
    //! tempo de uso do poder especial
    character_last_used_special = -character_special_cooldown;
    //! reseta ultimo uso do poder pesado   
    character_last_used_heavy_attack = -character_heavy_attack_cooldown;
    //! reseta ultimo uso do poder leve
    character_last_used_light_attack = -character_light_attack_cooldown;
    //! reseta ultimo uso da defesa
    character_last_used_defense = -character_defense_cooldown;
    //! reseta personagem ativo 
    character_active = true;
}

/** \fn do_heavy_attack()
  * \protected
  * \brief Método poder do ataque: 2000
*/
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

/** \fn do_light_atack()
  * \protected
  * \brief Método poder do ataque: 300
*/

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
/** \fn do_defense()
  * \protected
  * \brief Método poder de defesa: 300
*/
void
Soldier::do_defense() {
    //! som da defesa
    audio::play_sound_effect("res/sound/fx/soldier_block.ogg", EFFECTS_VOLUME, 0);
    //! muda o estado para defesa
    change_character_state(DEFENSE_STATE);
}

/** \fn do_special()
  * \protected
  * \brief Método poder do ataque: 5000
*/
void
Soldier::do_special() {
    //! som do ataque especial
    audio::play_sound_effect("res/sound/fx/soldier_ultimate.ogg", EFFECTS_VOLUME, 0);
    //! muda o estado do personagem para o ataque especial
    change_character_state(SPECIAL_STATE);
}
