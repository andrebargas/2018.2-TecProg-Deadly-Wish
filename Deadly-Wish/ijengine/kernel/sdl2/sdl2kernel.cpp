#include "sdl2kernel.h"
#include "sdl2window.h"
#include "sdl2font.h"
#include "sdl2time.h"
#include "sdl2texture.h"
#include "sdl2canvas.h"
#include "exception.h"
#include "event.h"
#include "system_event.h"
#include "keyboard_event.h"
#include "joystick_event.h"
#include "mouse_event.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

using namespace ijengine;
using std::vector;

MouseEvent::State button_state(int button_mask, int button_id);
static KeyboardEvent::Modifier key_modifier(Uint16 modifier);

vector<SDL_Joystick *> JOYSTICKS;

const int NUMBER_OF_MUSIC_CHANNELS = 20;

void when_channel_is_done(int channel) {
    printf("Channel being halted: %d\n", channel);
    Mix_Chunk *chunk = Mix_GetChunk(channel);
    if(chunk) {
        Mix_FreeChunk(chunk);
        chunk = nullptr;
    }
}

SDL2Kernel::SDL2Kernel()
{
    int rc = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);

    if (rc)
        throw Exception("Error on SDL2 initialization");


    for(int i = 0; i < SDL_NumJoysticks(); i++) {
        JOYSTICKS.push_back(SDL_JoystickOpen(i));
    }

    printf("%d joysticks are plugged.\n", SDL_NumJoysticks());

    rc = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 128);
    Mix_ChannelFinished(when_channel_is_done);

    if(rc) 
        throw Exception("Error on audio opening");

    rc = TTF_Init();

    if (rc)
        throw Exception("Error on SDL2_ttf initialization");

    m_timer = new SDL2Time();
    m_last_update = 0;

    init_table();
}

SDL2Kernel::~SDL2Kernel()
{
    for(auto joystick : JOYSTICKS) {
        SDL_JoystickClose(joystick);
    }

    Mix_CloseAudio();
    Mix_Quit();

    if (TTF_WasInit())
        TTF_Quit();

    if (SDL_WasInit(SDL_INIT_VIDEO))
        SDL_Quit();

}

Window *
SDL2Kernel::create_window(const string& title, int w, int h, double scale)
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer))
        return nullptr;

    SDL_SetWindowTitle(window, title.c_str());
    SDL_RenderSetScale(renderer, scale, scale);

	m_window = window;

    return new SDL2Window(window, renderer);
}

void
SDL2Kernel::set_full_screen(int mode)
{
    int flag;

    if(mode == 0)
        flag = 0;
    else if(mode == 1)
        flag = SDL_WINDOW_FULLSCREEN;
    else
        flag = SDL_WINDOW_FULLSCREEN_DESKTOP;

    SDL_SetWindowFullscreen(m_window, flag);
}

static KeyboardEvent::Modifier
key_modifier(Uint16 modifier)
{
    switch (modifier)
    {
    case KMOD_CAPS:
        return KeyboardEvent::CAPS;

    case KMOD_SHIFT:
        return KeyboardEvent::SHIFT;

    case KMOD_ALT:
        return KeyboardEvent::ALT;

    case KMOD_CTRL:
        return KeyboardEvent::CONTROL;

    default:
        return KeyboardEvent::NONE;
    }
}

