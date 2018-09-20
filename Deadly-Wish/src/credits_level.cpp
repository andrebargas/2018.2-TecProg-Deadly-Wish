/** \file credits_level.cpp
  * \brief Esta é o arquivo da classe do level DeathMatchLevel que mostra os creditos do jogo
  * com o nome de seus criadores e etc.
  */
#include "credits_level.h"
#include "engine.h"
#include "util.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>
#include <iostream>

// Distancia entre as linhas dos creditos
#define LINE_BREAK 25

using namespace std;
using namespace ijengine;
using namespace util;

/** \fn CreditsLevel(const string& next = "")
  * \public
  * \brief Método construtor
  * \param next const string& Parametro para o proximo level. Valor constante igual " ",
  * final do jogo.
  */
CreditsLevel::CreditsLevel(const string& next_level)
    : credits_level_done(false), credits_level_next(next_level), credits_level_start(-1)
{
    //UC
    printf("Construtor dos créditos!\n");

    //para a musica que estava tocando e inicia a musica do level
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/credits.ogg", 30, 10);

    // Faz o set dos texto que ira apecer nos creditos
    set_credits_strings();
    event::register_listener(this);
}

/** \fn ~CreditsLevel()
  * \public
  * \brief Método destrutor
  */
CreditsLevel::~CreditsLevel()
{
    event::unregister_listener(this);
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
CreditsLevel::update_self(unsigned now, unsigned)
{
    if (credits_level_start == -1)
        credits_level_start = now;
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
CreditsLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    /** \var auto font
      *  \brief variavel para a fonte do texto nos creditos
      */
    auto font = resources::get_font("Forelle.ttf", 20);

    //Set a fonte de texto dos creditos
    canvas->set_font(font);
    canvas->clear();

    //Printa "Creditos na posição 0, 0"
    canvas->draw("Créditos: ", 0, 0);

    //Seta a posição no eixo y do primeiro credito a aparecer
    int credits_y_position = LINE_BREAK;

    //faz uma iteração em nos creditos para ter uma diferença de 25px na quebra de linha
    for(string credit : credits_level_strings) {
        canvas->draw(credit, 10, credits_y_position);
        //faz a quebra de linha entre os creditos
        credits_y_pos += LINE_BREAK;
    }

    //Desenha a instrução de saida dos créditos
    canvas->draw("Aperte 'X' para voltar ao menu", 10, 200);

}

/** \fn set_credits_strings()
  * \protected
  * \brief seta a qual sera o texto que ira aparecer nos creditos
  * \return void
  */
void
CreditsLevel::set_credits_strings()
{
    //adiciona a credits_level_strings um a um, os creditos
    credits_level_strings.push_back("Arte: Vitor Dias & Fred");
    credits_level_strings.push_back("Programação: Iago Rodrigues & Lucas Mattioli");
    credits_level_strings.push_back("Música: Thiago Hardman & Gabriela Marla");
    credits_level_strings.push_back("");
    credits_level_strings.push_back("Agradecimentos especiais aos professores e monitores");
    credits_level_strings.push_back("que nos auxiliaram durante a construção do jogo! ");
}

/** \fn on_event(const GameEvent& event)
  * \protected
  * \brief Encerra o level quando a o jogador precisiona o botão equivalente
  *  ao do light attack (x no joystick)
  * \param const event GameEvent& Entrada do usuário
  * \return bool retorna true quando ocorre o evento
  */
bool
CreditsLevel::on_event(const GameEvent& event)
{
     if(event.id() == game_event::LIGHT_ATTACK_P1) {
        credits_level_done = true;
        return true;
     }
}

// PBS
/** \fn done()
  * \public
  * \brief Retorna verdadeiro quando o level chega ao final. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return bool retorna 'true' se o level acabou
  */
bool
CreditsLevel::done() const
{
    return credits_level_done;
}

//PBS
/** \fn next()
  * \public
  * \brief Retorna qual sera o proximo level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string retorna qual sera o proximo level
  */
string
CreditsLevel::next() const
{
    return credits_level_next;
}

//PBS
/** \fn audio()
  * \public
  * \brief Retorna qual é o audio do level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string string constante "."
  */
string
CreditsLevel::audio() const {
    return ".";
}
