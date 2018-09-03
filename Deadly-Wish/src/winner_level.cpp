#include "winner_level.h"
#include "engine.h"
#include "util.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace ijengine;
using namespace util;

WinnerLevel::WinnerLevel(const string& next_level, int winner_player)
    : m_done(false), m_next(next_level), m_start(-1), m_winner_player(winner_player) {
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/menu.ogg", 30, 3);
    set_congratulations_string();
}

WinnerLevel::~WinnerLevel() {

}

void WinnerLevel::update_self(unsigned now, unsigned) {
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 3000)
        m_done = true;
}

void WinnerLevel::draw_self(Canvas *canvas, unsigned, unsigned) {
    auto font = resources::get_font("Forelle.ttf", 45);
    canvas->set_font(font);

    canvas->clear();
    canvas->draw(m_congratulations, 60, 85);
}

void WinnerLevel::set_congratulations_string() {
    switch(m_winner_player) {
        case PLAYER_1:
            m_congratulations = "Jogador 1 venceu!";
        break;

        case PLAYER_2:
            m_congratulations = "Jogador 2 venceu!";
        break;

        case PLAYER_3:
            m_congratulations = "Jogador 3 venceu!";
        break;

        case PLAYER_4:
            m_congratulations = "Jogador 4 venceu!";
        break;

        default:
            printf("Error on set_congratulations_string!\n");
            printf("Valor de winner player: %d\n", m_winner_player);
            m_congratulations = "Houve um erro\n no jogo! :D";
        break;
    }
}

bool WinnerLevel::done() const {
    return m_done;
}

string WinnerLevel::next() const {
    return m_next;
}
string WinnerLevel::audio() const {
    return ".";
}