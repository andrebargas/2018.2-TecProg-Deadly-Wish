/** \file menu_level.cpp
  * \brief Esta é o arquivo da classe do level MenuLevel
  * \que mostra o menu para a seleão do modo de jogo
  */

#include "menu_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>

using namespace std;

//posição no eixo y da opção "modo bases"
#define BASE_OPTION_Y_POSITION 13
//posição no eixo y da opção "modo mata a mata"
#define DEATHMATCH_OPTION_Y_POSITION 33
//posição no eixo y da opção "creditos"
#define CREDITS_OPTION_Y_POSITION 53

/** \fn MenuLevel(const string& next = "")
  * \public
  * \brief Método construtor
  * \param next const string& Parametro para o proximo level. Valor constante igual " ",
  *
  */
MenuLevel::MenuLevel(const string& next_level)
    :menu_level_done(false), menu_level_next(next_level), menu_level_start(-1),
     menu_level_current_option(0)
{
    //para a musica que estava tocando e inicia a musica do level
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/menu.ogg", 60, 10);
    menu_level_textures.push_back(resources::get_texture("Titlecard.png"));
    menu_level_textures.push_back(resources::get_texture("character_selection/option_selection.png"));
    event::register_listener(this);
    menu_level_option_y_position = 13;

    menu_level_options.push_back("Modo Bases!");
    menu_level_options.push_back("Modo Mata-Mata!");
    menu_level_options.push_back("Créditos");

}

/** \fn ~MenuLevel()
  * \public
  * \brief Método destrutor
  */
MenuLevel::~MenuLevel() {
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
MenuLevel::done() const
{
    return menu_level_done;
}

//PBS
/** \fn next()
  * \public
  * \brief Retorna qual sera o proximo level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string retorna qual sera o proximo level
  */
string
MenuLevel::next() const
{
    return menu_level_next;
}

//PBS
/** \fn audio()
  * \public
  * \brief Retorna qual é o audio do level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string string constante "."
  */
string
MenuLevel::audio() const {
    return ".";
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
MenuLevel::update_self(unsigned now, unsigned)
{
    if (menu_level_start == -1)
        menu_level_start = now;
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
MenuLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    //Posição no eixo y da primeira opção no menu
    int option_y_pos = 5;
    canvas->clear();

    //Seta a fonte do texto usado no menu
    auto font = resources::get_font("Forelle.ttf", 20);
    canvas->set_font(font);

    //Define o tamanho da caixa de seleção que dara o highlight para o opção
    Rectangle rect {0.0, (menu_level_textures[POINTER]->h() / (double) 4), 9.0, 8.0};

    canvas->draw(menu_level_textures[BACKGROUND].get(), 0, 0);
    canvas->draw(menu_level_textures[POINTER].get(), rect, 100, menu_level_option_y_position);

    // Escreve as outras opções do menu
    for(string option : menu_level_options) {
        canvas->draw(option, 110, option_y_pos);
        //Faz uma quebra de linha com a distancia de 20px
        option_y_pos += 20;
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
MenuLevel::on_event(const GameEvent& event) {
    //Seleciona a opção que esta seleciona quando o usuário preciona a opção equivalente
    //ao input de light attack ( X no joystick)
    if(event.id() == game_event::LIGHT_ATTACK_P1) {
        //Seleciona o "modo mata mata"
        if(menu_level_current_option == DEATHMATCH_OPTION) {
            game_mode::choosen_mode = "deathmatch-mode";
        }
        //Seleciona o level dos creditos..
        else if(menu_level_current_option == CREDITS) {
            menu_level_next = "credits";
        }

        //Faz o set da variavel que indica quando o level termina
        menu_level_done = true;
        return true;
    }

    //Move a caixa de seleção do menu
    if(event.id() == game_event::MOVEMENT_P1) {

        string axis = event.get_property<string>("axis");

        //salva o direção no eixo do movimento em uma varivavel
        int value = event.get_property<int>("value");

        //caso o usuário mova para direita e esqueda
        if(axis == "X") {

            //caso ele mova para direita a caixa de seleção 'desce'
            if(value > 0) {
                menu_level_current_option = (menu_level_current_option + 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }

            //caso ele mova para esquerda a caixa de seleção 'sobe'
            else if(value < 0) {
                menu_level_current_option = (menu_level_current_option - 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
        }

        //caso ele mova o para cima e para baixo
        else if(axis == "Y") {

            //caso ele mova o cursor para 'baixo'
            if(value > 0) {
                menu_level_current_option = (menu_level_current_option + 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }

            //caso ele mova o cursor para 'cima'
            else if(value < 0) {
                menu_level_current_option = (menu_level_current_option - 1) % 3;
                audio::play_sound_effect("res/sound/fx/soldier_heavy.ogg", EFFECTS_VOLUME, 0);
            }
        }

        /* Caso a seleção tente ir depois do ultimo elemento, a caixa de seleção volta para
         * o topo da lista de opções
         */

        if(menu_level_current_option < 0) {
            menu_level_current_option += 3;
        }
        update_position();
        return true;
    }
    return false;
}

/** \fn update_position()
  * \protected
  * \brief atualiza a posição do seletor do menu
  * \return void
  */
void
MenuLevel::update_position()
{
    //Seta a posição das opções do menu
    switch(menu_level_current_option) {

        //faz o set da posição do 'modo bases'
        case BASE_OPTION:
            menu_level_option_y_position = BASE_OPTION_Y_POSITION;
            break;

        //faz o set da posição do modo 'mata a mata'
        case DEATHMATCH_OPTION:
            menu_level_option_y_position = DEATHMATCH_OPTION_Y_POSITION;
            break;

        //faz o set da opção creditos
        case CREDITS:
            menu_level_option_y_position = CREDITS_OPTION_Y_POSITION;
            break;

        //UC
        //Printa mensagem de erro
        default:
            printf("Error on update_position() menu level\n");
            break;
    }
}
