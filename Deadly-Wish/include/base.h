/** \file base.h
  * \brief Este é o arquivo da classe do Base que é a base 'fortaleza' do player no game.
  */
#ifndef BASE_H
#define BASE_H

//Incluindo arquivo da classe GameObject
#include <ijengine/game_object.h>
//Incluindo arquivo da classe Texture
#include <ijengine/texture.h>
//Incluindo arquivo da classe Collidable
#include <ijengine/collidable.h>
//Incluindo arquivo da classe Rectangle
#include <ijengine/rectangle.h>
//Incluindo arquivo de enum's
#include "util.h"

#include <memory>
#include <vector>
#include <string>
#include <utility>

using std::shared_ptr;
using std::vector;
using std::string;
using std::pair;

using namespace ijengine;
using namespace util;

/** \class Base base.h "include/base.h"
 *  \brief Classe usada para definir a base'fortaleza' de um
 *  player no jogo.
 */
class Base : public GameObject, public Collidable {
public:
     /** \fn DefenseState()
      * \public
      * \brief Método construtor
      * \param player_id int Id do player.Não é inicializado.
      */
    Base(int player_id);
    /** \fn ~Base()
      * \public
      * \brief Método destrutor
      * \param player_id int id de um personagem
      */
    ~Base();

    /** \fn get_base_player_id()
      * \public
      * \brief Método get
      * \return unsigned int retorna a base do player 
      */
    unsigned get_base_player_id() const { return base_player_id; }
    /** \fn get_base_life()
      * \public
      * \brief Método get
      * \return int retorna os pontos de vida da base 
      */
    int get_base_life() const {return base_life;}
    /** \fn set_base_status()
      * \public
      * \brief Método set
      * \param base_status int estados de uma basa no game
      * \return int retorna o status da base 
      */
    void set_base_status(int base_status);

    //metodos virtual de Collidable
    /** \fn active()
      * \public
      * \brief Método virtual de Collidable que retorna True se a base esta ativa
      * \return bool retorna o status da base se ativa = True 
      */
    bool active() const;
    //PBS
    /** \fn bounding_box()
      * \public
      * \brief Método que delimita os limites da base
      * \return const
      */
    const Rectangle& bounding_box() const;
    /** \fn hit_boxs()
      * \public
      * \brief Método que delimita os pontos de contato da base
      * \return const
      */
    const list<Rectangle>& hit_boxes() const;
    /** \fn on_collision()
      * \public
      * \brief Método que age quando hà colisão
      * \return void
      */
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    /** \fn direction()
      * \public
      * \brief Método que retorna velocidade da base em determinada direção
      * \return pair<double,double> retorna a velocidade da base na posiçao x e y
      */
    pair<double, double> direction() const;


protected:
    //PBS
    /** \fn set_base_position()
      * \protected
      * \brief Método set para a posição da base em determinada direção
      * \param player_id x_pos y_pos unsigned double double
      * id do personagem, posição do x no eixo, posição do y no eixo
      * \return void
      */
    void set_base_position(unsigned player_id, double& x_pos, double& y_pos);
    //PBS
    /** \fn change_base_status()
      * \protected
      * \brief Método que muda o status da base
      * \return void
      */
    void change_base_status();
    //PBS
    /** \fn update_self()
      * \protected
      * \brief Método virtual de GameObject
      * \param now last int int
      * ______________________
      * \return void
      */
    void update_self(unsigned now, unsigned last);
    //PBS
    /** \fn draw_self(()
      * \protected
      * \brief ____________________
      * \param *canvas now last Canvas unsigned unsigned
      * _______________________________
      * \return void
      */
    void draw_self(Canvas *canvas, unsigned now, unsigned last);


protected:
    //PBS
    unsigned base_player_id;
    //PBS
    int base_life;
    //PBS
    int base_frame;
    //PBS
    int base_start;
    //PBS
    int base_width;
    //PBS
    int base_height;
    //PBS
    int base_status;
    //PBS
    vector <string> base_sprite_paths;
    //PBS
    shared_ptr<Texture> base_texture;
    //PBS
    Rectangle base_bounding_box;
    //PBS
    double base_axis_x_speed;
    //PBS
    double base_axis_y_speed;

};

#endif
