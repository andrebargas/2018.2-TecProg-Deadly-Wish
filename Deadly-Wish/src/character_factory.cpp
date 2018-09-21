/** \file character_factory.cpp
  * \brief Este é o arquivo da classe que cria os personagens do jogo.
  */
#include "character_factory.h"

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

// Metodo construtor
CharacterFactory::CharacterFactory()
{

}

// Metodo destrutor
CharacterFactory::~CharacterFactory()
{

}

/** \fn Character* make_character(int character_code, unsigned player_id, double x_pos, double y_pos)
  * \public
  * \brief Fução que instacia um pesornagem
  * \param character_code int codigo relacionado ao personagem do enum. Valor entre 0 e 3.
  * \param player_id unsigned id do players. Valor entre 1 e 4.
  * \param x_position double  posição inicial do personagem a ser criado no eixo x
  * \param y_position double  posição inicial do personagem a ser criado no eixo y
  * \return um ponteiro para um Character.
  */
Character*
CharacterFactory::make_character(int character_code, unsigned player_id, double x_position, double y_position)
{
    character_sprites_paths = choose_sprite_path(character_code, player_id);


      //Switch case definir qual dos personagens sera criado.
    switch(character_code) {
        case INFILTRATOR:
            return new Infiltrator(character_sprites_paths, player_id, x_position, y_position, character_code);
            break;

        case MAGE:
            return new Mage(character_sprites_paths, player_id, x_position, y_position, character_code);
            break;

        case SOLDIER:
            return new Soldier(character_sprites_paths, player_id, x_position, y_position, character_code);
            break;

        case KNIGHT:
            return new Knight(character_sprites_paths, player_id, x_position, y_position, character_code);
            break;
        //Caso entrada seja invalida dipara mensagem no log e retorna nullptr
        default:
            printf("Valor inválido na CharacterFactory\n");
            return nullptr;
            break;
    }
}

/** \fn vector<string> choose_sprite_path(int character_code, unsigned player_id)
  * \protected
  * \brief Função que escolhe qual sera o caminho para o sprite de cada um dos jogadores e
  *  personagem, ja as cores e densenhos de cada um são diferentes.
  * \param character_code int Código de para o personagem
  * \param player unsigned Código de para o player
  * \return o vetor com paths paras as sprites no formato de String.
  */
vector<string>
CharacterFactory::choose_sprite_path(int character_code, unsigned player_id)
{
    /** \var strings choosen_class
      * Varaivel para salver nome do tipo de personagem a partir de seu código
      */
    string choosen_class;

    // Switch atribuir a variavel choosen_class a partir da variavel character_code
    switch(character_code) {
        case INFILTRATOR:
            choosen_class = "Infiltrator";
            break;

        case MAGE:
            choosen_class = "Mage";
            break;

        case SOLDIER:
            choosen_class = "Soldier";
            break;

        case KNIGHT:
            choosen_class = "Pesado";
            break;

        default:
            printf("Valor inválido na CharacterFactory\n");
            break;
    }


    /** \var directory string
      * Varaivel para salver nome da cor da equipe de cada um dos players
      */
    string directory;
    // Switch atribuir a variavel directory a partir da variavel player_id
    switch(player_id) {
        case PLAYER_1:
            directory = "Green";
            break;

        case PLAYER_2:
            directory = "Blue";
            break;

        case PLAYER_3:
            directory = "Yellow";
            break;

        case PLAYER_4:
            directory = "Red";
            break;

        default:
            printf("Valor inválido na CharacterFactory\n");
            break;
    }

    /** \var sprite_vector vector<string>
      * Varaivel para armazenar todos os sprites paths de um personagem que são referentes
      * a cada CharacterState.
      */
    vector<string> sprite_vector;

    //sprite para o estado de IdleState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Idle.png");
    //sprite para o estado de MovingState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Walk.png");
    //sprite para o estado de DeathState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Death.png");
    //sprite para o estado de LightAttackState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Attack.png");
    //sprite para o estado de SpecialState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Special.png");
    //sprite para o estado de HeavyAttackState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Ultimate.png");
    //sprite para o estado de DefenseState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Defense.png");

    return sprite_vector;
}
