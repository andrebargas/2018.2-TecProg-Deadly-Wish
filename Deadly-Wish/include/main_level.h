/** \file main_level.h
  * \brief Esta é o arquivo da classe do level MainLevel que acontece depois que os jogadores
  * escohem os persogens e o modo de jogo.
  */
#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

#include "character_factory.h"
#include "base.h"

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>

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

//Tamanho da tela durante o level
#define MAX_WIDTH 16
#define MAX_HEIGHT 12

/** \class MainLevel main_level.h "include/main_level.h"
 *  \brief Classe usada para definir level que aparece após a seleção de personagem e escolha do
 *  modo de jogo. É onde o core do jogo acontece.
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

    enum {
        INFILTRATOR,
        MAGE,
        SOLDIER,
        KNIGHT
    };

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
      *  #winner_level_start. Nome não pode ser mudado por ser um metodo herdado da classe pai,
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

    void set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos);
    void verify_bases();

private:
    bool main_level_done;
    string main_level_next;
    int main_level_start;
    bool main_level_has_winner;

    vector <Base* > main_level_bases;
    vector < int > main_level_players_characters;
    shared_ptr<Texture> main_level_texture;
    int main_level_map[MAX_WIDTH][MAX_HEIGHT];
    CharacterFactory main_level_character_factory;
};

#endif
