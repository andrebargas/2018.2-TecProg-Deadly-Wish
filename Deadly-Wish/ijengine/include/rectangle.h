#ifndef IJENGINE_RECTANGLE_H
#define IJENGINE_RECTANGLE_H

namespace ijengine
{
    class Rectangle {
    public:
        virtual ~Rectangle() = default;
        Rectangle(double x = 0.0, double y = 0.0, double w = 1.0, double h = 1.0);

        double x() const;
        double y() const;
        double w() const;
        double h() const;
        double area() const;

        void set_position(double new_x, double new_y);
        Rectangle intersection(const Rectangle& r) const;

    private:
        double m_x; // coordinate x of the rectangle's CENTER
        double m_y; // coordinate y of the rectangle's CENTER
        double m_w; // width of the rectangle
        double m_h; // height of the rectangle
    };
}

#endif
