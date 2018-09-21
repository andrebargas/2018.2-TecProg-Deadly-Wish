/** \file light_attack.h
  * \brief Este é o arquivo header da classe Light_Attack, com herança da classe Skill
  */
#ifndef LIGHT_ATTACK_H
#define LIGHT_ATTACK_H

#include "skill.h"

#include <cmath>

//! Inclui os arquivos da engine do jogo
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

/** \class LightAttack light_attack.h "include/light_attack.h"
 *  \brief Classe que controla o LightAttack indica direção, velocidade, player, 
 * com herança da classe Skill
 *  \param *parent Ponteiro para o GameObject
 *  \param mage_id
 *  \param xp posição em x 
 *  \param yp posição em y
 */
class LightAttack : public Skill
{
  public:
    /** \fn LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp);
      * \public
      * \brief Método construtor
      */
    LightAttack(GameObject *parent, unsigned mage_id, double xp, double yp);

    /** \fn ~LightAttack()
      * \public
      * \brief Método destrutor
      */
    ~LightAttack();

    //! Métodos virtuais de colisão
    bool active() const;
    const Rectangle &bounding_box() const;
    const list<Rectangle> &hit_boxes() const;
    pair<double, double> direction() const;

  protected:
    /** \fn update_self(unsigned now, unsigned last)
      * \protected
      * \brief Função para atualizar o tempo de inicio do level, e setar atributo
      *  #winner_level_start. Nome não pode ser mudado por ser um metodo herdado da classe pai,
      *  protegida pelo escopo do projeto
      * \param now unsigned Tempo atual do jogo
      * \param last unsigned
      * \return void
      */
    void update_self(unsigned now, unsigned last);

    /** \fn draw_self(Canvas *canvas, unsigned now, unsigned last)
      * \protected
      * \brief Método que faz o desenho grafico do jogo. Nome não pode ser mudado por ser um
      *  metodo herdado da classe pai, protegida pelo escopo do projeto
      * \param canvas Canvas* Ponteiro para objeto da classe responsavel pela renderização do jogo.
      * \param now unsigned Tempo atual do jogo
      * \param last unsigned
      * \return void
      */
    void draw_self(Canvas *canvas, unsigned, unsigned);

    void update_sprite_state();
    void update_time(unsigned now);
    string choose_sprite_path(unsigned player_id);

    unsigned light_attack_character_id;

    //! enum para lado do LightAttack
    typedef enum
    {
        MOVING_LEFT,
        MOVING_RIGHT
    } State;

    //! struct com enum para SpriteState do LightAttack
    typedef enum
    {
        CASTING,
        MOVING,
        HITTING
    } SpriteState;

    //! struct com enum para Players
    typedef enum
    {
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4
    } Players;

    //! Variável que indica o state usada na engine
    State m_state;
    //! Variável que indica o SpriteState usada na engine
    SpriteState m_sprite_state;
    //! Variáveis que indicam a direção em x e y do light_attack
    double light_attack_axis_x_direction, light_attack_axis_y_direction;
    //! Variável que indica o dano do light_attack
    int light_attack_damage;
    //! Variável que indica a velocidade do light_attack
    double light_attack_speed;
    //! Variável que indica frame do light_attack
    int light_attack_frame;
    //! Variável que indica frame do light_attack
    string light_attack_sprite_path;
    //! Variável que indica o inicio do light_attack
    unsigned light_attack_start;
    //! Variável que indica o tempo do light_attack
    unsigned light_attack_current_time;

    shared_ptr<Texture> light_attack_texture;

    Rectangle light_attack_bounding_box;

    //    bool on_event(const GameEvent& event);
};

#endif
