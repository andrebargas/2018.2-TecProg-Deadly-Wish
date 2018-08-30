#include "test_game.h"

#include <ijengine/system_event.h>

TestGame::TestGame(const string& title, int w, int h)
    : m_game(title, w, h), m_engine(), m_level_factory()
{
    event::register_translator(&m_translator);
    level::register_factory(&m_level_factory);

    resources::set_fonts_dir("res");
}

TestGame::~TestGame()
{
    level::unregister_factory();
    event::unregister_translator(&m_translator);
}

int
TestGame::run(const string& level_id)
{
    return m_game.run(level_id);
}
