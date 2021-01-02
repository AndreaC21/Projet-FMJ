// scene.h

#ifndef _SCENE_H_
#define _SCENE_H_

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <regex> // for split load_obj_file

// Allow log messages.
#define _LOG_
#include "log.h"

#include "camera.h"
#include "ibehavior.h"
#include "gui.h"
//#include "libgeometry.h"
#include "../include/libgeometry.hpp"
#include "object3d.h"

using namespace libgeometry;
using namespace gui;

//! Scene
class Scene
{
    public:
        // Constructor and destructor.
        Scene() {}

        // Get/set.
        void set_running( bool b ) { this->running = b; };

        // Initialise, loop and shutdown.
        bool initialise( int argc, const char * argv[] );
        void run_loop();
        void shutdown();

        void move_forward();
        void stop_forward();
        void move_backward();
        void stop_backward();
        void move_up();
        void stop_up();
        void move_down();
        void stop_down();
        void move_right();
        void stop_right();
        void move_left();
        void stop_left();
        // TODO: turn, zoom, ...

        void register_behavior( KeyCode key, IBehavior * const behavior );

        unsigned int get_win_width() const;
        unsigned int get_win_height() const;
        // TODO:
        //void add_object( Object3D * );

    private:
        const std::string title { "3D Scene Viewer" };
        const unsigned int win_width { 1024 };
        const unsigned int win_height { 768 };
        const Color background_color { black };

        // Max 60 FPS (i.e. minimum of 16 ms between frames).
        //const unsigned int min_frame_delay { 16 };
        // If the frame rate is to slow then do not go further than 0.5 sec in the future.
        const float delta_time_limit { 0.5f };
        // Counter of ticks for FPS calculations
        Uint32 ticks_count { 0u };

        // Pointer to the graphical interface.
        Screen * screen { nullptr };

        // Controls whether the game should continue to run.
        bool running { true };

        // The camera.
        Camera camera;

        // TODO: Objects container.
        std::vector< Object3D * > objects;

        // Key state behaviors container.
        // Only one behaviour for each key state is possible.
        // It is sufficient for this application.
        std::map< KeyCode, IBehavior * > key_state_behaviors { };

        // Behaviors.
        IBehavior * quit_behavior{ nullptr };
        IBehavior * forward_behavior{ nullptr };
        IBehavior * backward_behavior{ nullptr };
        IBehavior * up_behavior{ nullptr };
        IBehavior * down_behavior{ nullptr };
        IBehavior * right_behavior{ nullptr };
        IBehavior * left_behavior{ nullptr };
        // TODO: more behaviors, movement, turn, zoom...

        bool show_move_forward { false };
        bool show_move_backward { false };
        bool show_move_up { false };
        bool show_move_down { false };
        bool show_move_right{ false };
        bool show_move_left { false };
        bool show_turn_forward { false };
        bool show_turn_backward { false };
        bool show_turn_up { false };
        bool show_turn_down { false };
        bool show_turn_right{ false };
        bool show_turn_left { false };
        // TODO: more behaviors, movement, turn, zoom...

        // Helper functions.
        void process_input();
        void update();
        void generate_output() const;
        
        void load_data( int argc, const char * argv[] );
        void load_obj_file( const char * file_name );
        void unload_data();

        void draw() const;
        void draw_object( Object3D * const, float * ) const;
        void draw_wire_triangle( const Triangle & ) const;
        void draw_edge( const Point<float, 4> &, const Point<float, 4> & ) const;
    
        Point<float, 4> perspective_projection( const Point<float, 4> & ) const;

        void show_cam_params() const;
        void show_fr_params() const;
        void show_help() const;
};

//! Quit behavior.
class Quit : public IBehavior
{
    public:
        Quit( Scene & );
        void start() const override;
        void stop() const override;

    private:
        Scene & owner;
};

//! Forward behavior.
class Forward : public IBehavior
{
    public:
        Forward( Scene & s );
        void start() const override;
        void stop() const override;

    private:
        Scene & owner;
};

//! Backward behavior.
class Backward : public IBehavior
{
    public:
        Backward( Scene & );
        void start() const override;
        void stop() const override;

    private:
        Scene & owner;
};
class Up : public IBehavior
{
    public:
        Up( Scene & s );
        void start() const override;
        void stop() const override;

    private:
        Scene & owner;
};

//! Down behavior.
class Down : public IBehavior
{
    public:
        Down( Scene & );
        void start() const override;
        void stop() const override;

    private:
        Scene & owner;
};
class Right : public IBehavior
{
    public:
        Right( Scene & s );
        void start() const override;
        void stop() const override;

    private:
        Scene & owner;
};

//! Left behavior.
class Left : public IBehavior
{
    public:
        Left( Scene & );
        void start() const override;
        void stop() const override;

    private:
        Scene & owner;
};
#include "../src/scene.tpp"
#endif // _SCENE_H_
