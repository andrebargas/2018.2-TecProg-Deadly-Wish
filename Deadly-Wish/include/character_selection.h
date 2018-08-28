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

    int current_selection() const { return m_current_selection; }
    int player_id() const { return m_player_id;}
    bool chosen() const {return m_chosen;}

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    bool on_event(const GameEvent& event);
    void update_position(); 

private:
    int m_player_id;
    int m_frame;
    int m_start;
    int m_current_selection;
    int m_w;
    int m_h;
    int m_base_x;
    int m_base_y;
    bool m_chosen;
    shared_ptr<Texture> m_texture;
};

#endif