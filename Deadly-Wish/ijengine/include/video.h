#ifndef VIDEO_H
#define VIDEO_H

#include <string>

using std::string;

namespace ijengine {

    class Window;

    class Video {
    public:
        virtual ~Video() = default;
        virtual Window * create_window(const string& title, int w, int h) = 0;
		virtual void set_full_screen(int mode) = 0;
    };

}

#endif
