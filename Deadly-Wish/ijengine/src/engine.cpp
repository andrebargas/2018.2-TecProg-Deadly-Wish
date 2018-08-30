#include "os.h"
#include "lib.h"
#include "font.h"
#include "event.h"
#include "kernel.h"
#include "engine.h"
#include "texture.h"
#include "rectangle.h"
#include "templates.h"
#include "exception.h"
#include "collidable.h"
#include "game_event.h"
#include "system_event.h"
#include "level_factory.h"
#include "events_translator.h"
#include "game_events_listener.h"

#include <list>
#include <memory>
#include <utility>

using namespace std;

namespace ijengine 
{
    static Kernel *kernel = nullptr;
    
    Engine::Engine()
    {
        auto files = os::list_files("libs");
        string path("");
        
        for (auto file : files)
            if (file.find("kernel") != string::npos) 
            {
                path = "libs/" + file;
                break;
            }
            
        if (path.size() == 0)
            throw Exception("Kernel not found in libs dir");
            
        m_kernel_lib = unique_ptr<Lib>(os::load_lib(path));
        
        if (not m_kernel_lib)
            throw Exception("Can't load kernel lib");
            
        auto sym = m_kernel_lib->symbol("create_kernel");
                          
        if (not sym)
            throw Exception("Invalid kernel: missing create_kernel()");
            
        Kernel * (*create)();
        *reinterpret_cast<void **>(&create) = sym;
        
        kernel = create();
        
        if (not kernel)
            throw Exception("Can't create the kernel");
    }
    
    Engine::~Engine()
    {
        resources::release_all();

        auto sym = m_kernel_lib->symbol("destroy_kernel");
                          
        if (not sym)
            throw Exception("Invalid kernel: missing destroy_kernel()");
            
        void (*destroy)(Kernel *);
        *reinterpret_cast<void **>(&destroy) = sym;
        
        destroy(kernel);
    }
    
    namespace video 
    {
        Window *
        create_window(const string& title, int w, int h, double scale)
        {
            return kernel->create_window(title, w, h, scale);
        }
        
        void
        set_full_screen(int mode) {
            return kernel->set_full_screen(mode);
        }
    }

    namespace audio
    {
        void
        set_audio_dir(const string& dir_path)
        {
            kernel->set_audio_dir(dir_path);
        }

        void
        play_audio_from_path(const string& path)
        {
            kernel->play_audio_from_path(path);
        }

        void
        stop_audio()
        {
            kernel->stop_audio();
        }

        void
        play_sound_effect(const string &path, int volume, int loops)
        {
            kernel->play_sound_effect(path, volume, loops);
        }

        int
        set_audio_volume(double percentage)
        {
            return kernel->set_audio_volume(percentage);
        }

        int
        set_sound_effect_volume(double percentage)
        {
            return kernel->set_sound_effect_volume(percentage);
        }

        void
        stop_audio_channel(int channel) {
            kernel->stop_audio_channel(channel);
        }
    }

    namespace event
    {
        static list<EventsTranslator *> translators;
        static list<GameEventsListener *> listeners;

        void
        dispatch_pending_events(unsigned now)
        {
            auto events = kernel->pending_system_events(now);
            auto game_events = translate<SystemEvent>(events, translators);

            auto keyboard_events = kernel->pending_keyboard_events(now);
            game_events.merge(translate<KeyboardEvent>(keyboard_events,
                translators));

            auto mouse_events = kernel->pending_mouse_events(now);
            game_events.merge(translate<MouseEvent>(mouse_events,
                translators));

            auto joystick_events = kernel->pending_joystick_events(now);
            game_events.merge(translate<JoystickEvent>(joystick_events,
                translators));

            game_events.sort();

            for (auto event : game_events)
            {
                for (auto listener : listeners)
                    if (listener->on_event(event))
                        break;
            }

        }

        pair<int, int>
        mouse_position()
        {
            return kernel->mouse_position();
        }

        void
        register_translator(EventsTranslator *translator)
        {
            if (translator) translators.push_back(translator);
        }

        void
        unregister_translator(EventsTranslator *translator)
        {
            if (translator) translators.remove(translator);
        }

        void
        register_listener(GameEventsListener *listener)
        {
            if (listener) listeners.push_back(listener);
        }

