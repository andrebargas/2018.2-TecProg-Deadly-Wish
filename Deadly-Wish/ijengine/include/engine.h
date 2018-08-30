#ifndef IJENGINE_ENGINE_H
#define IJENGINE_ENGINE_H

#include <string>
#include <memory>

using std::pair;
using std::string;
using std::unique_ptr;
using std::shared_ptr;

namespace ijengine {
    
    class Lib;
    class Font;
    class Level;
    class Window;
    class Canvas;
    class Texture;
    class Collidable;
    class LevelFactory;
    class EventsTranslator;
    class GameEventsListener;
    
    class Engine {
    public:
        Engine();
        ~Engine();    
        
    private:
        unique_ptr<Lib> m_kernel_lib;
    };
    
    namespace video {
        Window * create_window(const string& title, int w, int h, double scale);
		void set_full_screen(int mode);

    }

    namespace audio {
        void set_audio_dir(const string& dir_path);
        void play_audio_from_path(const string& path);
        void stop_audio();

        void play_sound_effect(const string &path, int volume, int loops);
        void stop_audio_channel(int channel);
        int set_audio_volume(double percentage);
        int set_sound_effect_volume(double percentage);

    }

    namespace event {
        void dispatch_pending_events(unsigned now);
        void register_translator(EventsTranslator *translator);
        void unregister_translator(EventsTranslator *translator);
        void register_listener(GameEventsListener *listener);
        void unregister_listener(GameEventsListener *listener);
        pair<int, int> mouse_position(); 
    }

    namespace time {
        unsigned time_elapsed();
        void pause();
        void resume();
    }

    namespace level {
        void register_factory(LevelFactory *factory);
        void unregister_factory();
        Level * make(const string& level_id);
        void release(Level *level);
    }

    namespace resources {
        void set_textures_dir(const string& dir_path);
        void set_fonts_dir(const string& dir_path);
        void set_canvas(Canvas *canvas);

        shared_ptr<Texture> get_texture(const string& name);
        shared_ptr<Font> get_font(const string& name, unsigned size);

        void release_all();
    }

    namespace physics {
        typedef enum { ONE_TO_ALL, ALL_TO_ALL, NONE } Mode;

        void register_object(Collidable *c);
        void unregister_object(Collidable *c);
        void do_collisions(unsigned now, unsigned last);
        void set_collision_mode(Mode mode, Collidable *c = nullptr);
    }
}

#endif
