/** \file infiltrator.cpp
  * \brief Este é o arquivo da classe Infiltrator que é filha da classe Character.
  */

#include "infiltrator.h"
#include "ije02_game.h"
#include "light_attack.h"

//! Vida total do personagem
#define MAX_LIFE 100
//! Poder de ataque (special) do infiltrador
#define INFILTRATOR_SPECIAL_COOLDOWN 5000
//! Poder de ataque (heavy_atack) do infiltrador
#define INFILTRATOR_ATTACK_COOLDOWN 2000
//! Poder de ataque (light_atack) do infiltrador
#define INFILTRATOR_LIGHT_ATTACK_COOLDOWN 300
//! Poder de defesa do infiltrador
#define INFILTRATOR_DEFENSE_COOLDOWN 300

/** \fn Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
  * \public
  * \brief Método Construtor
  * \param sprite_paths - desenha personagem
  * \param id - identificador do personagem
  * \param x - posição no eixo x
  * \param y - posição no eixo y
  * \param character_code - codigo do personagem
  */
Infiltrator::Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    //! Poder de ataque especial - 5000
    character_special_cooldown = INFILTRATOR_SPECIAL_COOLDOWN;
    //! Poder de ataque heavy_atack - 2000
    character_heavy_attack_cooldown = INFILTRATOR_HEAVY_ATTACK_COOLDOWN;
    //! Poder de ataque light_atack - 300
    character_light_attack_cooldown = INFILTRATOR_LIGHT_ATTACK_COOLDOWN;
    //! Poder de defesa - 300
    character_defense_cooldown = INFILTRATOR_DEFENSE_COOLDOWN;
    //! Último uso do poder especial
    character_last_used_special = -INFILTRATOR_SPECIAL_COOLDOWN;
    //! Último uso do poder heavy_atack   
    character_last_used_heavy_attack = -INFILTRATOR_HEAVY_ATTACK_COOLDOWN;
    //! Último uso do poder ligth_atack
    character_last_used_light_attack = -INFILTRATOR_LIGHT_ATTACK_COOLDOWN;
    //! Último uso da defesa
    character_last_used_defense = -INFILTRATOR_DEFENSE_COOLDOWN;
    //! Personagem ativo 
    character_active = true;
}

/** \fn do_heavy_attack()
  * \protected
  * \brief Método que executa um ataque pesado
  */
void
Infiltrator::do_heavy_attack()
{
    //! Som do poder heavy_atack
    audio::play_sound_effect("res/sound/fx/infiltrador_heavy.ogg", EFFECTS_VOLUME, 0);
    //! Personagem deixa de ficar ativo
    character_active = false;
    Character::character_active = false;
    //! Muda o estado do personagem
    change_character_state(HEAVY_ATTACK_STATE);
}

/** \fn do_light_attack()
  * \protected
  * \brief Método que executa um ataque leve
  */
void
Infiltrator::do_light_attack() {
    //! Som do poder light_atack
    audio::play_sound_effect("res/sound/fx/infiltrador_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    //! Posição do ataque no eixo X - tipo Double
    double light_attack_x_pos = 0.0;

    //! Personagem se movimentando para direita
    if(character_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    //! Personagem se movimentando para esquerda ou outros
    else{
        light_attack_x_pos = x() - 15;
    }

    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));

    //! Muda o estado do personagem
    change_character_state(LIGHT_ATTACK_STATE);
}

/** \fn do_defense()
  * \protected
  * \brief Método que executa uma defesa
  */
void
Infiltrator::do_defense() {
    //! Som da defesa
    audio::play_sound_effect("res/sound/fx/infiltrador_block.ogg", EFFECTS_VOLUME, 0);
    //! Muda o estado do personagem
    change_character_state(DEFENSE_STATE);
}

/** \fn do_special()
  * \protected
  * \brief Método que executa um ataque especial
  */
void
Infiltrator::do_special() {
    //! Som do ataque especial
    audio::play_sound_effect("res/sound/fx/infiltrador_ultimate.ogg", EFFECTS_VOLUME, 0);
    //! Muda o estado do personagem
    change_character_state(SPECIAL_STATE);
}

/** \fn active()
  * \public
  * \brief Retorna verdadeiro se o personagem está ativo.
  * \return bool
  */
bool
Infiltrator::active() const {
    return Character::character_active;
}
