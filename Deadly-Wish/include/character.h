#ifndef CHARACTER_H
#define CHARACTER_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/collidable.h>
#include <ijengine/rectangle.h>
#include <ijengine/event.h>

#include "character_state.h"
#include "character_state_factory.h"
#include "util.h"
#include "base.h"

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::vector;
using std::pair;
using std::string;
using std::unordered_map;
using namespace ijengine;
using namespace util;

//! Classe que descreve o personagem de forma geral
/*! Permite que o personagem tenha poderes de defesa e ataque,
personagem ativo ou não e suas posições nos eixos x e y
\param sprite paths indica o vetor que desena o personagem
\param id indica o identificado do personagem
\param x indica a posição x do personagem
\param y indica a posição y do personagem
\param max_life indica a vida maxima do personagem
\param character_Code indica o codigo do personagem
*/
class Character : public GameObject, public GameEventsListener, public Collidable {
public:
	Character(const vector<string> sprite_paths, unsigned id, double x, double y, int max_life, int character_code);
	~Character();

//! Enumerado com os possiveis personagens
    enum 
    {
        //! variavel Enum que representa o cavaleiro
        KNIGHT, 
        //! variável Enum que representa o soldado
        SOLDIER,
        //! variável Enum que representa o mago
        MAGE,
        //! variável Enum que representa o infiltrador
        INFILTRATOR
    };

//! Enumerado com os possiveis eventos
    enum 
    {
        //! variável que indica inicio de movimento para baixo
        START_MOVING_DOWN,
        //! variável que indica inicio de movimento para esquerda
        START_MOVING_LEFT,
        //! variável que indica inicio de movimento para direita
        START_MOVING_RIGHT,
        //! variável que indica inicio de movimento para cima
        START_MOVING_UP,
        //! variável que indica fim de movimento para baixo
        STOP_MOVING_DOWN,
        //! variável que indica fim de movimento para esquerda
        STOP_MOVING_LEFT,
        //! variável que indica fim de movimento para direita
        STOP_MOVING_RIGHT,
        //! variável que indica fim de movimento para cima
        STOP_MOVING_UP,
        //! variável que indica light_atack
        LIGHT_ATTACK,
        //! variável que indica heavy_atack
        HEAVY_ATTACK,
        //! variável que indica defesa
        DEFENSE,
        //! variável que indica ataque especial
        SPECIAL,
        //! variável que indica número de eventos dos personagens
        NUMBER_OF_CHARACTER_EVENTS
    };


    //! Métodos virtuais de colisão
    virtual bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
		void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
		pair<double, double> direction() const;


    //! Método que retorna o identificador do personagem
    unsigned get_id() const { 
        return character_id; 
    }


    //! Método que retorna o número de vidas do personagem
    int get_number_of_lives() const { 
        return character_number_of_lives; 
    }

    //! Método que coloca as bases com os seus devidos personagens
    void set_base(Base *base);


//!Métodos protegidos
protected:

    //! Método que muda o estado do personagem
    /*
    \param next_state é um objeto que indica o próximo estado do personagem
    \param bool respawing é uma variável que indica o reaparecimento do personagem
    */
    void change_character_state(State next_state, bool respawning = false);
    //! Método que trata o estado
    void handle_state();
    //! Método que define onde o personagem irá ser "desovado"
    void set_spawn_position();
    //! Método que permite o reaparecimento do personagem
    void respawn_character();
    //! Método que define se o personagem foi morto
    void kill_character();
    //! Pacote que desenha o personagem
    /* 
    \param player_id mostrar o identificador de cada personagem
    */
    string choose_sprite_path(unsigned player_id);
    //! Método que retorna os eventos em geral 
    bool on_event(const GameEvent& event);
    //! Método virtual do ataque especial
    virtual void do_heavy_attack() = 0;
    //! Método virtual do ataque ligth_atack
    virtual void do_light_attack() = 0;
    //! Método virtual da defesa
    virtual void do_defense() = 0;
    //! Método virtual do ataque especial
    virtual void do_special() = 0;

    //! Enuemrado que define o tipo de movimento
    typedef enum 
    {
        MOVING_RIGHT, //! Movimento para direita
        MOVING_LEFT //! Movimento para esquerda
    } MovingState;

		//! Métodos virtual de gameobject
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);


protected:
    //! Estado do movimento do personagem
    MovingState character_moving_state;
    //! Estado do personagem
    CharacterState* character_state;
    //! Construindo o personagem
    CharacterStateFactory new_character_state_factory;
    //! variável que indica se o personagem esta ativo
    bool character_active;
    //! variável que serve para identificador do personagem
    unsigned character_id;
    //! variável que indica vida maxima de cada personagem
    int character_max_life;
    //! variável que indica a vida atual de cada personagem
    int character_current_life;
    //! variável que indica o número de vidas
    int character_number_of_lives;
    //! variável que indica frame do personagem
    int character_frame;
    //! variável que indica que o Personagem foi iniciado
    int character_start;
    //! variável que indica a largura do personagem
    int character_width;
    //! variável que indica a altura do personagem
    int character_height;
    //! variável que indica o ataque pesado do personagem
    int character_heavy_attack_cooldown;
    //! variável que indica ataque leve do personagem
    int character_light_attack_cooldown;
    //! variável que indica defesa do personagem
    int character_defense_cooldown;
    //! variável que indica ataque especial do personangem
    int character_special_cooldown;
    //! variável que indica o ultimo uso dos ataques e defesas
    int character_last_used_heavy_attack;
    int character_last_used_light_attack;
    int character_last_used_defense;
    int character_last_used_special;
    //! variável que indica o tempo de reaparecimento
    int character_respawn_time;
    //! variável que indica codigo do personagem
    int character_code;
    //! variável que indica o último som que foi tocado
    int character_last_sound_played;
    //! variável que indica o congelamento do personagem
    bool character_freeze;
    //! personagem vivo ou morto
    bool character_dead;
    //! velocidade no eixo x
    double character_axis_x_speed;
    //! velocidade no eixo y
    double character_axis_y_speed;
    //! variável que indica a velocidade do personagem
    double character_speed;
    //! variável que indica base do personagem
    Base* character_base;
    vector< shared_ptr<Texture> > character_textures;
    unordered_map<string, pair<double, double> > character_speed_vector;
    Rectangle character_bounding_box;
    vector<string> character_sprite_paths;

// Método que indica que vai atualizar poisção do personagem
/* 
\param now indica o tempo atual
\param last indica o último evento
\param backwards indica a posição anterior
*/    

    inline void update_position(const unsigned &now, const unsigned &last, bool backwards = false);
};

#endif
