/** \file character_choose_level.h
  * \brief Esta é o arquivo da classe do level CharacterChooseLevel que mostra o menu para a seleão
  *  dos personagens
  */
#ifndef CHARACTER_CHOOSE_LEVEL_h
#define CHARACTER_CHOOSE_LEVEL_h

//faz o import das classes da ijegine
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>

//import de classes do jogo
#include "character_selection.h"

//import de bibliotecas da linguagem
#include <string>
#include <memory>
#include <vector>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using namespace ijengine;

/** CharacterChooseLevel : public Level, public GameEventsListener
 *  \brief Classe usada para definir level do menu de seleção de personagens
 */
class CharacterChooseLevel : public Level, public GameEventsListener {
public:

    /** \fn CharacterChooseLevel(const string& next = "")
      * \public
      * \brief Método construtor
      * \param next const string& Parametro para o proximo level. Valor constante igual " ",
      *
      */
    CharacterChooseLevel(const string& next = "");

    /** \fn ~CharacterChooseLevel()
      * \public
      * \brief Método destrutor
      */
    ~CharacterChooseLevel();

    //enum para elementos da interface
    enum {
        BACKGROUND,
        PORTRAITS,
        ICONS
    };

    /** \fn const vector < int > get_players_characters()
      * \public
      * \brief função para fazer o "get" no atributo privado do vetor de personagens selecionados
      * \return const vector < int > retorna o vetor de personagens selecionados
      */
    const vector < int >
    get_players_characters() const { return character_choose_level_players_characters; }

    /** \var vector < int > character_choose_level_players_characters
      *  \brief Vetor com o id dos personagens possiveis jogaveis
      */
    vector < int > character_choose_level_players_characters;

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

    /** \fn on_event(const GameEvent& event)
      * \protected
      * \brief Encerra o level quando a o jogador precisiona o botão equivalente
      *  ao do light attack (x no joystick)
      * \param const event GameEvent& Entrada do usuário
      * \return bool retorna true quando ocorre o evento
      */
    bool on_event(const GameEvent& event);


private:

    /** \var bool character_choose_level_done
      *  \brief Variavel que é setada com True quando o level chega ao final
      */
    bool character_choose_level_done;

    /** \var string character_choose_level_next
      *  \brief Variavel com o nome do proximo level
      */
    string character_choose_level_next;

    /** \var int character_choose_level_start
      *  \brief Variavel para persistir o tempo de inicio de jogo
      */
    int character_choose_level_start;


    int character_choose_level_frame;

    /** \var int vector<int> character_choose_level_selected_characters
      *  \brief Vetor para os ids dos personagens que foram selecionados
      */
    vector<int> character_choose_level_selected_characters;

    /** \var int character_choose_level_current_player
      *  \brief id do player que esta fazendo a seleção
      */
    int character_choose_level_current_player;
    /** \var int character_choose_level_number_of_players
      *  \brief numero de jogadores que estão na seleção de personagens
      */
    int character_choose_level_number_of_players;

    /** \var vector<CharacterSelection *> character_choose_level_character_selections
      *  \brief Vetor de CharacterSelection de personagem
      */
    vector<CharacterSelection *> character_choose_level_character_selections;

    /** \var int character_choose_level_current_player_character
      *  \brief id do personagem que esta na com o foco
      */
    int character_choose_level_current_player_character;

    /** \var shared_ptr<Texture> character_choose_level_textures
      *  \brief Vetor com as texturas utilizadas para renderizar o level
      */
    vector< shared_ptr<Texture> > character_choose_level_textures;

};

#endif
