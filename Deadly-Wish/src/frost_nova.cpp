#include "frost_nova.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define FROST_NOVA_BASE_DAMAGE 40


using namespace std;
using namespace ijengine;


FrostNova::FrostNova(GameObject *parent, unsigned mage_id, double xp, double yp, double dx,
    double dy)
    : Skill(parent, xp, yp, FROST_NOVA_BASE_DAMAGE, mage_id), character_id(mage_id), m_dx(dx/hypot(dx, dy)),
        m_dy(dy/hypot(dx, dy)), speed(100.0)

{
    frame = 0;
    start = 0;
    sprite_path = ChooseSpritePath(mage_id);

    m_texture = ijengine::resources::get_texture(sprite_path);
    m_x = xp;
    m_y = yp;
    double hip = sqrt(48 * 48 * 2);
    m_x -= hip / 2.0;
    m_y -= hip / 2.0;
    bounding_box = Rectangle(m_x, m_y, 96.00, 96.00);
    damage = FROST_NOVA_BASE_DAMAGE;
    printf("Frost nova damage: %d\n", damage);
}

FrostNova::~FrostNova()
{

}

void
FrostNova::DrawSelf(Canvas *canvas, unsigned, unsigned)
{

    Rectangle rect {(double) 96.0 * frame, 0.0, 96.00, 96.00};
    canvas->draw(m_texture.get(),rect, x(), y());

}

void
FrostNova::UpdateSelf(unsigned now, unsigned last)
{
    UpdateTime(now);
}

bool
FrostNova::Active() const
{
    return true;
}


const Rectangle& FrostNova::bounding_box() const {
  
    return bounding_box;
}

const list<Rectangle>&
FrostNova::HitBoxes() const {
    static list<Rectangle> boxes {bounding_box};
    return boxes;
}

pair<double, double>
FrostNova::Direction() const
{
    return pair<double, double>(m_dx, m_dy);
}

void
FrostNova::UpdateTime(unsigned now)
{
    // if it's the first update self
    if(start == 0) {
        start = now;
        current_time = now;
    }

    if (now - current_time > 100)
    {
        current_time += 100;
        frame = (frame + 1) % (texture->w() / 96);
    }

    if((current_time - start) > 100 * 6) {
        invalidate();
    }

}

string
FrostNova::ChooseSpritePath(unsigned player_id)
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
            printf("Valor inválido na FrostNova\n");
            break;
    }

    sprite_path = "Spritesheets/" + directory + "/ObjectFrostNova" + directory + ".png";

    return sprite_path;
}

void
FrostNova::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last)
{
    const Character *c = dynamic_cast<const Character *>(who);
    const Base *b = dynamic_cast<const Base *>(who);

    bool c_bool = c and c->id() != character_id;
    bool b_bool = b and b->base_player_id() != character_id;


    if(c_bool) {
        m_collided |= (1 << c->get_id());
    }
    if(b_bool) {
        m_collided |= (1 << ((b->base_player_id() + 4)));
    }

    // if ( (c and c->get_id() != m_character_id) || (b and b->base_player_id() != m_character_id) )
    // {
    //     printf("OI\n");
    //     invalidate();
    // }
}
