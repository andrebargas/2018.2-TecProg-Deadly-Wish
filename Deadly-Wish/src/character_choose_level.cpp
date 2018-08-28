#include "character_choose_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"
#include "test_level_factory.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/rectangle.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;
using namespace ijengine;
using std::vector;

CharacterChooseLevel::CharacterChooseLevel(const string& next_level)
    : m_done(false), m_next(next_level), m_start(-1)
{
    m_textures.push_back(resources::get_texture("character_selection/character_selection_background.png"));
    m_textures.push_back(resources::get_texture("character_selection/CharacterPortraits.png"));
    m_textures.push_back(resources::get_texture("character_selection/Icons.png"));

    m_number_of_players = 4;
    m_current_player = 1;
    m_frame = 0;

    int base_x = 120;
    for(int i = 0; i < m_number_of_players; i++) {
        m_character_selections.push_back(new CharacterSelection("character_selection/Pointers.png", base_x + 10 * i, 73, i));
        add_child(m_character_selections[i]);
    }

    m_selected_characters.resize(4);

    printf("antes de add o filho\n");
    printf("depois de add o filho\n");
    fflush(stdout);

    event::register_listener(this);
}

CharacterChooseLevel::~CharacterChooseLevel() {
    event::unregister_listener(this);
}

bool
CharacterChooseLevel::done() const
{
    return m_done;
}

string
CharacterChooseLevel::next() const
{
    return m_next;
}

string
CharacterChooseLevel::audio() const {
    return "music/menu_v1.ogg";
}

void
CharacterChooseLevel::update_self(unsigned now, unsigned)
{   
    int dones = 0;
    for(int i = 0; i < m_number_of_players; i++) {
        dones += m_character_selections[i]->chosen();
    }

    if(dones == 1) {
        if(!m_done) {
            for(int i = 0; i < m_number_of_players; i++) {
                int selection = m_character_selections[i]->current_selection();
                // if(selection == 0) {
                //     selection = 3;
                // }
                character_selection::players_characters.push_back(selection);
            }
        }
        m_done = true;
    }
}

void
CharacterChooseLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();
    // background
    canvas->draw(m_textures[BACKGROUND].get(), 0, 0);

    vector<Rectangle> portrait_rects;
    vector< pair<int, int> > rects_positions {{12, 12}, {208, 12}, {12, 128}, {208, 128}};
    for(int i = 0; i < m_number_of_players; i++) {
        Rectangle rect {(double) m_character_selections[i]->current_selection() * 100, i * 100, 100, 100};
        portrait_rects.push_back(rect);
        canvas->draw(m_textures[PORTRAITS].get(), rect, rects_positions[i].first, rects_positions[i].second);
    }
    
    vector< pair<double, double> > icons_start_coordinates {{122.4, 83.33}, {122.4, 126.66}, {165.6, 83.83},
        {165.6, 126.66}};

    for(int i = 0; i < 4; i++) {
        Rectangle rect {(double) 32 * i, 0.0, 32, 32};
        canvas->draw(m_textures[ICONS].get(), rect, icons_start_coordinates[i].first, icons_start_coordinates[i].second);
    }
}

bool
CharacterChooseLevel::on_event(const GameEvent& event) {
    return false;
}