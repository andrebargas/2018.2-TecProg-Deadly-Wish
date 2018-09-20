/** \file main_level.h
  * \brief Esta é o arquivo da classe do level MainLevel que acontece depois que os jogadores
  * escohem os persogens e o modo de jogo igual a "modo bases".
  */
#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

//imports da classe do jogo
#include "character_factory.h"
#include "base.h"

//imports de classes da ijengine
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>

//import de bibliotecas da linguagem
#include <string>
#include <memory>
#include <vector>
#include <utility>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using ijengine::Level;
using ijengine::Canvas;
using ijengine::Texture;
using ijengine::Event;

//DC
/** \def MAX_WIDTH 16
  * \brief define largura da tela do level
  */
 #define MAX_WIDTH 16
 /** \def MAX_HEIGHT 12
   * \brief define altura da tela do level
   */
#define MAX_HEIGHT 12

/** \class MainLevel main_level.h "include/main_level.h"
 *  \brief Classe usada para definir level que aparece após a seleção de personagem e escolha do
 *  modo de jogo. É onde o core do jogo acontece no modo "bases".
 */
class MainLevel : public Level {
public:
    /** \fn MainLevel(const string& next = "", vector < int > players_characters = {})
      * \public
      * \brief Método construtor
      * \param next const string& Parametro para o proximo level. Valor constante igual " ",
      * final do jogo.
      * \param players_characters vector< int > Lista de character presentes no jogo
      */
    MainLevel(const string& next = "", vector < int > players_characters = {});

    /** \fn ~MainLevel
      * \public
      * \brief Método destrutor
      */
    ~MainLevel();

    // Enum para os personagens jogaveis
    enum {
        INFILTRATOR,
        MAGE,
        SOLDIER,
        KNIGHT
    };

    //enum para possiveis players
    enum {
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4
    };

    // PBS
    /** \fn done()
      * \public
      * \brief Retorna verdadeiro quando o level chega ao final. Nome não pode ser mudado
      * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
      * \return bool retorna 'true' se o level acabou
      */
    bool done() const;

    //PBS
    /** \fn next()
      * \public
      * \brief Retorna qual sera o proximo level. Nome não pode ser mudado
      * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
      * \return string retorna qual sera o proximo level
      */
    string next() const;

    //PBS
    /** \fn audio()
      * \public
      * \brief Retorna qual é o audio do level. Nome não pode ser mudado
      * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
      * \return string string constante "."
      */
    string audio() const;

protected:
    /** \fn update_self(unsigned now, unsigned last)
      * \protected
      * \brief Função para atualizar o tempo de inicio do level, e setar atributo
      *  winner_level_start. Nome não pode ser mudado por ser um metodo herdado da classe pai,
      *  protegida pelo escopo do projeto
      * \param now unsigned Tempo atual do jogo
      * \param last unsigned
      * \return void
      */
    void update_self(unsigned now, unsigned last);
    /** \fn draw_self(Canvas *canvas, unsigned now, unsigned last)
      * \protected
      * \brief Método que faz o desenho grafico do jogo. Nome não pode ser mudado por ser um
      *  metodo herdado da classe pai, protegida pelo escopo do projeto
      * \param canvas Canvas* Ponteiro para objeto da classe responsavel pela renderização do jogo.
      * \param now unsigned Tempo atual do jogo
      * \param last unsigned
      * \return void
      */
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    /** \fn set_players_characters_position(unsigned player_id, double& axis_x_position,
      *                                     double& axis_y_position)
      * \protected
      * \brief seta a posição inicial de cada persongem
      * \param player_id unsigned Id do player que tera a posição do personagem setada
      * \param axis_x_position double& Endereço da posição do persoangem no eixo x
      * \param axis_y_position double& Endereço da posição do persoangem no eixo y
      * \return void
      */
    void set_players_characters_position(unsigned player_id, double& axis_x_position, double& axis_y_position);
    /** \fn verify_bases()
      * \protected
      * \brief Verifica se ainda há bases remanecentes, e se existe um vencedor
      * \return void
      */
    void verify_bases();

private:
    /** \var bool main_level_done
      *  \brief Variavel que é setada com True quando o level chega ao final
      */
    bool main_level_done;
    /** \var bool main_level_next
      *  \brief Variavel com o nome do proximo level
      */
    string main_level_next;
    /** \var bool main_level_start
      *  \brief Variavel para persistir o tempo de inicio de jogo
      */
    int main_level_start;
    /** \var bool main_level_has_winner
      *  \brief Variavel que é setada com true quando existe um jogador ganhador
      */
    bool main_level_has_winner;
    /** \var vector <Base* > main_level_bases
      *  \brief Vetor com os ponteiros para as bases presentes no jogo
      */
    vector <Base* > main_level_bases;
    /** \var vector < int > main_level_players_characters
      *  \brief Vetor com o código de cada personagem presente no jogo
      */
    vector < int > main_level_players_characters;
    /** \var shared_ptr<Texture> main_level_texture
      *  \brief Vetor com as texturas utilizadas para renderizar o jogo
      */
    shared_ptr<Texture> main_level_texture;
    /** \var int main_level_map[MAX_WIDTH][MAX_HEIGHT]
      *  \brief matriz para fazer o grid do jogo, com sua respectiva altura e largura
      */
    int main_level_map[MAX_WIDTH][MAX_HEIGHT];
    /** \var CharacterFactory main_level_character_factory
      *  \brief Instancia da classe CharacterFactory responsavel pela criação dos personagens do jogo
      */
    CharacterFactory main_level_character_factory;
};

#endif
