#ifndef IJENGINE_POINT_H
#define IJENGINE_POINT_H

namespace ijengine
{

    class Point {
    public:
        Point(double x, double y);   

        double x() const;
        double y() const;

    private:
        double m_x;
        double m_y;
    };
}

#endif
