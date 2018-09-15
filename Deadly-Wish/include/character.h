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

// Classe que descreve o personagem de forma geral
class Character : public GameObject, public GameEventsListener, public Collidable {
public:
	Character(const vector<string> sprite_paths, unsigned id, double x, double y, int max_life, int character_code);
	~Character();

// enumerado com os possiveis personagens
    enum 
    {
        KNIGHT,
        SOLDIER,
        MAGE,
        INFILTRATOR
    };

// enumerado com os possiveis eventos
    enum {
        START_MOVING_DOWN,
        START_MOVING_LEFT,
        START_MOVING_RIGHT,
        START_MOVING_UP,
        STOP_MOVING_DOWN,
        STOP_MOVING_LEFT,
        STOP_MOVING_RIGHT,
        STOP_MOVING_UP,
        LIGHT_ATTACK,
        HEAVY_ATTACK,
        DEFENSE,
        SPECIAL,
        NUMBER_OF_CHARACTER_EVENTS
    };


    //metodos de collidable
    virtual bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
		void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
		pair<double, double> direction() const;

    // método que pega o identificador do personagem
    unsigned get_id() const { 
        return character_id; 
    }

    // método que pega a quantidade de vida do personagem
    int get_number_of_lives() const { 
        return character_number_of_lives; 
    }

    // método que coloca as bases com os seus devidos personagens
    void set_base(Base *base);


protected:
    // método que muda o estado do personagem 
    void change_character_state(State next_state, bool respawning = false);
    // método que trata o estado
    void handle_state();
    // método que define onde o personagem irá ser "desovado"
    void set_spawn_position();
    // método que permite o reaparecimento do personagem
    void respawn_character();
    // método que define se o personagem foi morto
    void kill_character();
    // pacote que desenha o personagem
    string choose_sprite_path(unsigned player_id);
    // evento em geral 
    bool on_event(const GameEvent& event);
    virtual void do_heavy_attack() = 0;
    virtual void do_light_attack() = 0;
    virtual void do_defense() = 0;
    virtual void do_special() = 0;

    //enuemrado que define o tipo de movimento(Estado)
    typedef enum {
        MOVING_RIGHT, MOVING_LEFT
    } MovingState;

		//metodos virtual de gameobject
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);


protected:
    // estado do movimento do personagem
    MovingState character_moving_state;
    // estado do personagem
    CharacterState* character_state;
    // construindo o personagem
    CharacterStateFactory new_character_state_factory;
    // personagem ativo
    bool character_active;
    // identificador do personagem
    unsigned character_id;
    // vida maxima de cada personagem
    int character_max_life;
    // vida atual de cada personagem
    int character_current_life;
    // numero de vidas
    int character_number_of_lives;
    // frame do personagem
    int character_frame;
    // personagem iniciado
    int character_start;
    // largura do personagem
    int character_width;
    // largura do personagem
    int character_height;
    // ataque pesado do personagem
    int character_heavy_attack_cooldown;
    // ataque leve do personagem
    int character_light_attack_cooldown;
    // defesa do personagem
    int character_defense_cooldown;
    // ataque especial do personangem
    int character_special_cooldown;
    // ultimo uso dos ataques e defesas
    int character_last_used_heavy_attack;
    int character_last_used_light_attack;
    int character_last_used_defense;
    int character_last_used_special;
    // tempo de reaparecimento
    int character_respawn_time;
    // codigo do personagem
    int character_code;
    // ultimo som que foi tocado
    int character_last_sound_played;

    bool character_freeze;
    // personagem vivo ou morto
    bool character_dead;
    // velocidade no eixo x
    double character_axis_x_speed;
    // velocidade no eixo y
    double character_axis_y_speed;
    // velocidade do personagem
    double character_speed;
    //base do personagem
    Base* character_base;
    vector< shared_ptr<Texture> > character_textures;
    unordered_map<string, pair<double, double> > character_speed_vector;
    Rectangle character_bounding_box;
    vector<string> character_sprite_paths;

// atualizar poisção do personagem
    inline void update_position(const unsigned &now, const unsigned &last, bool backwards = false);
};

#endif
