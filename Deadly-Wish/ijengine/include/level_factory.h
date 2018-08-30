#ifndef IJENGINE_LEVEL_FACTORY_H
#define IJENGINE_LEVEL_FACTORY_H

namespace ijengine
{
    class LevelFactory {
    public:
        virtual ~LevelFactory() = default;

        virtual Level * make_level(const string& level_id) = 0;
        virtual void release(Level *level) = 0;
    };
}

#endif