void
SDL2Kernel::init_table()
{
    m_key_table[SDLK_BACKSPACE] = KeyboardEvent::BACKSPACE;
    m_key_table[SDLK_TAB] = KeyboardEvent::TAB;
    m_key_table[SDLK_CLEAR] = KeyboardEvent::CLEAR;
    m_key_table[SDLK_RETURN] = KeyboardEvent::RETURN;
    m_key_table[SDLK_PAUSE] = KeyboardEvent::PAUSE;
    m_key_table[SDLK_ESCAPE] = KeyboardEvent::ESCAPE;
    m_key_table[SDLK_SPACE] = KeyboardEvent::SPACE;
    m_key_table[SDLK_EXCLAIM] = KeyboardEvent::EXCLAIM;
    m_key_table[SDLK_QUOTEDBL] = KeyboardEvent::DOUBLE_QUOTE;
    m_key_table[SDLK_HASH] = KeyboardEvent::HASH;
    m_key_table[SDLK_DOLLAR] = KeyboardEvent::DOLLAR;

    m_key_table[SDLK_AMPERSAND] = KeyboardEvent::AMPERSAND;
    m_key_table[SDLK_QUOTE] = KeyboardEvent::QUOTE;
    m_key_table[SDLK_LEFTPAREN] = KeyboardEvent::LEFT_PARENTESIS;
    m_key_table[SDLK_RIGHTPAREN] = KeyboardEvent::RIGHT_PARENTESIS;
    m_key_table[SDLK_ASTERISK] = KeyboardEvent::ASTERISK;
    m_key_table[SDLK_PLUS] = KeyboardEvent::PLUS;
    m_key_table[SDLK_COMMA] = KeyboardEvent::COMMA;
    m_key_table[SDLK_MINUS] = KeyboardEvent::MINUS;
    m_key_table[SDLK_PERIOD] = KeyboardEvent::PERIOD;
    m_key_table[SDLK_SLASH] = KeyboardEvent::SLASH;

    m_key_table[SDLK_0] = KeyboardEvent::ZERO;
    m_key_table[SDLK_1] = KeyboardEvent::ONE;
    m_key_table[SDLK_2] = KeyboardEvent::TWO;
    m_key_table[SDLK_3] = KeyboardEvent::THREE;
    m_key_table[SDLK_4] = KeyboardEvent::FOUR;
    m_key_table[SDLK_5] = KeyboardEvent::FIVE;
    m_key_table[SDLK_6] = KeyboardEvent::SIX;
    m_key_table[SDLK_7] = KeyboardEvent::SEVEN;
    m_key_table[SDLK_8] = KeyboardEvent::EIGHT;
    m_key_table[SDLK_9] = KeyboardEvent::NINE;
    m_key_table[SDLK_COLON] = KeyboardEvent::COLON;
    m_key_table[SDLK_SEMICOLON] = KeyboardEvent::SEMICOLON;
    m_key_table[SDLK_LESS] = KeyboardEvent::LESS;
    m_key_table[SDLK_EQUALS] = KeyboardEvent::EQUALS;
    m_key_table[SDLK_GREATER] = KeyboardEvent::GREATER;

    m_key_table[SDLK_QUESTION] = KeyboardEvent::QUESTION;
    m_key_table[SDLK_AT] = KeyboardEvent::AT;
    m_key_table[SDLK_LEFTBRACKET] = KeyboardEvent::LEFT_BRACKET;
    m_key_table[SDLK_BACKSLASH] = KeyboardEvent::BACKSLASH;
    m_key_table[SDLK_RIGHTBRACKET] = KeyboardEvent::RIGHT_BRACKET;
    m_key_table[SDLK_CARET] = KeyboardEvent::CARET;
    m_key_table[SDLK_UNDERSCORE] = KeyboardEvent::UNDERSCORE;
    m_key_table[SDLK_BACKQUOTE] = KeyboardEvent::BACKQUOTE;
    m_key_table[SDLK_DELETE] = KeyboardEvent::DELETE;

    m_key_table[SDLK_a] = KeyboardEvent::A;
    m_key_table[SDLK_b] = KeyboardEvent::B;
    m_key_table[SDLK_c] = KeyboardEvent::C;
    m_key_table[SDLK_d] = KeyboardEvent::D;
    m_key_table[SDLK_e] = KeyboardEvent::E;
    m_key_table[SDLK_f] = KeyboardEvent::F;
    m_key_table[SDLK_g] = KeyboardEvent::G;
    m_key_table[SDLK_h] = KeyboardEvent::H;
    m_key_table[SDLK_i] = KeyboardEvent::I;
    m_key_table[SDLK_j] = KeyboardEvent::J;
    m_key_table[SDLK_k] = KeyboardEvent::K;
    m_key_table[SDLK_l] = KeyboardEvent::L;
    m_key_table[SDLK_m] = KeyboardEvent::M;
    m_key_table[SDLK_n] = KeyboardEvent::N;
    m_key_table[SDLK_o] = KeyboardEvent::O;
    m_key_table[SDLK_p] = KeyboardEvent::P;
    m_key_table[SDLK_q] = KeyboardEvent::Q;
    m_key_table[SDLK_r] = KeyboardEvent::R;
    m_key_table[SDLK_s] = KeyboardEvent::S;
    m_key_table[SDLK_t] = KeyboardEvent::T;
    m_key_table[SDLK_u] = KeyboardEvent::U;
    m_key_table[SDLK_v] = KeyboardEvent::V;
    m_key_table[SDLK_w] = KeyboardEvent::W;
    m_key_table[SDLK_x] = KeyboardEvent::X;
    m_key_table[SDLK_y] = KeyboardEvent::Y;
    m_key_table[SDLK_z] = KeyboardEvent::Z;

    m_key_table[SDLK_LEFT] = KeyboardEvent::LEFT;
    m_key_table[SDLK_RIGHT] = KeyboardEvent::RIGHT;
    m_key_table[SDLK_UP] = KeyboardEvent::UP;
    m_key_table[SDLK_DOWN] = KeyboardEvent::DOWN;

    m_key_table[SDLK_F1] = KeyboardEvent::F1;
    m_key_table[SDLK_F2] = KeyboardEvent::F2;
    m_key_table[SDLK_F3] = KeyboardEvent::F3;
    m_key_table[SDLK_F4] = KeyboardEvent::F4;
    m_key_table[SDLK_F5] = KeyboardEvent::F5;
    m_key_table[SDLK_F6] = KeyboardEvent::F6;
    m_key_table[SDLK_F7] = KeyboardEvent::F7;
    m_key_table[SDLK_F8] = KeyboardEvent::F8;
    m_key_table[SDLK_F9] = KeyboardEvent::F9;
    m_key_table[SDLK_F10] = KeyboardEvent::F10;
    m_key_table[SDLK_F11] = KeyboardEvent::F11;
    m_key_table[SDLK_F12] = KeyboardEvent::F12;

    m_button_table[SDL_CONTROLLER_BUTTON_INVALID] = JoystickEvent::BUTTON_INVALID;

    m_button_table[SDL_CONTROLLER_BUTTON_A] = JoystickEvent::TRIANGLE;
    m_button_table[SDL_CONTROLLER_BUTTON_B] = JoystickEvent::CIRCLE;
    m_button_table[SDL_CONTROLLER_BUTTON_X] = JoystickEvent::X;
    m_button_table[SDL_CONTROLLER_BUTTON_Y] = JoystickEvent::SQUARE;

    m_button_table[4] = JoystickEvent::L1;
    m_button_table[5] = JoystickEvent::R1;

    m_button_table[6] = JoystickEvent::L2;
    m_button_table[7] = JoystickEvent::R2;

    // m_button_table[SDL_CONTROLLER_BUTTON_BACK] = JoystickEvent::BACK;
    // m_button_table[SDL_CONTROLLER_BUTTON_GUIDE] = JoystickEvent::GUIDE;
    // m_button_table[SDL_CONTROLLER_BUTTON_START] = JoystickEvent::START;


    // m_button_table[SDL_CONTROLLER_BUTTON_DPAD_UP] = JoystickEvent::DPAD_UP;
    // m_button_table[SDL_CONTROLLER_BUTTON_DPAD_DOWN] = JoystickEvent::DPAD_DOWN;
    // m_button_table[SDL_CONTROLLER_BUTTON_DPAD_LEFT] = JoystickEvent::DPAD_LEFT;
    // m_button_table[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = JoystickEvent::DPAD_RIGHT;

    // m_button_table[SDL_CONTROLLER_BUTTON_MAX] = JoystickEvent::BUTTON_MAX;

    m_axis_table[SDL_CONTROLLER_AXIS_INVALID] = JoystickEvent::AXIS_INVALID;

    m_axis_table[SDL_CONTROLLER_AXIS_LEFTX] = JoystickEvent::LEFTX;
    m_axis_table[SDL_CONTROLLER_AXIS_LEFTY] = JoystickEvent::LEFTY;
    m_axis_table[SDL_CONTROLLER_AXIS_RIGHTX] = JoystickEvent::RIGHTX;
    m_axis_table[SDL_CONTROLLER_AXIS_RIGHTY] = JoystickEvent::RIGHTY;

    m_axis_table[SDL_CONTROLLER_AXIS_TRIGGERLEFT] = JoystickEvent::TRIGGERLEFT;
    m_axis_table[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] = JoystickEvent::TRIGGERRIGHT;

    m_axis_table[SDL_CONTROLLER_AXIS_MAX] = JoystickEvent::AXIS_MAX;
}

