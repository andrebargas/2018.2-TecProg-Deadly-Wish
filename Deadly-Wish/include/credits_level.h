/** \file credits_level.h
  * \brief Esta é o arquivo da classe do level DeathMatchLevel que mostra os creditos do jogo
  * com o nome de seus criadores e etc.
  */
#ifndef CREDITS_LEVEL_H
#define CREDITS_LEVEL_H

//Import das classes da ijengine
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>

//Import de bibliotecas da linguagem
#include <string>
#include <memory>
#include <vector>
#include <utility>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using namespace ijengine;

//DC
/** \def MAX_WIDTH 16
  * \brief define largura da tela do level
  */
 #define MAX_WIDTH 16
 /** \def MAX_HEIGHT 12
   * \brief define altura da tela do level
   */
#define MAX_HEIGHT 12

/** class CreditsLevel : public Level, public GameEventsListener
 *  \brief Classe usada para definir level de creditos do jogo, com o nome de seus criadores
 */
class CreditsLevel : public Level, public GameEventsListener  {
public:

    /** \fn CreditsLevel(const string& next = "")
      * \public
      * \brief Método construtor
      * \param next const string& Parametro para o proximo level. Valor constante igual " ",
      * final do jogo.
      */
    CreditsLevel(const string& next = "");

    /** \fn ~CreditsLevel()
      * \public
      * \brief Método destrutor
      */
    ~CreditsLevel();

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
      *  #credits_level_start. Nome não pode ser mudado por ser um metodo herdado da classe pai,
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

    /** \fn set_credits_strings()
      * \protected
      * \brief seta a qual sera o texto que ira aparecer nos creditos
      * \return void
      */
    void set_credits_strings();

    /** \fn on_event(const GameEvent& event)
      * \protected
      * \brief Encerra o level quando a o jogador precisiona o botão equivalente
      *  ao do light attack (x no joystick)
      * \param event GameEvent& Entrada do usuário
      * \return bool retorna true quando ocorre o evento
      */
    bool on_event(const GameEvent& event);

private:
  /** \var bool credits_level_done
    *  \brief Variavel que é setada com True quando o level chega ao final
    */
    bool credits_level_done;
    /** \var string credits_level_next
      *  \brief Variavel com o nome do proximo level
      */
    string credits_level_next;
    /** \var vector <string> credits_level_strings
      *  \brief Variavel com os textos que irão aparecer nos creditos
      */
    vector <string> credits_level_strings;

    /** \var int credits_level_start
      *  \brief Variavel para persistir o tempo de inicio de jogo
      */
    int credits_level_start;
    /** \var int credits_level_winner_player
      *  \brief Variavel id do player vencedor
      */
    int credits_level_winner_player;
    /** \var shared_ptr<Texture> credits_level_winner_player
      *  \brief Vetor com as texturas utilizadas para renderizar o level
      */
    shared_ptr<Texture> m_texture;
};

#endif
