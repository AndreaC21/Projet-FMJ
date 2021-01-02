// camera.h

#ifndef _CAMERA_H_
#define _CAMERA_H_

/*
#include "libmatrix.h"
#include "libgeometry.h"
*/
#include "../include/libgeometry.hpp"
#include "../include/libmatrix.hpp"
#include "frustum.hpp"

using namespace libmatrix;
using namespace libgeometry;

class Camera
{
    // You may change these values to fit your application.
    const float move_speed { 0.1f };
    const float turn_speed { 1.0f };
    const float zoom_speed { 1.0f };

    public:
        Camera() {}

        // Movement.
        void move_forward() { this->curr_move_speed[2] = Camera::move_speed; }
        void stop_forward() { this->curr_move_speed[2] = 0.0f; }
        void move_backward() { this->curr_move_speed[2] = -Camera::move_speed; }
        void stop_backward() { this->curr_move_speed[2] = 0.0f; }

        void move_up() { this->curr_move_speed[1] = Camera::move_speed; }
        void stop_up() { this->curr_move_speed[1] = 0.0f; }   
        void move_down() { this->curr_move_speed[1] = -Camera::move_speed; }
        void stop_down() { this->curr_move_speed[1] = 0.0f; }

        void move_right() { this->curr_move_speed[0] = Camera::move_speed; }
        void stop_right() { this->curr_move_speed[0] = 0.0f; }   
        void move_left() { this->curr_move_speed[0] = -Camera::move_speed; }
        void stop_left() { this->curr_move_speed[0] = 0.0f; }

        //Turn
        void turn_forward() { this->curr_turn_speed[2] = Camera::turn_speed; }
        void stop_turn_forward() { this->curr_turn_speed[2] = 0.0f; }
        void turn_backward() { this->curr_turn_speed[2] = -Camera::turn_speed; }
        void stop_turn_backward() { this->curr_turn_speed[2] = 0.0f; }

        void turn_up() { this->curr_turn_speed[1] = Camera::turn_speed; }
        void stop_turn_up() { this->curr_turn_speed[1] = 0.0f; }   
        void turn_down() { this->curr_turn_speed[1] = -Camera::turn_speed; }
        void stop_turn_down() { this->curr_turn_speed[1] = 0.0f; }

        void turn_right() { this->curr_turn_speed[0] = Camera::turn_speed; }
        void stop_turn_right() { this->curr_turn_speed[0] = 0.0f; }   
        void turn_left() { this->curr_turn_speed[0] = -Camera::turn_speed; }
        void stop_turn_left() { this->curr_turn_speed[0] = 0.0f; }

        //Zoom
        void zoom_forward() { this->curr_zoom_speed = Camera::zoom_speed; }
        void stop_zoom_forward() { this->curr_zoom_speed = 0.0f; }
        void zoom_backward() { this->curr_zoom_speed = -Camera::zoom_speed; }
        void stop_zoom_fbackward() { this->curr_zoom_speed = 0.0f; }

        Mat44r get_transf_matrix() const;
        bool outside_fov( const Sphere & ) const;
        bool sees( Triangle & ) const;
        LineSegment visible_part( const LineSegment & ) const;

        void update();
        
        //SETTER
        void set_image_width( unsigned int ) ;
        void set_image_height( unsigned int ) ;

        // GETTER 
        Vec4r get_curr_pos() const;
        Quatr get_curr_orient() const;
        float get_curr_viewer_dist() const;

        std::string get_curr_viewer_dist_to_string() const;
        std::string get_curr_orient_to_string() const;
        std::string get_curr_pos_to_string() const;

        std::string frnear_to_string() const;

    private:
        unsigned int image_width;
        unsigned int image_height;

        // Vec4r accelerates calculations.
        Vec4r curr_pos;
        Quatr curr_orient;
        float curr_viewer_dist;
        Vec4r curr_move_speed { 0.0f, 0.0f, 0.0f, 0.0f };
        Vec4r curr_turn_speed { 0.0f, 0.0f, 0.0f, 0.0f };
        float curr_zoom_speed { 0.0f };
        
        // TODO:
        Frustum fov;
};
#include "../src/camera.tpp"
#endif // _CAMERA_H_
