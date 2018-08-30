#include "point.h"

namespace ijengine
{
    Point::Point(double xv, double yv) :
        m_x(xv), m_y(yv)
    {
    }

    double
    Point::x() const {
        return m_x;
    }

    double
    Point::y() const {
        return m_y;
    }
}
