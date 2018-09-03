#include "frost_nova.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#define FROST_NOVA_BASE_DAMAGE 40
#define SPEED_ATTACK 100

using namespace std;
using namespace ijengine;


FrostNova::FrostNova(GameObject *parent, unsigned hero_id, double x_position, double y_position, double x_direction,
    double y_direction)
    : Skill(parent, x_position, y_position, FROST_NOVA_BASE_DAMAGE, hero_id), character_id(hero_id), skill_x_direction(x_direction/hypot(x_direction, y_direction)),
        skill_y_direction(y_direction/hypot(x_direction, y_direction)), speed_attack(SPEED_ATTACK) 
{
    frame = 0;
    start = 0;
    sprite_path = choose_sprite_path(hero_id);

    texture = ijengine::resources::get_texture(sprite_path);
    x_position_frost_nova = x_position;
    y_position_frost_nova = y_position;
    double hypotenuse = sqrt(48 * 48 * 2);
    x_position_frost_nova -= hypotenuse / 2.0;
    y_position_frost_nova -= hypotenuse / 2.0;
    bounding_box = Rectangle(x_position_frost_nova, y_position_frost_nova, 96.00, 96.00);
    new_skill_damage = FROST_NOVA_BASE_DAMAGE;
    printf("Frost nova damage: %d\n", new_skill_damage);
}

FrostNova::~FrostNova()
{

}

void
FrostNova::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rectangle {(double) 96.0 * frame, 0.0, 96.00, 96.00};
    canvas->draw(texture.get(), rectangle, x(), y()); 
}

void
FrostNova::update_self(unsigned now_moment, unsigned last_moment)
{
    update_time(now_moment);
}

bool
FrostNova::active() const
{
    return true;
}

const Rectangle& 
FrostNova::bounding_box() const
{
    return bounding_box;
}

const list<Rectangle>&
FrostNova::hit_boxes() const {
    static list<Rectangle> boxes {bounding_box};
    return boxes;
}

pair<double, double>
FrostNova::direction() const
{
    return pair<double, double>(skill_x_direction, skill_y_direction);
}

void
FrostNova::update_time(unsigned now_moment)
{
    // if it's the first update self
    if(start == 0) {
        start = now_moment;
        current_time = now_moment;
    }

    if (now_moment - current_time > 100)
    {
        current_time += 100;
        frame = (frame + 1) % (texture->w() / 96);
    }

    if((current_time - start) > 100 * 6) {
        invalidate();
    }

}

string
FrostNova::choose_sprite_path(unsigned player_id)
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
FrostNova::on_collision(const Collidable *who, const Rectangle& where, unsigned now_moment, unsigned last_moment)
{
    const Character *character = dynamic_cast<const Character *>(who);
    const Base *base = dynamic_cast<const Base *>(who);

    bool character_verify = character and character->id() != character_id;
    bool base_verify = base and base->base_player_id() != character_id;

    if(character_verify) {
        skill_collided |= (1 << character->id());
    }
    if(base_verify) {
        skill_collided |= (1 << ((base->base_player_id() + 4)));
    }

    // if ( (c and c->id() != character_id) || (b and b->base_player_id() != character_id) )
    // {
    //     printf("OI\n");
    //     invalidate();
    // }
}