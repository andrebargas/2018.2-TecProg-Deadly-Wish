#ifndef IJENGINE_SDL2TIME_H
#define IJENGINE_SDL2TIME_H

#include <SDL2/SDL.h>
#include "time.h"

using namespace ijengine;

class SDL2Time : public Time {
public:
    SDL2Time();

private:
    unsigned real_time_elapsed() const;
};

#endif
