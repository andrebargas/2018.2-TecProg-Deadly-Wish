/** \file character_choose_level.cpp
  * \brief Esta é o arquivo da classe do level CharacterChooseLevel que mostra o menu para a seleão
  *  dos personagens
  */

#include "character_choose_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"
#include "test_level_factory.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/rectangle.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;
using namespace ijengine;
using std::vector;

/** \fn CharacterChooseLevel(const string& next = "")
  * \public
  * \brief Método construtor
  * \param next const string& Parametro para o proximo level. Valor constante igual " ",
  *
  */
CharacterChooseLevel::CharacterChooseLevel(const string& next_level)
    : character_choose_level_done(false), character_choose_level_next(next_level),
      character_choose_level_start(-1)
{
    character_choose_level_textures.push_back
    (resources::get_texture("character_selection/character_selection_background.png"));
    character_choose_level_textures.push_back
    (resources::get_texture("character_selection/CharacterPortraits.png"));
    character_choose_level_textures.push_back
    (resources::get_texture("character_selection/Icons.png"));

    character_choose_level_number_of_players = 4;
    character_choose_level_current_player = 1;
    character_choose_level_frame = 0;

    int base_x = 120;
    for(int i = 0; i < character_choose_level_number_of_players; i++) {
        character_choose_level_character_selections.push_back(new CharacterSelection("character_selection/Pointers.png", base_x + 10 * i, 73, i));
        add_child(character_choose_level_character_selections[i]);
    }

    character_choose_level_selected_characters.resize(4);

    printf("antes de add o filho\n");
    printf("depois de add o filho\n");
    fflush(stdout);

    event::register_listener(this);
}

/** \fn ~CharacterChooseLevel()
  * \public
  * \brief Método destrutor
  */
CharacterChooseLevel::~CharacterChooseLevel() {
    event::unregister_listener(this);
}

// PBS
/** \fn done()
  * \public
  * \brief Retorna verdadeiro quando o level chega ao final. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return bool retorna 'true' se o level acabou
  */
bool
CharacterChooseLevel::done() const
{
    return character_choose_level_done;
}

//PBS
/** \fn next()
  * \public
  * \brief Retorna qual sera o proximo level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string retorna qual sera o proximo level
  */
string
CharacterChooseLevel::next() const
{
    return character_choose_level_next;
}


//PBS
/** \fn audio()
  * \public
  * \brief Retorna qual é o audio do level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string string constante "."
  */
string
CharacterChooseLevel::audio() const {
    return "music/menu_v1.ogg";
}


/** \fn update_self(unsigned now, unsigned last)
  * \protected
  * \brief Função para atualizar o tempo de inicio do level, e setar atributo
  *  #winner_level_start. Nome não pode ser mudado por ser um metodo herdado da classe pai,
  *  protegida pelo escopo do projeto
  * \param now unsigned Tempo atual do jogo
  * \param last unsigned
  * \return void
  */
void
CharacterChooseLevel::update_self(unsigned now, unsigned)
{
    int dones = 0;
    for(int i = 0; i < character_choose_level_number_of_players; i++) {
        dones += character_choose_level_character_selections[i]->chosen();
    }

    if(dones == 1) {
        if(!character_choose_level_done) {
            for(int i = 0; i < character_choose_level_number_of_players; i++) {
                int selection = character_choose_level_character_selections[i]->current_selection();
                // if(selection == 0) {
                //     selection = 3;
                // }
                character_selection::players_characters.push_back(selection);
            }
        }
        character_choose_level_done = true;
    }
}


/** \fn draw_self(Canvas *canvas, unsigned now, unsigned last)
  * \protected
  * \brief Método que faz o desenho grafico do jogo. Nome não pode ser mudado por ser um
  *  metodo herdado da classe pai, protegida pelo escopo do projeto
  * \param canvas Canvas* Ponteiro para objeto da classe responsavel pela renderização do jogo.
  * \param now unsigned Tempo atual do jogo
  * \param last unsigned
  * \return void
  */
void
CharacterChooseLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();
    // background
    canvas->draw(character_choose_level_textures[BACKGROUND].get(), 0, 0);

    vector<Rectangle> portrait_rects;
    vector< pair<int, int> > rects_positions {{12, 12}, {208, 12}, {12, 128}, {208, 128}};
    for(int i = 0; i < character_choose_level_number_of_players; i++) {
        Rectangle rect {(double) character_choose_level_character_selections[i]->current_selection() * 100, i * 100, 100, 100};
        portrait_rects.push_back(rect);
        canvas->draw(character_choose_level_textures[PORTRAITS].get(), rect, rects_positions[i].first, rects_positions[i].second);
    }

    vector< pair<double, double> > icons_start_coordinates {{122.4, 83.33}, {122.4, 126.66}, {165.6, 83.83},
        {165.6, 126.66}};

    for(int i = 0; i < 4; i++) {
        Rectangle rect {(double) 32 * i, 0.0, 32, 32};
        canvas->draw(character_choose_level_textures[ICONS].get(), rect, icons_start_coordinates[i].first, icons_start_coordinates[i].second);
    }
}

/** \fn on_event(const GameEvent& event)
  * \protected
  * \brief Encerra o level quando a o jogador precisiona o botão equivalente
  *  ao do light attack (x no joystick)
  * \param const event GameEvent& Entrada do usuário
  * \return bool retorna true quando ocorre o evento
  */
bool
CharacterChooseLevel::on_event(const GameEvent& event) {
    return false;
}