MouseEvent::State
button_state(int button_mask, int button_id)
{
    return (button_mask & button_id) == button_id ? MouseEvent::PRESSED :
        MouseEvent::RELEASED;
}

static string audio_dir_path { "." };

void
SDL2Kernel::set_audio_dir(const string& dir_path)
{
    audio_dir_path = dir_path;
}

void
SDL2Kernel::play_audio_from_path(const string& path)
{   
    if(Mix_PlayingMusic() == 0)
    {
        if(path.empty()) {
            printf("Empty audio path\n");
        }

        Mix_Music *audio;

        string audio_path = audio_dir_path + "/" + path;

        audio = Mix_LoadMUS(audio_path.c_str());

        if(not audio){
            printf("Failed to load audio\n");
            printf("error: %s\n", Mix_GetError());
        }

        Mix_FadeInMusic(audio, -1, 2000);
    }
}

void
SDL2Kernel::stop_audio()
{
    Mix_HaltMusic();
}

void
SDL2Kernel::play_sound_effect(const string& path, int volume, int loops)
{
    Mix_Chunk *effect = Mix_LoadWAV(path.c_str());

    if(not effect){
        printf("Failed to load sound effect\n");
    }

    Mix_VolumeChunk(effect, volume);
    Mix_PlayChannel(-1, effect, loops);
}

