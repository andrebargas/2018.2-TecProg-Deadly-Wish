/**\file base.h
  *\brief Este é o arquivo da classe do Base que é a base 'fortaleza' do player no game.
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

/**\class Base base.h "include/base.h"
*\brief Classe usada para definir a base'fortaleza' de um
*player no jogo.
*/
class Base : public GameObject, public Collidable {
public:

    /**\fn Base()
    *\public
    *\brief Método construtor
    *\param player_id int Id do player.Não é inicializado.
    */
    Base(int player_id);
    /**\fn ~Base()
    *\public
    *\brief Método destrutor
    *\param player_id int id de um personagem
    */
    ~Base();
    /**\fn get_base_player_id()
    *\public
    *\brief Método get
    *\return unsigned int retorna a base do player
    */
    unsigned get_base_player_id() const { return base_player_id; }
    /**\fn get_base_life()
    *\public
    *\brief Método get
    *\return int retorna os pontos de vida da base
    */
    int get_base_life() const {return base_life;}
    /**\fn set_base_status()
    *\public
    *\brief Método set
    *\param base_status int estados de uma base no game
    *\return void
    */
    void set_base_status(int base_status);

    //metodos virtual de Collidable
    /**\fn active()
    *\public
    *\brief Método virtual de Collidable que retorna True se a base esta ativa
    *\return bool retorna o status da base se ativa = True
    */
    bool active() const;
    
    /**\fn bounding_box()
    *\public
    *\brief Método que delimita os limites da base
    *\return const Rectangle&
    */
    const Rectangle& bounding_box() const;
    /**\fn hit_boxs()
    *\public
    *\brief Método que delimita os pontos de contato da base
    *\return const list<Rectangle>&
    */
    const list<Rectangle>& hit_boxes() const;
    /**\fn on_collision()
    *\public
    *\brief Método que age quando hà colisão
    *\return void
    */
    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    /**\fn direction()
   *\public
   *\brief Método que retorna velocidade da base em determinada direção
   *\return pair<double,double> retorna a velocidade da base na posiçao x e y
   */
    pair<double, double> direction() const;


protected:
    
    /**\fn set_base_position()
    *\protected
    *\brief Método set para a localização da base em determinada posição
    *\param player_id unsigned id do personagem
    *\param x_pos double& posição no eixo x
    *\param y_pos double& posição no eixo y
    *\return void
    */
    void set_base_position(unsigned player_id, double& x_pos, double& y_pos);
    
    /**\fn change_base_status()
    *\protected
    *\brief Método que muda o status da base (numero de esferas no desenho)
    *\return void
    */
    void change_base_status();

    /**\fn update_self()
    *\protected
    *\brief Método virtual de GameObject
    *\param now unsigned situacao atual
    *\param last unsigned ultima situacao passada
    *\return void
    */
    void update_self(unsigned now, unsigned last);
    
    /**\fn draw_self(()
    *\protected
    *\brief funcao que Desenha a base
    *\param *canvas Canvas
    *\param now unsigned
    *\param last unsigned
    *\return void
    */
    void draw_self(Canvas *canvas, unsigned now, unsigned last);


protected:
    
    /*\var base_player_id
     *\brief recebe o valor de player_id
     */
    unsigned base_player_id;
    
    /*\var base_life
     *\brief representa o valor da vida da base = 4000
     */
    int base_life;

    /*\var base_frame
     *\brief representa o frame da base no momento
    */
    int base_frame;

    /*\var base_start
     *\brief variavel que inicializa a base do player
     *inicia com -1
    */
    int base_start;

    /*\var base_width
     *\brief largura da base em pixels
    */
    int base_width;
    /*\var base_height
     *\brief altura da base em pixels
    */
    int base_height;

    /*\var base_status
     *\brief status da base, quantidade de esferas presentes na base
     *... vai de '8' a '0', se chegar a '0' muda o status para destruido
    */
    int base_status;

    /*\var base_sprite_paths
     *\brief vetor com as imagens em png
     */
    vector <string> base_sprite_paths;
    
    /*\var base_texture
     *\brief contem a textura da base
     */
    shared_ptr<Texture> base_texture;
    
    /*\var base_bounding_box
     *\brief delimita os limites da base
     */
    Rectangle base_bounding_box;
    
    /*\var base_axis_x_speed
     *\brief velocidade no eixo x
     */
    double base_axis_x_speed;
    
    /*\var base_axis_y_speed
     *\brief velocidade no eixo y
     */
    double base_axis_y_speed;

};

#endif