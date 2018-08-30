#ifndef IJENGINE_LINE_H
#define IJENGINE_LINE_H

namespace ijengine
{
    class Line {
    public:
        virtual ~Line() = default;
        Line(double x1, double y1, double x2, double y2);

        double x1() const;
        double y1() const;
        double x2() const;
        double y2() const;

    private:
        double m_x1;
        double m_y1;
        double m_x2;
        double m_y2;
    };
}

#endif
