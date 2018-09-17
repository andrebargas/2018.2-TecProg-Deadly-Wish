/** \file winner_level.h
  * \brief Esta é o arquivo da classe do level WinnerLevel, que é ativado quando algum player ganha
  *  o jogo.
  */
#ifndef WINNER_LEVEL_H
#define WINNER_LEVEL_H

//Incluindo arquivos da ijengine
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

using namespace ijengine;

//UC
#define MAX_WIDTH 16
#define MAX_HEIGHT 12

/** \class WinnerLevel winner_level.h "include/winner_level.h"
 *  \brief Classe usada para definir level que aparece no final do jogo, quando algum dos
 *  players é o vencedor.
 */
class WinnerLevel : public Level {
public:
    /** \fn WinnerLevel(const string& next = "", int winner_player = -1)
      * \public
      * \brief Método construtor
      * \param next const string& Parametro para o proximo level. Valor constante igual " ",
      * final do jogo.
      * \param winner_player int Id do player ganhador. É iniciado com "-1" para que não o seja
      * level não seja iniciado já com um ganhador.
      */
    WinnerLevel(const string& next = "", int winner_player = -1);
    /** \fn ~WinnerLevel()
      * \public
      * \brief Método destrutor
      */
    ~WinnerLevel();

    /** \fn done()
      * \public
      * \brief Retorna verdadeiro quando o level chega ao final. Nome não pode ser mudado
      * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
      * \return bool retorna 'true' se o level acabou
      */
    bool done() const;
    /** \fn next()
      * \public
      * \brief Retorna qual sera o proximo level. Nome não pode ser mudado
      * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
      * \return string retorna qual sera o proximo level
      */
    string next() const;

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
    /** \fn set_congratulations_string()
      * \protected
      * \brief Faz o 'set' da string usada na parabenização do jogador ao ganhar o jogo
      * \return void
      */
    void set_congratulations_string();

private:

    /** \var bool winner_level_done
      *  \brief Variavel que é setada com True quando o level chega ao final
      */
    bool winner_level_done;

    /** \var string winner_level_next
      *  \brief Varivel com o nome do proximo level.
      */
    string winner_level_next;
    /** \var string winner_level_congratulations
      *  \brief Variavel que usada para a frase que é mostrada ao jogador ao ganhar o jogo
      */
    string winner_level_congratulations;
    /** \var int winner_level_start
      *  \brief Varivel que é iniciada quando o level começa
      */
    int winner_level_start;
    /** \var int winner_level_winner_player
    *  \brief Variavel como o id do player vencedor
    */
    int winner_level_winner_player;
    /** \var shared_ptr<Texture> m_texture
    *  \brief Variavel para a textura usada na renderização do level
    */
    shared_ptr<Texture> m_texture;
};

#endif
