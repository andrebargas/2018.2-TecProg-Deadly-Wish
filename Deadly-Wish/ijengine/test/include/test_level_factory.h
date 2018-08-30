#ifndef TEST_LEVEL_FACTORY_H
#define TEST_LEVEL_FACTORY_H

#include <ijengine/level_factory.h>

using namespace ijengine;

class TestLevelFactory : public LevelFactory {
public:
    Level * make_level(const string& level_id);
    void release(Level *level);
};

#endif
