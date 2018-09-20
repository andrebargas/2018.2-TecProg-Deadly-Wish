/** \file menu_level.h
  * \brief Esta é o arquivo da classe do level MenuLevel que mostra o menu para a seleão do modo de jogo
  */
#ifndef MENU_LEVEL_H
#define MENU_LEVEL_H

//Import dos arquivos da ijegine
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>

//import de bibliotecas da linguagem
#include <string>
#include <memory>
#include <vector>

using std::string;
using std::vector;
using std::shared_ptr;

using ijengine::Level;
using ijengine::Canvas;
using ijengine::Texture;
using ijengine::Event;

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


/** class MenuLevel : public Level, public GameEventsListener
 *  \brief Classe usada para definir level do menu de seleção do modo de jogo. É a primeira fase do
 *  jogo
 */
class MenuLevel : public Level, public GameEventsListener {
public:

    /** \fn MenuLevel(const string& next = "")
      * \public
      * \brief Método construtor
      * \param next const string& Parametro para o proximo level. Valor constante igual " ",
      *
      */
    MenuLevel(const string& next = "");

    /** \fn ~MenuLevel()
      * \public
      * \brief Método destrutor
      */
    ~MenuLevel();

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

    /** \fn update_position()
      * \protected
      * \brief atualiza a posição do seletor do menu
      * \return void
      */
    void update_position();

    /** \fn on_event(const GameEvent& event)
      * \protected
      * \brief Encerra o level quando a o jogador precisiona o botão equivalente
      *  ao do light attack (x no joystick)
      * \param event const GameEvent& Entrada do usuário
      * \return bool retorna true quando ocorre o evento
      */
    bool on_event(const GameEvent& event);

private:

    /** \var bool menu_level_done
      *  \brief Variavel que é setada com True quando o level chega ao final
      */
    bool menu_level_done;
    /** \var string menu_level_next
      *  \brief Variavel com o nome do proximo level
      */
    string menu_level_next;
    /** \var int menu_level_start
      *  \brief Variavel para persistir o tempo de inicio de jogo
      */
    int menu_level_start;
    /** \var int menu_level_option_y_position
      *  \brief Posição da opção de jogo no eixo y
      */
    int menu_level_option_y_position;

    /** \var int menu_level_current_option
      *  \brief Posição do foco de seleção do jogador na escolha do modo de jogo
      */
    int menu_level_current_option;

    //enum para as opções de jogo
    enum {
            BASE_OPTION,
            DEATHMATCH_OPTION,
            CREDITS
        };

    enum {
            BACKGROUND,
            POINTER
        };

    /** \var shared_ptr<Texture> menu_level_textures
      *  \brief Vetor com as texturas utilizadas para renderizar o level
      */
    vector< shared_ptr<Texture> > menu_level_textures;

    /** \var shared_ptr<string> menu_level_options
      *  \brief Vetor com o texto das opções de jogo
      */
    vector < string > menu_level_options;
};

#endif