void
SDL2Kernel::stop_audio_channel(int channel) {
    Mix_HaltChannel(channel);
}

int
SDL2Kernel::set_audio_volume(double percentage)
{
    double new_volume = (MIX_MAX_VOLUME * percentage);

    // Mix_VolumeMusic(int volume, int loops)
    // if volume is -1, returns current volume
    int d = Mix_VolumeMusic(new_volume);

    return d;
}

int
SDL2Kernel::set_sound_effect_volume(double percentage){
    double new_volume = (MIX_MAX_VOLUME * percentage);

    // Mix_Volume(channel, volume)
    // if channel is -1, set volume to all channels
    int d = Mix_Volume(-1, new_volume);

    return d;
}

void
SDL2Kernel::update_pending_events(unsigned now)
{
    if (m_last_update == now)
        return;

    m_events.clear();
    SDL_PumpEvents();

    SDL_Event event;

    while (SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT,
        SDL_LASTEVENT) > 0)
    {
        unsigned timestamp = event.quit.timestamp;

        if (timestamp > now)
            break;

        SDL_PollEvent(&event);
        m_events.push_back(event);

        SDL_PumpEvents();
    }

    m_last_update = now;
}

list<JoystickEvent>
SDL2Kernel::pending_joystick_events(unsigned now)
{
    update_pending_events(now);
    auto it = m_events.begin();

    list<JoystickEvent> events;

    while (it != m_events.end())
    {
        unsigned timestamp = it->quit.timestamp;

        if (it->type == SDL_JOYBUTTONDOWN)
        {
            auto event = JoystickEvent(timestamp,
                JoystickEvent::State::BUTTON_PRESSED,
                m_button_table[it->jbutton.button],
                JoystickEvent::Axis::AXIS_INVALID,
                it->jbutton.which,
                it->jbutton.state);

            events.push_back(event);
            it = m_events.erase(it);
        } else if (it->type == SDL_JOYBUTTONUP)
        {
            auto event = JoystickEvent(timestamp,
                JoystickEvent::State::BUTTON_RELEASED,
                m_button_table[it->jbutton.button],
                JoystickEvent::Axis::AXIS_INVALID,
                it->jbutton.which,
                it->jbutton.state);

            events.push_back(event);
            it = m_events.erase(it);
        } else if (it->type == SDL_JOYAXISMOTION)
        {
            auto event = JoystickEvent(timestamp,
                JoystickEvent::State::AXIS_MOTION,
                JoystickEvent::Button::BUTTON_INVALID,
                m_axis_table[it->jaxis.axis],
                it->jaxis.which,
                it->jaxis.value);

            events.push_back(event);
            it = m_events.erase(it);
        } else
            ++it;
    }

    return events;
}