        void unregister_listener(GameEventsListener *listener)
        {
            if (listener) listeners.remove(listener);
        }
    }

    namespace time
    {
        unsigned
        time_elapsed()
        {
            return kernel->time_elapsed();
        }

        void
        pause()
        {
            kernel->pause_timer();
        }

        void
        resume()
        {
            kernel->resume_timer();
        }
    }

    namespace level
    {
        static LevelFactory *level_factory = nullptr;

        void
        register_factory(LevelFactory *factory)
        {
            level_factory = factory;
        }

        void unregister_factory()
        {
            level_factory = nullptr;
        }

        Level *
        make(const string& level_id)
        {
            return level_factory ? level_factory->make_level(level_id) : nullptr;
        }

        void
        release(Level *level)
        {
            if (level_factory)
                level_factory->release(level);
        }
    }

    namespace resources {

        static string textures_dir_path { "." };
        static string fonts_dir_path { "." };

        static map<string, shared_ptr<Texture> > textures;
        static map<pair<string, unsigned>, shared_ptr<Font> > fonts;

        static Canvas *canvas = nullptr;

        void
        set_textures_dir(const string& dir_path)
        {
            textures_dir_path = dir_path;
        }

        void
        set_fonts_dir(const string& dir_path)
        {
            fonts_dir_path = dir_path;
        }

        void
        set_canvas(Canvas *c)
        {
            canvas = c;
        }

        shared_ptr<Font>
        get_font(const string& name, unsigned size)
        {
            auto p = make_pair(name, size);
            auto it = fonts.find(p);

            if (it != fonts.end())
                return it->second;

            string filepath = fonts_dir_path + "/" + name;
            Font *font = kernel->load_font(filepath, size);

            if (not font)
                throw Exception("Can't load font " + filepath);

            fonts[p] = shared_ptr<Font>(font);

            return fonts[p];
        }

        shared_ptr<Texture>
        get_texture(const string& name)
        {
            if (not canvas)
                throw Exception("Can't load textures with a null canvas\n");

            auto it = textures.find(name);

            if (it != textures.end())
                return it->second;

            string filepath = textures_dir_path + "/" + name;
            Texture *texture = kernel->load_texture(canvas, filepath);

            if (not texture)
                throw Exception("Can't load texture " + filepath);

            textures[name] = shared_ptr<Texture>(texture);

            return textures[name];
        }

        void
        release_all()
        {
            textures.clear();
            fonts.clear();
        }
    }

    namespace physics {
        static Collidable *target = nullptr;
        static list<Collidable *> objects;
        static Mode collisions_mode = ALL_TO_ALL;

        Rectangle collision(Collidable *a, Collidable *b);

        void
        register_object(Collidable *c)
        {
            if (c)
                objects.push_back(c);
        }

        void
        unregister_object(Collidable *c)
        {
            objects.remove(c);

            if (target == c)
                target = nullptr;
        }
        
        Rectangle
        collision(Collidable *a, Collidable *b)
        {
            auto bbA = a->bounding_box();
            auto bbB = b->bounding_box();

            auto r = bbA.intersection(bbB);

            if (r.area() > 0)
                return r;

            return Rectangle(0, 0, 0, 0);
        }

        void
        do_collisions(unsigned now, unsigned last)
        {
            switch (collisions_mode) {
            case ONE_TO_ALL:
                for (auto obj : objects)
                {
                    if (obj == target or not target->active() or not obj->active())
                        continue;

                    auto r = collision(target, obj);

                    if (r.area() > 0)
                    {
                        target->on_collision(obj, r, now, last);
                        obj->on_collision(target, r, now, last);
                    }
                }

                break;

            case ALL_TO_ALL:
                for (auto a : objects)
                {
                    if (not a->active())
                        continue;

                    for (auto b : objects)
                    {
                        if (a == b or not b->active())
                            continue;

                        auto r = collision(a, b);

                        if (r.area() > 0)
                        {
                            a->on_collision(b, r, now, last);
                            b->on_collision(a, r, now, last);
                        }
                    }
                }

                break;

            default:
                break;
            }
        }

        void
        set_collision_mode(Mode mode, Collidable *c)
        {
            collisions_mode = mode;

            if (c and mode == ONE_TO_ALL)
                target = c;
        }
    }
}
