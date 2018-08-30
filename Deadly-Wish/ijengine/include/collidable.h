#ifndef IJENGINE_COLLIDABLE_H
#define IJENGINE_COLLIDABLE_H


#include <list>
#include <utility>

using std::list;
using std::pair;

namespace ijengine
{
    class Rectangle;

    class Collidable {
    public:
        virtual ~Collidable() = default;

        virtual bool active() const = 0;
        virtual pair<double, double> direction() const = 0;

        virtual const Rectangle& bounding_box() const = 0;
        virtual const list<Rectangle>& hit_boxes() const = 0;

        virtual void on_collision(const Collidable *who, const Rectangle& where, const unsigned now, const unsigned last) = 0;
    };
}

#endif 
