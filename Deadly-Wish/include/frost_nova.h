/** \file frost_nova.h
  * \brief Este é o arquivo header da classe FrostNova, uma
  * habilidade do Character Mage, com herança da classe Skill
  */
#ifndef FROST_NOVA_H
#define FROST_NOVA_H

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

/** \class FrostNova frost_nova.h "include/frost_nova.h"
  * \brief Cria o GameObject FrostNova, controla sua posição e colisão, atualiza o sprite e o tempo
  */
class FrostNova : public Skill {
public:
    /** \fn FrostNova(GameObject *parent, unsigned mage_id, double xp, double yp, double dx, double dy)
      * \public
      * \brief Método construtor
      * \param *parent Ponteiro para o GameObject
      * \param mage_id
      * \param xp posição em x
      * \param yp posição em y
      * \param dx
      * \param dy
      */
    FrostNova(GameObject *parent, unsigned mage_id, double xp, double yp,
        double dx, double dy);
    /** \fn ~FrostNova
      * \public
      * \brief Método destrutor
      */
    ~FrostNova();

    /** \fn active()
		  * \public
		  * \brief Estado do objeto usado pela Engine
		  * \return bool fixo em true
		  */
    bool active() const;

    /** \fn bounding_box()
		  * \public
		  * \brief Função que retorna a caixa delimitadora do objeto criada pela Engine
		  * \return Rectangle& para habilidade FrostNova
		  */
    const Rectangle& bounding_box() const;

    /** \fn hit_boxes()
      * \public
      * \brief Função que retorna uma lista com a caixa delimitadora do objeto criada pela Engine
      * \return list<Rectangle>& para habilidade FrostNova
      */
    const list<Rectangle>& hit_boxes() const;

    /** \fn direction()
      * \publicon_collision
      * \brief Função que retorna uma dupla com a direção no eixo x e no y do objeto
      * \return pair<double, double> direção da habilidade FrostNova
      */
    pair<double, double> direction() const;

    /** \fn on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last)
      * \public
      * \brief Método construtor
      * \param *parent Ponteiro para o GameObject
      * \param mage_id
      * \param xp posição em x
      * \param yp posição em y
      * \param dx
      * \param dy
      * \return void
      */
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);

protected:

    // PBS
    /** \fn update_self(unsigned now, unsigned last)
      * \protected
      * \brief Função para atualizar o tempo. Nome não pode ser mudado por ser um
      * metodo herdado da classe pai, protegida pelo escopo do projeto
      * \param now unsigned Tempo atual do jogo
      * \param last unsigned
      * \return void
      */
    void update_self(unsigned now, unsigned last);

    // PBS
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

    //UC
    /** \fn update_sprite_state()
      * \protected
      * \brief Função não implementada
      * \return void
      */
    void update_sprite_state();

    /** \fn update_time(unsigned now)
      * \protected
      * \brief Método que atualiza os tempos da FrostNova e seu frame considerando sua textura e largura
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

    /** \var unsigned frost_character_id
      *  \brief Variável que indica o frost_character_id
      */
    unsigned frost_character_id;
    /** \enum State
      * \brief Enum com o estado de movimentação para a esquerda e para a direita
      */
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    /** \enum SpriteState
      * \brief Enum com o estado da sprite
      */
    typedef enum { CASTING, MOVING, HITTING } SpriteState;
    /** \enum Players
      * \brief Enum com os 4 jogadores
      */
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;
    /** \var State frost_state
      * \brief Variável que indica o estado do FrostNova
      */
    State frost_state;
    /** \var SpriteState frost_sprite_state
      * \brief Variável que indica o estado do sprite do FrostNova
      */
    SpriteState frost_sprite_state;
    /** \var double frost_axis_x_direction
      * \brief Variável que indica a direção no eixo x
      */
    /** \var double frost_axis_y_direction
      * \brief Variável que indica a direção no eixo y
      */
    double frost_axis_x_direction, frost_axis_y_direction;
    /** \var int frost_damage
      * \brief Variável que indica o dano do FrostNova
      */
    int frost_damage;
    /** \var double frost_speed
      * \brief Variável que indica a velocidade do FrostNova
      */
    double frost_speed;
    /** \var int frost_frame
      * \brief Variável que indica o frame do FrostNova
      */
    int frost_frame;
    /** \var string frost_sprite_path
      * \brief Variável que indica o caminho da pasta da sprite do FrostNova
      */
    string frost_sprite_path;
    /** \var unsigned frost_start
      * \brief Variável que indica o tempo inicial do FrostNova
      */
    unsigned frost_start;
    /** \var unsigned frost_current_time
      * \brief Variável que indica o tempo atual do FrostNova
      */
    unsigned frost_current_time;
    /** \var shared_ptr<Texture> frost_texture
      * \brief Variável que indica a textura do FrostNova
      */
    shared_ptr<Texture> frost_texture;
    /** \var Rectangle frost_bounding_box
      * \brief Variável que indica a caixa delimitadora do FrostNova
      */
    Rectangle frost_bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif
