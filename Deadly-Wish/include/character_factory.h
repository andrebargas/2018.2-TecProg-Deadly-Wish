/** \file character_factory.h
  * \brief Esta é o arquivo da classe que cria os personagens do jogo.
  */
#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

// Inclui arquivos das classes dos pesornagens
#include "character.h"
#include "mage.h"
#include "infiltrator.h"
#include "soldier.h"
#include "knight.h"
// Inclui arquivo com metodos auxiliares
#include "util.h"

#include <vector>
#include <string>


using std::vector;
using std::string;

using namespace util;

/** \class CharacterFactory character_factory.h "include/character_factory.h"
 *  \brief Classe usada para instanciar objetos de personagens do jogo. Sendo relativos a
 *  escolha dos jogadores em cada partida.
 */
class CharacterFactory {
public:
  /** \fn CharacterFactory()
    * \public
    * \brief Método construtor
    */
    CharacterFactory();
    /** \fn ~CharacterFactory()
      * \public
      * \brief Método destrutor
      */
    ~CharacterFactory();

    /** enum para os tipos de persongens possiveis */
    enum {
        KNIGHT,
        SOLDIER,
        MAGE,
        INFILTRATOR
    };
    /** \fn Character* make_character(int character_code, unsigned player_id, double x_pos, double y_pos)
      * \public
      * \brief Fução que instacia um pesornagem
      * \param character_code int codigo relacionado ao personagem do enum. Valor entre 0 e 3.
      * \param player_id unsigned id do players. Valor entre 1 e 4.
      * \param x_position double  posição inicial do personagem a ser criado no eixo x
      * \param y_position double  posição inicial do personagem a ser criado no eixo y
      * \return um ponteiro para um Character.
      */
    Character* make_character(int character_code, unsigned player_id, double x_position, double y_position);

protected:
    /** \enum Players
      * enum paras cada um dos playes
      */
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;

    /** \fn vector<string> choose_sprite_path(int character_code, unsigned player_id)
      * \protected
      * \brief Função que escolhe qual sera o caminho para o sprite de cada um dos jogadores e
      *  personagem, ja as cores e densenhos de cada um são diferentes.
      * \param character_code int Código de para o personagem
      * \param player unsigned Código de para o player
      * \return o vetor com paths paras as sprites no formato de String.
      */
    vector<string> choose_sprite_path(int character_code, unsigned player_id);
    /** \var vector<string> character_sprites_paths
      *  \brief Variavel para armazenar os caminhos para os sprites do personagem
      */
    vector<string> character_sprites_paths;
};
#endif
