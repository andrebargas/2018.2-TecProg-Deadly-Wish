#include "test_level.h"
#include "test_level_factory.h"

Level *
TestLevelFactory::make_level(const string& level_id)
{
    if (level_id == "red")
        return new TestLevel(255, 0, 0, "green", "res/beat.wav");
    else if (level_id == "green")
        return new TestLevel(0, 255, 0, "blue", "res/sweep.mp3");
    else if (level_id == "blue")
        return new TestLevel(0, 0, 255, "", "res/laser.mp3");
    else
        return nullptr;
}

void
TestLevelFactory::release(Level *level)
{
    delete level;
}

