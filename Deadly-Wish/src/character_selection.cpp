#include "character_selection.h"
#include "ije02_game.h"

#include <ijengine/engine.h>
#include <ijengine/canvas.h>
#include <ijengine/rectangle.h>

#include <cmath>

using namespace std;

//! Inicializando o método construtor
/*! 
\param sprite_path guarda o caminho do sprite do personagem
\param base_x guarda a posição da base no eixo x
\param base_y guarda a posição da base no eixo y
\param player_id guarda o id do jogador
*/
CharacterSelection::CharacterSelection(const string sprite_path, int base_x, int base_y, int player_id)
    : m_base_x(base_x), m_base_y(base_y), m_player_id(player_id), m_frame(player_id), m_start(-1), m_current_selection(KNIGHT)
{
    m_texture = resources::get_texture(sprite_path);
    m_w = 8;
    m_h = 9;

    m_chosen = false;

    event::register_listener(this);
    update_position();
}

//! Método destrutor
CharacterSelection::~CharacterSelection() {
    event::unregister_listener(this);
}

//! Método que atualiza a tela
void
CharacterSelection::update_self(unsigned now, unsigned last)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 100)
    {
        m_start += 100;
    }
}

//! A diferença entre bases no eixo x
const int DIFF_X = 43;

//! A diferença entre bases no eixo y
const int DIFF_Y = 42;

// BASE X = 135
// BASE Y = 73

//! Método que seta a posição do personagem
void
CharacterSelection::update_position()
{
    switch(m_current_selection) {
        case KNIGHT:
            set_x(m_base_x);
            set_y(m_base_y);
            break;

        case SOLDIER:
            set_x(m_base_x + DIFF_X);
            set_y(m_base_y);
            break;

        case MAGE:
            set_x(m_base_x);
            set_y(m_base_y + DIFF_Y);
            break;

        case INFILTRATOR:
            set_x(m_base_x + DIFF_X);
            set_y(m_base_y + DIFF_Y);
            break;

        default:
            printf("Argumento inválido no update_position() do character_selection.cpp\n");
            break;
    }
}

//! Método virtual de gameobject
void
CharacterSelection::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {0.0, (m_texture->h() / (double) 4) * m_frame, (double) m_w, (double) m_h};
    canvas->draw(m_texture.get(), rect, x(), y());
}

//! Esse método processa todas as entradas do jogador pelo controle
bool
CharacterSelection::on_event(const GameEvent &event)
{
    //! Movimenta pelos personagens disponíveis usando os botões direcionais
    if(((event.id() == game_event::MOVEMENT_P1 && m_player_id == 0) ||
       (event.id() == game_event::MOVEMENT_P2 && m_player_id == 1) ||
       (event.id() == game_event::MOVEMENT_P3 && m_player_id == 2) ||
       (event.id() == game_event::MOVEMENT_P4 && m_player_id == 3)) and 
       (m_chosen == false)) {
        string axis = event.get_property<string>("axis");
        int value = event.get_property<int>("value");

        if(axis == "X") {
            if(value > 0) {
                m_current_selection = (m_current_selection + 1) % 4;
            }
            else if(value < 0) {
                m_current_selection = (m_current_selection - 1) % 4;
            }
        }
        else if(axis == "Y") {
            if(value > 0) {
                m_current_selection = (m_current_selection - 2) % 4;
            }
            else if(value < 0) {
                m_current_selection = (m_current_selection + 2) % 4;
            }
        }
        
        if(m_current_selection < 0) {
            m_current_selection += 4;
        }
        update_position();
        return true;
    }
    //! Escolhe o personagem com o botão 'LIGHT_ATTACK'
    else if((event.id() == game_event::LIGHT_ATTACK_P1 && m_player_id == 0) ||
            (event.id() == game_event::LIGHT_ATTACK_P2 && m_player_id == 1) ||
            (event.id() == game_event::LIGHT_ATTACK_P3 && m_player_id == 2) ||
            (event.id() == game_event::LIGHT_ATTACK_P4 && m_player_id == 3)) {
        m_chosen = true;
    }
    //! Anula a escolha do personagem com o botão 'DEFENSE'
    else if((event.id() == game_event::DEFENSE_P1 && m_player_id == 0) ||
            (event.id() == game_event::DEFENSE_P2 && m_player_id == 1) ||
            (event.id() == game_event::DEFENSE_P3 && m_player_id == 2) ||
            (event.id() == game_event::DEFENSE_P4 && m_player_id == 3)) {
        m_chosen = false;
   }
    return false;
}