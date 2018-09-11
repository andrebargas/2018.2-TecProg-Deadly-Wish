#include "credits_level.h"
#include "engine.h"
#include "util.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace ijengine;
using namespace util;

CreditsLevel::CreditsLevel(const string& next_level)
    : m_done(false), m_next(next_level), m_start(-1)
{
    printf("Construtor dos créditos!\n");
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/credits.ogg", 30, 10);
    set_credits_strings();
    event::register_listener(this);
}

CreditsLevel::~CreditsLevel()
{
    event::unregister_listener(this);
}

void
CreditsLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;
}

void
CreditsLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    auto font = resources::get_font("Forelle.ttf", 20);
    canvas->set_font(font);
    canvas->clear();
    canvas->draw("Créditos: ", 0, 0);
    int y_pos = 25;

    for(string credit : credits_level_strings) {
        canvas->draw(credit, 10, y_pos);
        y_pos += 25;
    }

    canvas->draw("Aperte 'X' para voltar ao menu", 10, 200);
    
}

void
CreditsLevel::set_credits_strings()
{
    credits_level_strings.push_back("Arte: Vitor Dias & Fred");
    credits_level_strings.push_back("Programação: Iago Rodrigues & Lucas Mattioli");
    credits_level_strings.push_back("Música: Thiago Hardman & Gabriela Marla");
    credits_level_strings.push_back("");
    credits_level_strings.push_back("Agradecimentos especiais aos professores e monitores");
    credits_level_strings.push_back("que nos auxiliaram durante a construção do jogo! ");
}

bool
CreditsLevel::on_event(const GameEvent& event) 
{
     if(event.id() == game_event::LIGHT_ATTACK_P1) {
        credits_level_done = true;
        return true;
     }
}

bool
CreditsLevel::done() const
{
    return credits_level_done;
}

string
CreditsLevel::next() const
{
    return credits_level_done;
}
string
CreditsLevel::audio() const {
    return ".";
}