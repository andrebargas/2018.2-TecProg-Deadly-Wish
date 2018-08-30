#include "line.h"

namespace ijengine
{
    Line::Line(double x1v, double y1v, double x2v, double y2v) :
        m_x1(x1v), m_y1(y1v), m_x2(x2v), m_y2(y2v)
    {
    }

    double
    Line::x1() const {
        return m_x1;
    }

    double
    Line::y1() const {
        return m_y1;
    }

    double
    Line::x2() const {
        return m_x2;
    }

    double
    Line::y2() const {
        return m_y2;
    }
}
