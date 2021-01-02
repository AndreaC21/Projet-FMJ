#ifndef _FRUSTUM_H_
#define _FRUSTUM_H_

#include "../include/libgeometry.hpp"
#include "../include/libmatrix.hpp"

using namespace libmatrix;
using namespace libgeometry;

class Frustum
{
    private:
        Plane near;
        Plane far;
        Plane right;
        Plane left;
        Plane top;
        Plane bottom;
    public:
        //Returns if the point given as argument is outside the field of vision.
        bool outside( const Point<float, 4> & ) const;

        // Returns if the sphere given as argument is completely outside the field of vision.
        bool outside( const Sphere & ) const;
        
        // Returns the intersection between the segment and the field of vision (visible part).
        LineSegment inter( const LineSegment & ) const;

        //Updates the position of the field of vision, where h is the horizontal resolution, v is the vertical resolution 
        //and e is the distance between the projection plane and the camera.
        void update( float h, float v, float e );

        // 0->near,1->far,2->right,3->left,4->top,5->bottom
        Plane getPlane(int) const;

};

#include "../src/frustum.tpp"
#endif