/** \file fireball.h
  * \brief Este é o arquivo header da classe Fireball, uma
	* habilidade do Character Mage, com herança da classe Skill
  */
#ifndef FIREBALL_H
#define FIREBALL_H

#include "skill.h"

#include <cmath>
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/color.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

using namespace std;
using namespace ijengine;


/** \class Fireball fireball.h "include/fireball.h"
  * \brief Cria o GameObject Fireball, controla sua posição e colisão, atualiza o sprite e o tempo
  */
class Fireball : public Skill {
public:
		/** \fn Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx, double dy)
			* \public
			* \brief Método construtor
			* \param *parent Ponteiro para o GameObject
			* \param mage_id
			* \param xp posição em x
			* \param yp posição em y
			* \param dx
			* \param dy
			*/
		Fireball(GameObject *parent, unsigned mage_id, double xp, double yp,
        double dx, double dy);
		/** \fn ~Fireball
      * \public
      * \brief Método destrutor
      */
		~Fireball();

		/** \fn active()
		  * \public
		  * \brief Estado do objeto usado pela Engine
		  * \return bool fixo em true
		  */
    bool active() const;

		/** \fn bounding_box()
		  * \public
		  * \brief Função que retorna a caixa delimitadora do objeto criada pela Engine
		  * \return Rectangle& para habilidade Fireball
		  */
    const Rectangle& bounding_box() const;

		/** \fn hit_boxes()
      * \public
      * \brief Função que retorna uma lista com a caixa delimitadora do objeto criada pela Engine
      * \return list<Rectangle>& para habilidade Fireball
      */
    const list<Rectangle>& hit_boxes() const;

		/** \fn direction()
		  * \public
		  * \brief Função que retorna uma dupla com a direção no eixo x e no y do objeto
		  * \return pair<double, double> direção da habilidade Fireball
		  */
    pair<double, double> direction() const;

protected:
		/** \fn update_self(unsigned now, unsigned last)
			* \protected
			* \brief Função para atualizar o tempo. Nome não pode ser mudado por ser um
			* metodo herdado da classe pai, protegida pelo escopo do projeto
			* \param now unsigned Tempo atual do jogo
			* \param last unsigned
			* \return void
			*/
    void update_self(unsigned now, unsigned last);

		/** \fn draw_self(Canvas *canvas, unsigned now, unsigned last)
      * \protected
      * \brief Método que faz o desenho gráfico do jogo. Nome não pode ser mudado por ser um
      *  metodo herdado da classe pai, protegida pelo escopo do projeto
      * \param canvas Canvas* Ponteiro para objeto da classe responsavel pela renderização do jogo.
      * \param unsigned
      * \param unsigned
      * \return void
      */
    void draw_self(Canvas *canvas, unsigned, unsigned);

		/** \fn update_sprite_state()
		  * \protected
		  * \brief Função que atualiza o estado do sprite considerando os tempos, a largura e a textura da Fireball
		  * \return void
		  */
    void update_sprite_state();

		/** \fn update_time(unsigned now)
		  * \protected
		  * \brief Método que atualiza os tempos da Fireball e o estado do seu sprite
		  * \param now Tempo do jogo
		  * \return void
		  */
    void update_time(unsigned now);

		/** \fn choose_sprite_path(unsigned player_id)
		  * \protected
		  * \brief Método que retorna o caminho do sprite de acordo com o id do jogador
		  * \param player_id Identificador do jogador
		  * \return void
		  */
    string choose_sprite_path(unsigned player_id);

    unsigned fireball_character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    typedef enum { CASTING, MOVING, HITTING } SpriteState;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    State fireball_state;
    SpriteState fireball_sprite_state;
    double fireball_axis_x_direction, fireball_axis_y_direction;
    int fireball_damage;
    double fireball_speed;
    int fireball_frame;
    string fireball_sprite_path;
    unsigned fireball_start;
    unsigned fireball_current_time;
    shared_ptr<Texture> fireball_texture;
    Rectangle fireball_bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif
