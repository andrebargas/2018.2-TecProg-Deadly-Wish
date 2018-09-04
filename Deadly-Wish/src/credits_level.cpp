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

CreditsLevel::CreditsLevel(const string& next)
    : exit(false), next_level(next_level), start(-1)
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
CreditsLevel::update_self(unsigned now_moment, unsigned)
{
    if (start == -1)
        start = now_moment;
}

void
CreditsLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    auto font = resources::get_font("Forelle.ttf", 20);
    canvas->set_font(font);
    canvas->clear();
    canvas->draw("Créditos: ", 0, 0);
    int y_position = 25;

    for(string credit : credits_text) {
        canvas->draw(credit, 10, y_position);
        y_position += 25;
    }

    canvas->draw("Aperte 'X' para voltar ao menu", 10, 200);
    
}

void
CreditsLevel::set_credits_text()
{
    credits_text.push_back("Arte: Vitor Dias & Fred");
    credits_text.push_back("Programação: Iago Rodrigues & Lucas Mattioli");
    credits_text.push_back("Música: Thiago Hardman & Gabriela Marla");
    credits_text.push_back("");
    credits_text.push_back("Agradecimentos especiais aos professores e monitores");
    credits_text.push_back("que nos auxiliaram durante a construção do jogo! ");
}

bool
CreditsLevel::on_event(const GameEvent& event) 
{
     if(event.id() == game_event::LIGHT_ATTACK_P1) {
        exit = true;
        return true;
     }
}

bool
CreditsLevel::exit_level() const
{
    return exit;
}

string
CreditsLevel::go_to_next_level() const
{
    return next_level;
}
string
CreditsLevel::audio() const {
    return ".";
}