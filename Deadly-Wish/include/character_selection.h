#ifndef CHARACTER_SELECTION_H
#define CHARACTER_SELECTION_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/rectangle.h>
#include <ijengine/event.h>

#include <memory>
#include <string>
#include "assert.h"
using std::shared_ptr;
using std::string;
using namespace ijengine;


//! Classe que indica qual vai ser o personagem escolhido
class CharacterSelection : public GameObject, GameEventsListener {


//! Método construtor que permite a escolha do personagem
/*
\param sprint_path constroi o personagem
\param base_x indica a posição da base no eixo x
\param base_y indica a posição da base no eixo y
\param player_id indica o identificador do jogador
*/
public:
    CharacterSelection(const string sprite_path, int base_x, int base_y, int player_id);
    ~CharacterSelection();

    //! Define enumerado dos tipos de personagem
    enum 
    {
        //! Escolha do cavaleiro
        KNIGHT,
        //! Escolha do soldado
        SOLDIER,
        //! Escolha do mago
        MAGE,
        //! Escolha do infiltrador
        INFILTRATOR
    };

    //! variável que indica o jogador que vai escolher
    int current_selection() const { return m_current_selection;
        assert(m_current_selection != NULL);
    }
    //! variável que indica o identificador do player
    int player_id() const { return m_player_id;
        assert(m_player_id != NULL);
    }
    //! variável que retorna se ja escolheu ou não um jogador
    bool chosen() const {return m_chosen;
        assert(m_chosen != NULL);
    }


//! Métodos protegidos 
protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    bool on_event(const GameEvent& event);
    void update_position(); 

private:
    //! variável inteira que define o identificador do personagem
    int m_player_id;
    //! variável inteira que define o frame
    int m_frame;
    //! variável inteira que indica que vai começar a partida
    int m_start;
    //! variável inteira que indica a escolha do jogador
    int m_current_selection;
    //! variável que indica a largura do...
    int m_width;
    //! variável que indica a largura do...
    int m_height;
    //!variável que indica a posição da base no eixo x
    int m_base_x;
    //! variável que indica a posição da base no eixo y
    int m_base_y;
    //! variável que indica a escolha se ja ocorreu o u não
    bool m_chosen;
    shared_ptr<Texture> m_texture;
};

#endif