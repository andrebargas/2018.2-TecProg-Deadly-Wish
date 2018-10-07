/** \file spear.h
  * \brief Este é o arquivo header da classe Spear que exibe a spear(lança) do soldier, com herança da classe Skill
  */
#ifndef SPEAR_H
#define SPEAR_H

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
#include <assert.h>

using std::shared_ptr;
using std::vector;

using namespace std;
using namespace ijengine;

/** \class Spear spear.h "include/spear.h"
 *  \brief Classe que herda de GameObject e Collidable
 *  que calcula o dano recebido pelos personagens.
 * \breif Método Construtor Spear
 * \param *parent Ponteiro para o GameObject
 * \param soldier_id identificador do personagem soldier
 * \param xp double posição no eixo X
 * \param yp double posição no eixo y
 */
class Spear : public Skill
{
  public:
    /** \fn Spear(GameObject *parent, unsigned soldier_id, double xp, double yp,
          double dx, double dy);
     * \public
     * \brief Método construtor
     */
    Spear(GameObject *parent, unsigned soldier_id, double xp, double yp,
          double dx, double dy);

    /** \fn ~Spear()
      * \public
      * \brief Método destrutor
      */
    ~Spear();

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
      *  Metodos virtual de GameObject
      * \param now unsigned Tempo atual do jogo
      * \param last unsigned
      * \return void
      */
    void update_self(unsigned now, unsigned last);

    /** \fn draw_self(Canvas *canvas, unsigned now, unsigned last)
      * \protected
      * \brief Método que faz o desenho grafico do jogo. Nome não pode ser mudado por ser um
      *  metodo herdado da classe pai, protegida pelo escopo do projeto
      *  Metodos virtual de GameObject
      * \param canvas Canvas* Ponteiro para objeto da classe responsavel pela renderização do jogo.
      * \param now unsigned Tempo atual do jogo
      * \param last unsigned
      * \return void
      */
    void draw_self(Canvas *canvas, unsigned, unsigned);

    void update_sprite_state();
    void update_time(unsigned now);
    string choose_sprite_path(unsigned player_id);

    //! enum para escolher a direção do Spear
    typedef enum
    {
        MOVING_LEFT,
        MOVING_RIGHT
    } State;

    //! struct com enum para SpriteState do Spear
    typedef enum
    {
        THROW,
        MOVING,
        FALLING,
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

    //! Variável que intica o spear_id_character
    unsigned spear_character_id;
    //! Variável que indica o state do spear
    State spear_state;
    //! Variável que indica o SpriteState usada na engine
    SpriteState spear_sprite_state;
    //! Variável que indica a direção em x e y do spear
    double spear_axis_x_direction;
    //! Variável que indica a direção em x e y do spear
    double spear_axis_y_direction;
    //! Variável que indica o dano do spear
    int spear_damage;
    //! Variável que indica velocidade da spear
    double spear_speed;
    //! Variável que indica o frame da spear
    int spear_frame;
    //! Variável que indica o sprite_path
    string spear_sprite_path;
    //! Variável que indica o inicio da spear(lança)
    unsigned spear_start;
    //! Variável que indica o tempo da spear
    unsigned spear_current_time;
    shared_ptr<Texture> spear_texture;
    Rectangle spear_bounding_box;

    //    bool on_event(const GameEvent& event);
};

#endif