list<KeyboardEvent>
SDL2Kernel::pending_keyboard_events(unsigned now) {
    update_pending_events(now);
    auto it = m_events.begin();

    list<KeyboardEvent> events;

    while (it != m_events.end())
    {
        unsigned timestamp = it->quit.timestamp;

        if (it->type == SDL_KEYDOWN) {
            bool repeated = it->key.repeat != 0;
            auto event = KeyboardEvent(timestamp,
                KeyboardEvent::State::PRESSED,
                m_key_table[it->key.keysym.sym],   
                key_modifier(it->key.keysym.mod),
                repeated);

                events.push_back(event);
                it = m_events.erase(it);
        } else if (it->type == SDL_KEYUP)
        {
            bool repeated = it->key.repeat != 0;
            auto event = KeyboardEvent(timestamp,
                KeyboardEvent::State::RELEASED,
                m_key_table[it->key.keysym.sym],   
                key_modifier(it->key.keysym.mod),
                repeated);

                events.push_back(event);
                it = m_events.erase(it);
        } else
            ++it;
    }
 
    return events;
} 

list<MouseEvent>
SDL2Kernel::pending_mouse_events(unsigned now)
{
    update_pending_events(now);
    auto it = m_events.begin();

    list<MouseEvent> events;

    while (it != m_events.end())
    {
        unsigned timestamp = it->quit.timestamp;

        if (it->type == SDL_MOUSEBUTTONDOWN)
        {
            auto event = MouseEvent(timestamp, MouseEvent::PRESSED,
                button_state(it->button.button, SDL_BUTTON_LEFT),
                button_state(it->button.button, SDL_BUTTON_MIDDLE),
                button_state(it->button.button, SDL_BUTTON_RIGHT),
                it->button.x, it->button.y, 0, 0);

                events.push_back(event);
                it = m_events.erase(it);
        } else if (it->type == SDL_MOUSEBUTTONUP)
        {

            auto event = MouseEvent(timestamp, MouseEvent::RELEASED,
                button_state(it->button.button, SDL_BUTTON_LEFT),
                button_state(it->button.button, SDL_BUTTON_MIDDLE),
                button_state(it->button.button, SDL_BUTTON_RIGHT),
                it->button.x, it->button.y, 0, 0);

                events.push_back(event);
                it = m_events.erase(it);
        } else if (it->type == SDL_MOUSEMOTION)
        {
            auto event = MouseEvent(timestamp, MouseEvent::MOTION,
                button_state(it->button.button, SDL_BUTTON_LEFT),
                button_state(it->button.button, SDL_BUTTON_MIDDLE),
                button_state(it->button.button, SDL_BUTTON_RIGHT),
                it->button.x, it->button.y, it->motion.xrel, it->motion.yrel);

                events.push_back(event);
                it = m_events.erase(it);
        } else
            ++it;
    }

    return events;
}

list<SystemEvent>
SDL2Kernel::pending_system_events(unsigned now)
{
    update_pending_events(now);
    auto it = m_events.begin();

    list<SystemEvent> events;

    while (it != m_events.end())
    {
        if (it->type == SDL_QUIT)
        {
            unsigned timestamp = it->quit.timestamp;
            auto event = SystemEvent(timestamp, SystemEvent::Action::QUIT);
            events.push_back(event);
            it = m_events.erase(it);
        } else
            ++it;
    }

    return events;
}

unsigned
SDL2Kernel::time_elapsed() {
    return m_timer->time_elapsed();
}

void
SDL2Kernel::pause_timer() {
    m_timer->pause_timer();
}

void
SDL2Kernel::resume_timer() {
    m_timer->resume_timer();
}

Texture *
SDL2Kernel::load_texture(const Canvas* c, const string& filepath)
{
    const SDL2Canvas *canvas = dynamic_cast<const SDL2Canvas *>(c);
    SDL_Renderer *renderer = canvas->renderer();

    SDL_Texture *texture = IMG_LoadTexture(renderer, filepath.c_str());

    if (not texture)
        throw Exception(SDL_GetError());

    int w, h;

    int rc = SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    if (rc)
        throw Exception(SDL_GetError());

    SDL2Texture *t = new SDL2Texture(texture, w, h);
    return t;
}

Font *
SDL2Kernel::load_font(const string& filepath, unsigned size)
{
    TTF_Font *font = TTF_OpenFont(filepath.c_str(), size);

    if (not font)
        throw Exception(TTF_GetError());

    SDL2Font *f = new SDL2Font(filepath, size, font);
    return f;
}

pair<int, int>
SDL2Kernel::mouse_position()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    return pair<int, int>(x, y);
}

