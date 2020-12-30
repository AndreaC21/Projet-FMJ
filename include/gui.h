// gui.h
//
// This implementation uses the Simple Directmedia Layer <libsdl.org>.

#ifndef _GUI_H_
#define _GUI_H_

#include <SDL2/SDL.h>

// Uncomment the line below for Ubuntu.
//#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_ttf.h>

// Uncomment the line below for MacOS.
//#include <SDL_ttf.h>

#include <sstream>

//#include "libmatrix.h"
#include "../include/libmatrix.hpp"
#include "log.h"

using namespace libmatrix;

namespace gui {

class Color 
{
    public:
        float red;
        float green;
        float blue;
        float alpha;

        SDL_Color to_sdl_color() const;
        std::string to_string() const;
};

//! Color names (add more if you need).
static constexpr Color black        { 0.0f,  0.0f,  0.0f,  0.0f };
static constexpr Color white        { 1.0f,  1.0f,  1.0f,  0.0f };
static constexpr Color red          { 1.0f,  0.0f,  0.0f,  0.0f };
static constexpr Color green        { 0.0f,  1.0f,  0.0f,  0.0f };
static constexpr Color blue         { 0.0f,  0.0f,  1.0f,  0.0f };
static constexpr Color darkgrey     { 0.86f, 0.86f, 0.86f, 0.0f };
static constexpr Color grey         { 0.5f,  0.5f,  0.5f,  0.0f };

//! Keyboard key codes (add more if you need).
using KeyCode = int;
static constexpr KeyCode KEY_ESCAPE = SDL_SCANCODE_ESCAPE;
static constexpr KeyCode KEY_Q = SDL_SCANCODE_Q;
static constexpr KeyCode KEY_W = SDL_SCANCODE_W;
static constexpr KeyCode KEY_E = SDL_SCANCODE_E;
static constexpr KeyCode KEY_A = SDL_SCANCODE_A;
static constexpr KeyCode KEY_S = SDL_SCANCODE_S;
static constexpr KeyCode KEY_D = SDL_SCANCODE_D;
static constexpr KeyCode KEY_Z = SDL_SCANCODE_Z;
static constexpr KeyCode KEY_X = SDL_SCANCODE_X;
static constexpr KeyCode KEY_C = SDL_SCANCODE_C;
static constexpr KeyCode KEY_UP = SDL_SCANCODE_UP;
static constexpr KeyCode KEY_DOWN = SDL_SCANCODE_DOWN;
static constexpr KeyCode KEY_LEFT = SDL_SCANCODE_LEFT;
static constexpr KeyCode KEY_RIGHT = SDL_SCANCODE_RIGHT;

//! Defines screen (user interface).
class Screen
{
    public:
        Screen();
        ~Screen();

        // Get/set.
        std::string get_title() const { return this->title; }
        unsigned int get_width() const { return this->width; }
        unsigned int get_height() const { return this->height; }
        Color get_background_color() const { return this->background_color; }
        Color get_foreground_color() const { return this->foreground_color; }
        void set_title( std::string title ) { this->title = title; }
        void set_width( unsigned int width ) { this->width = width; this->window_center[0] = static_cast<int>( this->width / 2 ); }
        void set_height( unsigned int height ) { this->height = height; this->window_center[1] = static_cast<int>( this->height / 2 ); }
        void set_background_color( Color color ) { this->background_color = color; }
        void set_foreground_color( Color color ) { this->foreground_color = color; }

        void render_line( Vec2r, Vec2r, Color ) const;
        void render_point( Vec2r, Color ) const;
        void render_text( Vec2r, std::string, Color ) const;

        // Initialise and shutdown.
        bool start();
        void stop();

        void clear( Color ) const;
        void update();

    private:
        SDL_Window* window { nullptr };
        SDL_Renderer* renderer { nullptr };
        TTF_Font* font { nullptr };

        std::string title { "Screen" };
        unsigned int width { 600 };
        unsigned int height { 400 };
        Color background_color { darkgrey };
        Color foreground_color { white };

        const char ttf_file[25] = "fonts/DejaVuSansMono.ttf";
        const unsigned int default_font_size { 12 };
        Vec2i window_center 
        {
            static_cast<int>( width / 2 ),
            static_cast<int>( height / 2 )
        };

        // Ticks (to be able to count frames per second).
        unsigned int start_ticks;
        unsigned int num_frames;
        unsigned int fps;

        // Helper functions.
        void render_line_naive( int, int, int, int ) const;
        void render_line_incr( int, int, int, int ) const;
        void render_line_midle( int, int, int, int ) const;
        void render_line_bresenham( int, int, int, int ) const;

        Vec2i screen_coords( Vec2r ) const;
        inline void draw_point( int, int ) const;
};

//! Defines a GUI exception.
class GuiException : std::exception
{
    public:
        virtual const char * what() const noexcept = 0;
};

class GuiSdlException : GuiException
{
    public:
        const char * what() const noexcept;
};

class GuiTtfException : GuiException
{
    public:
        const char * what() const noexcept;
};

} // namespace gui

#include "../src/gui.tpp"
#endif // _GUI_H_
