#include "game_object.h"

#include <algorithm>

using std::stable_sort;

namespace ijengine {

    GameObject::GameObject(GameObject *obj, double xpos, double ypos,
        int p) : m_parent(nullptr), m_x(xpos), m_y(ypos),
        m_priority(p), m_valid(true)
    {
        if (obj)
        {
            obj->add_child(this);
        }
    }

    GameObject::~GameObject()
    {
        for (auto obj : m_children)
            delete obj;
    }

    void
    GameObject::add_child(GameObject *obj)
    {
        if (not obj)
            return;

        auto p = obj->parent();

        if (p)
        {
            if (p != this)
                p->remove_child(obj);
            else
                return;
        }
        
        m_children.push_back(obj);
        obj->set_parent(this); 
        update_priorities();
    }

    void
    GameObject::destroy_child(GameObject *obj)
    {
        remove_child(obj);
        delete obj;
    }

    void
    GameObject::remove_child(GameObject *obj)
    {
        if (obj)
        {
            obj->set_parent(nullptr);
            m_children.erase(remove(m_children.begin(), m_children.end(), obj));
            update_priorities();
        }
    }

    void
    GameObject::update_priorities()
    {
        stable_sort(m_children.begin(), m_children.end(),
            [](GameObject *a, GameObject *b)
                { return a->priority() < b->priority(); }
        );
    }

    void
    GameObject::set_priority(int p)
    {
        if (p != m_priority)
        {
            m_priority = p;

            if (m_parent)
                m_parent->update_priorities();
        }
    }

    double
    GameObject::x() const
    {
        return m_x + (m_parent ? m_parent->x() : 0);
    }

    double
    GameObject::y() const
    {
        return m_y + (m_parent ? m_parent->y() : 0);
    }

    void
    GameObject::update(unsigned now, unsigned last)
    {
        for (auto child : m_children)
            child->update(now, last);

        update_self(now, last);
        
        for (size_t i = 0; i < m_children.size(); ++i)
            if (not m_children[i]->valid())
            {
                destroy_child(m_children[i]);
            }
    }

    void
    GameObject::draw(Canvas *canvas, unsigned now, unsigned last)
    {
        draw_self(canvas, now, last);

        for (auto child : m_children)
            child->draw(canvas, now, last);

        draw_self_after(canvas, now, last);
    }
}
