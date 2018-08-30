#ifndef IJENGINE_KERNEL_H
#define IJENGINE_KERNEL_H

#include "event.h"
#include "mouse_event.h"
#include "system_event.h"
#include "keyboard_event.h"
#include "joystick_event.h"

#include <string>
#include <list>

using std::list;
using std::string;

namespace ijengine {

    class Font;
    class Event;
    class Window;
    class Canvas;
    class Texture;
    
    class Kernel {
    public:
        virtual ~Kernel() {}
        
        virtual Window * create_window(const string& title, int w, int h,
            double scale) = 0;
        
		virtual void set_full_screen(int mode) = 0;

        virtual void set_audio_dir(const string& dir_path) = 0;
        virtual void play_audio_from_path(const string& title) = 0;
        virtual void stop_audio() = 0;
        virtual void play_sound_effect(const string& path, int volume, int loops) = 0;
        virtual void stop_audio_channel(int channel) = 0;
        virtual int set_audio_volume(double percentage) = 0;
        virtual int set_sound_effect_volume(double percentage) = 0;

    	virtual list<MouseEvent> pending_mouse_events(unsigned now) = 0;
    	virtual list<SystemEvent> pending_system_events(unsigned now) = 0;
    	virtual list<KeyboardEvent> pending_keyboard_events(unsigned now) = 0;
    	virtual list<JoystickEvent> pending_joystick_events(unsigned now) = 0;

        virtual unsigned time_elapsed() = 0;
        virtual void pause_timer() = 0;
        virtual void resume_timer() = 0;

        virtual Texture * load_texture(const Canvas* canvas, const string& filepath) = 0;
        virtual Font * load_font(const string& filepath, unsigned size) = 0;

        virtual pair<int, int> mouse_position() = 0;
    };
}

#endif
