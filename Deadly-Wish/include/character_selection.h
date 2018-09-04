#ifndef CHARACTER_SELECTION_H
#define CHARACTER_SELECTION_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/rectangle.h>
#include <ijengine/event.h>

#include <memory>
#include <string>

using std::shared_ptr;
using std::string;
using namespace ijengine;

class CharacterSelection : public GameObject, GameEventsListener {
public:
    CharacterSelection(const string sprite_path, int base_x, int base_y, int player_id);
    ~CharacterSelection();

    enum {
        KNIGHT,
        SOLDIER,
        MAGE,
        INFILTRATOR
    };

    int get_current_selection() const { return current_selection; }
    int player_id() const { return m_player_id;}
    bool chosen() const {return chosen;}

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    bool on_event(const GameEvent& event);
    void update_position(); 

private:
    int m_player_id;
    int frame;
    int start;
    int current_selection;
    int width;
    int height;
    int axis_base_x;
    int axis_base_y;
    bool chosen;
    shared_ptr<Texture> m_texture;
};

#endif