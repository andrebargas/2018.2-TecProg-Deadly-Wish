/** \file mage.cpp
  * \brief Este é o arquivo da classe Mage que é filha da classe Character.
  */

#include "mage.h"
#include "fireball.h"
#include "frost_nova.h"
#include "ije02_game.h"
#include "skill.h"
#include "light_attack.h"

#include <vector>
#include <string>

//! Vida total do personagem
#define MAX_LIFE 100
//! Poder de ataque (special) do mago
#define MAGE_SPECIAL_COOLDOWN 5000
//! Poder de ataque (heavy_atack) do mago
#define MAGE_HEAVY_ATTACK_COOLDOWN 2000
//! Poder de ataque (light_atack) do mago
#define MAGE_LIGHT_ATTACK_COOLDOWN 300
//! Poder de defesa do mago
#define MAGE_DEFENSE_COOLDOWN 300

using std::vector;
using std::string;

/** \fn Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
  * \public
  * \brief Método Construtor
  * \param sprite_paths - desenha personagem
  * \param id - identificador do personagem
  * \param x - posição no eixo x
  * \param y - posição no eixo y
  * \param character_code - codigo do personagem
  */
Mage::Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    //! Poder de ataque especial - 5000
    character_special_cooldown = MAGE_SPECIAL_COOLDOWN;
    //! Poder de ataque heavy_atack - 2000
    character_heavy_attack_cooldown = MAGE_HEAVY_ATTACK_COOLDOWN;
    //! Poder de ataque light_atack - 300
    character_light_attack_cooldown = MAGE_LIGHT_ATTACK_COOLDOWN;
    //! Poder de defesa - 300
    character_defense_cooldown = MAGE_DEFENSE_COOLDOWN;
    //! Último uso do poder special   
    character_last_used_special = -character_special_cooldown;
    //! Último uso do poder heavy_atack   
    character_last_used_heavy_attack = -character_heavy_attack_cooldown;
    //! Último uso do poder ligth_atack
    character_last_used_light_attack = -character_light_attack_cooldown;
    //! Último uso da defesa
    character_last_used_defense = -character_defense_cooldown;
    //! Personagem ativo 
    character_active = true;
}

/** \fn do_heavy_attack()
  * \protected
  * \brief Método que executa um ataque pesado
  */
void
Mage::do_heavy_attack()
{
    // executa o som do heavy_atack
    audio::play_sound_effect("res/sound/fx/mago_heavy.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    // Direção e posição a fireball (eixo x)
    double fireball_dx = 0.0;
    double fireball_x_pos = 0.0;

    // Se o personagem estiver se movendo para a direita
    if(character_moving_state == MOVING_RIGHT) {
        fireball_dx = 1.0;
        fireball_x_pos = x() + 20;
    }
    else{
        fireball_dx = -1.0;
        fireball_x_pos = x() - 20;
    }

    p->add_child(new Fireball(p, get_id(), fireball_x_pos, y(), fireball_dx, 0.0));

    // Muda o estado do personagem
    change_character_state(HEAVY_ATTACK_STATE);
}

/** \fn do_light_attack()
  * \protected
  * \brief Método que executa um ataque leve
  */
void
Mage::do_light_attack() {
    // executa o som do light_atack
    audio::play_sound_effect("res/sound/fx/mago_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    // posicao do ataque no eixo x
    double light_attack_x_pos = 0.0;

    // se o personagem estiver se movendo para a direita 
    if(character_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    else{
        light_attack_x_pos = x() - 15;
    }

    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));

    // Muda o estado do personagem
    change_character_state(LIGHT_ATTACK_STATE);
}

/** \fn do_defense()
  * \protected
  * \brief Método que executa uma defesa
  */
void
Mage::do_defense() {
    // executa o som de defesa
    audio::play_sound_effect("res/sound/fx/mago_block.ogg", EFFECTS_VOLUME, 0);
    // muda o estado do personagem
    change_character_state(DEFENSE_STATE);
}

/** \fn do_special()
  * \protected
  * \brief Método que executa um ataque especial
  */
void
Mage::do_special() {
    // executa o som do poder especial
    audio::play_sound_effect("res/sound/fx/mago_ultimate.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    p->add_child(new FrostNova(p, get_id(), x(), y(), 0.0, 0.0));

    // muda o estado do personagem
    change_character_state(SPECIAL_STATE);
}
