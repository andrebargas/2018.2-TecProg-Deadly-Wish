/** \file knight.cpp
  * \brief Este é o arquivo da classe Knight que é filha da classe Character.
  */

#include "knight.h"
#include "light_attack.h"
#include "ije02_game.h"

//! Vida total do personagem
#define MAX_LIFE 300
//! Poder de ataque (special) do cavaleiro
#define KNIGHT_SPECIAL_COOLDOWN 5000
//! Poder de ataque (heavy_atack) do cavaleiro
#define KNIGHT_HEAVY_ATTACK_COOLDOWN 2000
//! Poder de ataque (light_atack) do cavaleiro
#define KNIGHT_LIGHT_ATTACK_COOLDOWN 300
//! Poder de defesa do cavaleiro
#define KNIGHT_DEFENSE_COOLDOWN 300

/** \fn Knight(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
  * \public
  * \brief Método Construtor
  * \param sprite_paths - desenha personagem
  * \param id - identificador do personagem
  * \param x - posição no eixo x
  * \param y - posição no eixo y
  * \param character_code - codigo do personagem
  */
Knight::Knight(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    //! Poder de ataque especial - 5000
    character_special_cooldown = KNIGHT_SPECIAL_COOLDOWN;
    assert(character_special_cooldown == 5000);
    
    //! Poder de ataque heavy_atack - 2000
    character_heavy_attack_cooldown = KNIGHT_HEAVY_ATTACK_COOLDOWN;
    assert(character_heavy_attack_cooldown == 2000);
    
    //! Poder de ataque ligth_atack - 300
    character_light_attack_cooldown = KNIGHT_LIGHT_ATTACK_COOLDOWN;
    
    assert(character_light_attack_cooldown == 300);
    //! Poder de defesa - 300
    character_defense_cooldown = KNIGHT_DEFENSE_COOLDOWN;
    assert(character_defense_cooldown == 300);

    //! Último uso do special
    character_last_used_special = -character_special_cooldown;
    assert(character_last_used_special == -5000);

    //! Último uso do heavy_atack
    character_last_used_heavy_attack = -character_heavy_attack_cooldown;
    assert(character_last_used_heavy_attack == -2000);

    //! Último uso do light_atack 
    character_last_used_light_attack = -character_light_attack_cooldown;
    assert(character_last_used_light_attack == -300);

    //! ÚLtimo uso da defesa
    character_last_used_defense = -character_defense_cooldown;
    assert(character_last_used_defense == -300);

    //! Indica que o peronsagem esta ativo
    character_active = true;
    assert(character_active == true);
}

/** \fn do_heavy_attack()
  * \protected
  * \brief Método que executa um ataque pesado
  */
void
Knight::do_heavy_attack()
{
    audio::play_sound_effect("res/sound/fx/pesadao_heavy.ogg", EFFECTS_VOLUME, 0);
    change_character_state(HEAVY_ATTACK_STATE);
}

/** \fn do_light_attack()
  * \protected
  * \brief Método que executa um ataque leve
  */
void
Knight::do_light_attack() {
    audio::play_sound_effect("res/sound/fx/pesadao_light.ogg", EFFECTS_VOLUME, 0);
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double light_attack_x_pos = 0.0;
    assert (light_attack_x_pos == 0.0);
    if(character_moving_state == MOVING_RIGHT) {
        light_attack_x_pos = x() + 15;
    }
    else{
        light_attack_x_pos = x() - 15;
    }

    p->add_child(new LightAttack(p, get_id(), light_attack_x_pos, y()));

    change_character_state(LIGHT_ATTACK_STATE);
}

/** \fn do_defense()
  * \protected
  * \brief Método que executa uma defesa
  */
void
Knight::do_defense() {
    audio::play_sound_effect("res/sound/fx/pesadao_block.ogg", EFFECTS_VOLUME, 0);
    change_character_state(DEFENSE_STATE);
}

/** \fn do_special()
  * \protected
  * \brief Método que executa um ataque especial
  */
void
Knight::do_special() {
    change_character_state(SPECIAL_STATE);
}
