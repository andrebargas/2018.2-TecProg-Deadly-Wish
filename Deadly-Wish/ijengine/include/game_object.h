#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

using std::vector;

namespace ijengine {

    class Canvas;

    class GameObject {
    public:
        typedef enum { LOWEST = 10000, LOW = 20000, NORMAL = 30000, 
            HIGH = 40000, HIGHEST = 50000 } Priority;

        GameObject(GameObject *parent = nullptr, double x = 0.0, double y = 0.0,
            int priority = NORMAL);

        virtual ~GameObject();

        void add_child(GameObject *obj);
        void remove_child(GameObject *obj);
        void destroy_child(GameObject *obj);

        double x() const;
        double y() const;
        GameObject * parent() const { return m_parent; }

        void set_x(double value) { m_x = value; }
        void set_y(double value) { m_y = value; }
        void set_position(double xv, double yv) { m_x = xv; m_y = yv; }
        void set_priority(int priority);
        void set_parent(GameObject *obj) { m_parent = obj; }

        void update(unsigned now, unsigned last);
        void draw(Canvas *canvas, unsigned now, unsigned last);

        int priority() const { return m_priority; }

        bool valid() const { return m_valid; }
        void invalidate() { m_valid = false; }

    protected:
        GameObject *m_parent;
        vector<GameObject *> m_children;
        double m_x, m_y;
        int m_priority;
        bool m_valid;

        virtual void update_self(unsigned now, unsigned last) = 0;
        virtual void draw_self(Canvas *canvas, unsigned now, unsigned last) = 0;
        virtual void draw_self_after(Canvas *, unsigned, unsigned) {}

        void update_priorities();
    };

}

#endif
