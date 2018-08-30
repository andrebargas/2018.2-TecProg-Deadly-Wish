#ifndef IJENGINE_COLOR_H
#define IJENGINE_COLOR_H

namespace ijengine
{
    using byte = unsigned char;

    class Color {
    public:
        Color(byte R, byte G, byte B, byte A = 255)
            : m_r(R), m_g(G), m_b(B), m_a(A) { }

        byte r() const { return m_r; }
        byte g() const { return m_g; }
        byte b() const { return m_b; }
        byte a() const { return m_a; }

        void set_r(byte value) { m_r = value; }
        void set_g(byte value) { m_g = value; }
        void set_b(byte value) { m_b = value; }
        void set_a(byte value) { m_a = value; }

        void set(byte R, byte G, byte B, byte A = 255)
        {
            m_r = R;
            m_g = G;
            m_b = B;
            m_a = A;
        }

        static const Color WHITE;
        static const Color BLACK;

    private:
        byte m_r, m_g, m_b, m_a;
    };
}

#endif
