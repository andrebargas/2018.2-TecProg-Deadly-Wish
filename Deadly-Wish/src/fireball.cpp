/** \file fireball.cpp
  * \brief Este é o arquivo da classe Fireball, uma habilidade
  * do Character Mage, com herança da classe Skill
  */
#include "fireball.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define FIREBALL_BASE_DAMAGE 20
#define FIREBALL_WIDTH 32

using namespace std;
using namespace ijengine;

/** \fn Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx, double dy)
  * \public
  * \brief Método construtor
  * \param *parent Ponteiro para o GameObject
  * \param mage_id
  * \param xp direção no eixo x
  * \param yp direção no eixo y
  * \param dx
  * \param dy
  */
Fireball::Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx,
    double dy)
    : Skill(parent, xp, yp, FIREBALL_BASE_DAMAGE, mage_id), fireball_character_id(mage_id),
            fireball_axis_x_direction(dx/hypot(dx, dy)),
            fireball_axis_y_direction(dy/hypot(dx, dy)), fireball_speed(100.0)
{
    fireball_frame = 0;
    fireball_start = 0;
    fireball_sprite_path = choose_sprite_path(mage_id);
    fireball_texture = ijengine::resources::get_texture(fireball_sprite_path);
    fireball_bounding_box = Rectangle(m_x, m_y, 20, 20);

    //Atributos de GameObject
    fireball_axis_x_direction = xp;
    fireball_axis_y_direction = yp;

    if(fireball_axis_x_direction > 0) {
        fireball_state = MOVING_LEFT;
    }
    else {
        fireball_state = MOVING_RIGHT;
    }
}

/** \fn ~Fireball
  * \public
  * \brief Método destrutor
  */
Fireball::~Fireball()
{

}

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
void
Fireball::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double)FIREBALL_WIDTH * fireball_frame,
                    (double)FIREBALL_WIDTH * fireball_state,
                    (double)FIREBALL_WIDTH, (double)FIREBALL_WIDTH};

    canvas->draw(fireball_texture.get(),rect, x(), y());
}

// PBS
/** \fn update_self(unsigned now, unsigned last)
  * \protected
  * \brief Função para atualizar o tempo. Nome não pode ser mudado por ser um
  * metodo herdado da classe pai, protegida pelo escopo do projeto
  * \param now unsigned Tempo atual do jogo
  * \param last unsigned
  * \return void
  */
void
Fireball::update_self(unsigned now, unsigned last)
{
    update_time(now);

    if(fireball_current_time - fireball_start > 300) {
        double new_y = y() + fireball_axis_y_direction *  fireball_speed * (now - last) / 1000.0;
        double new_x = x() + fireball_axis_x_direction *  fireball_speed * (now - last) / 1000.0;
        set_position(new_x, new_y);

        fireball_bounding_box.set_position(x(), y());
    }
}

/** \fn active()
  * \public
  * \brief Estado do objeto usado pela Engine
  * \return bool fixo em true
  */
bool
Fireball::active() const
{
    return true;
}

/** \fn bounding_box()
  * \public
  * \brief Função da Engine que cria a caixa delimitadora do objeto
  * \return Rectangle& para habilidade FrostNova
  */
const Rectangle&
Fireball::bounding_box() const
{
    return fireball_bounding_box;
}

/** \fn hit_boxes()
  * \public
  * \brief Função que retorna uma lista com a caixa delimitadora do objeto criada pela Engine
  * \return list<Rectangle>& para habilidade Fireball
  */
const list<Rectangle>&
Fireball::hit_boxes() const {
    static list<Rectangle> boxes {fireball_bounding_box};
    return boxes;
}

/** \fn direction()
  * \public
  * \brief Função que retorna uma dupla com a direção no eixo x e no y do objeto
  * \return pair<double, double> direção da habilidade Fireball
  */
pair<double, double>
Fireball::direction() const
{
    return pair<double, double>(fireball_axis_x_direction, fireball_axis_y_direction);
}

/** \fn update_sprite_state()
  * \protected
  * \brief Função que atualiza o estado do sprite considerando os tempos, a largura e a textura da Fireball
  * \return void
  */
void
Fireball::update_sprite_state()
{
    if(fireball_current_time - fireball_start < 300) {
        fireball_frame = (fireball_frame + 1) % (fireball_texture->w() / FIREBALL_WIDTH);
    }

    else if(fireball_current_time - fireball_start > 300) {
        fireball_frame = (fireball_frame + 1) % (fireball_texture->w() / FIREBALL_WIDTH);

        if(fireball_frame >= 5){
            fireball_frame = 2;
        }
    }

  //  else if(m_current_time < -1) {
  //      m_frame = 5;
  //  }
}

/** \fn update_time(unsigned now)
  * \protected
  * \brief Método que atualiza os tempos da Fireball e o estado do seu sprite
  * \param now Tempo do jogo
  * \return void
  */
void
Fireball::update_time(unsigned now)
{
    // if it's the first update self
    if(fireball_start == 0) {
        fireball_start = now;
        fireball_current_time = now;
    }

    if (now - fireball_current_time > 150)
    {
        fireball_current_time += 150;
        update_sprite_state();
    }

    if((fireball_current_time - fireball_start) > 2000) {
        invalidate();
    }

}

/** \fn choose_sprite_path(unsigned player_id)
  * \protected
  * \brief Método que retorna o caminho do sprite de acordo com o id do jogador
  * \param player_id Identificador do jogador
  * \return void
  */
string
Fireball::choose_sprite_path(unsigned player_id)
{
    string directory = "Green";
    string sprite_path;

    switch(player_id) {
        case PLAYER_1:
            directory = "Green";
            break;

        case PLAYER_2:
            directory = "Blue";
            break;

        case PLAYER_3:
            directory = "Yellow";
            break;

        case PLAYER_4:
            directory = "Red";
            break;

        default:
            printf("Valor inválido na Spear\n");
            break;
    }

    sprite_path = "Spritesheets/" + directory + "/ObjectHadouken" + directory + ".png";

    return sprite_path;
}
