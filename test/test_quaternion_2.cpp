// test_quaternion_2.cpp
//
// This file is part of the 3D Scene Viewer
// by Tiago de Lima <tiago.delima@univ-artois.fr>
// on 21 Dec 2020
//
// Tests the rotations with quaternions.

#include <iostream>
#include <cmath>

//#include "libmatrix.h"
//#include "libgeometry.h"

#include "../include/libgeometry.hpp"
#include "../include/libmatrix.hpp"

using namespace libmatrix;
using namespace libgeometry;

using real = float;
using Point4r = Point<real, 4ul>;

// Uncomment if you need it.
//const real pi { 3.14159265 };

Mat44r transf_matrix( Vec4r rot )
{
    // Camera orientation in radians (360 degrees = (2 * pi) radians).
    Vec4r a
    {
        rot[0] * pi / 180.0f,
        rot[1] * pi / 180.0f,
        rot[2] * pi / 180.0f,
        0.0f
    };
            
    // Camera transformation matrices.
    Mat44r t1
    { 
        { 1.0f,      0.0f,       0.0f, 0.0f },
        { 0.0f, cos(a[0]), -sin(a[0]), 0.0f },
        { 0.0f, sin(a[0]),  cos(a[0]), 0.0f },
        { 0.0f,      0.0f,       0.0f, 1.0f }
    };

    Mat44r t2
    {
        {  cos(a[1]), 0.0f,  sin(a[1]), 0.0f },
        {       0.0f, 1.0f,       0.0f, 0.0f },
        { -sin(a[1]), 0.0f,  cos(a[1]), 0.0f },
        {       0.0f, 0.0f,       0.0f, 1.0f }
    };

    Mat44r t3
    {
        { cos(a[2]), -sin(a[2]), 0.0f, 0.0f },
        { sin(a[2]),  cos(a[2]), 0.0f, 0.0f },
        {      0.0f,       0.0f, 1.0f, 0.0f },
        {      0.0f,       0.0f, 0.0f, 1.0f }
    };       

    //std::cout << t1 << "\n";
    //std::cout << t2 << "\n";
    //std::cout << t3 << "\n";
    // Calculates final transformation matrix.
    return t1 * (t2 * t3);
}

Vec4r quat_to_point( const Quatr & q )
{
    return { q.im()[0], q.im()[1], q.im()[2], q.re() };
}

int main()
{
/*
Expected output below.
Note that, e.g., -4.3e-8 is "almost" zero.
Therefore, the results are "almost" equivalent.

Test 1:
-------
current position = ( 1, 0, 0, 1 )
rotation = ( 90, 0, 0, 0 )
new position (using matrix)     = ( 1, 0, 0, 1 )
new position (using quaternion) = ( 1, 0, 0, 1 )

Test 2:
-------
current position = ( 1, 0, 0, 1 )
rotation = ( 0, 90, 0, 0 )
new position (using matrix)     = ( -4.37114e-08, 0, -1, 1 )
new position (using quaternion) = ( 0, 0, -1, 1 )

Test 3:
-------
current position = ( 1, 0, 0, 1 )
rotation = ( 0, 0, 90, 0 )
new_position (using matrix)    = ( -4.37114e-08, 1, 0, 1 )
new position (with quaternion) = ( 0, 1, 0, 1 )

Test 4:
-------
current position = ( 1, 0, 0, 1 )
rotation = ( 0, 45, 45, 0 )
new_position (using matrix)    = ( 0.5, 0.707107, -0.5, 1 )
new position (with quaternion) = ( 0.5, 0.707107, -0.5, 1 )
*/ 

    std::cout << "\nTest 1:\n";
    std::cout << "-------\n";

    Vec4r curr_pos { 1.0f, 0.0f, 0.0f, 1.0f };
    Vec4r rotation { 90.0f, 0.0f, 0.0f, 0.0f };

    // Rotation using matrix.
    Mat44r rot_matrix { transf_matrix( rotation ) };
    Vec4r new_pos { rot_matrix * curr_pos };

    // Rotation using quaternion.
    Quatr rotation_quat = deg_to_quat( rotation.at( 0 ), rotation.at( 1 ), rotation.at( 2 ) );
    Quatr q = rotation_quat * curr_pos * rotation_quat.inverse();

    // Comment out if you want to verify the matrix generated from the quaternion.
    //Mat44r rot_matrix_quat = rotation_matrix( rotation_quat );
    //cout << rot_matrix_quat << endl;
    //Vec4r new_pos = rot_matrix_quat * curr_pos;
    //Quatr q = rotation_quat * curr_pos;
    //q = q * rotation_quat.inverse();

    std::cout << "current position = " << curr_pos << std::endl;
    std::cout << "rotation = " << rotation << std::endl;
    std::cout << "new position (using matrix)     = " << new_pos << std::endl;
    std::cout << "new position (using quaternion) = " << quat_to_point( q ) << std::endl;

    std::cout << "\nTest 2:\n";
    std::cout << "-------\n";

    rotation = { 0.0f, 90.0f, 0.0f, 0.0f };

    // Rotation using matrix.
    rot_matrix = transf_matrix( rotation );
    new_pos = rot_matrix * curr_pos;

    // Rotation using quaternion.
    rotation_quat = deg_to_quat( rotation.at( 0 ), rotation.at( 1 ), rotation.at( 2 ) );
    q = rotation_quat * curr_pos * rotation_quat.inverse();

    std::cout << "current position = " << curr_pos << std::endl;
    std::cout << "rotation = " << rotation << std::endl;
    std::cout << "new position (using matrix)     = " << new_pos << std::endl;
    std::cout << "new position (using quaternion) = " << quat_to_point( q ) << std::endl;

    std::cout << "\nTest 3:\n";
    std::cout << "-------\n";

    rotation = { 0.0f, 0.0f, 90.0f, 0.0f };

    // Rotation using matrix.
    rot_matrix = transf_matrix( rotation );
    new_pos = rot_matrix * curr_pos;

    // Rotation with quaternion
    rotation_quat = deg_to_quat( rotation.at( 0 ), rotation.at( 1 ), rotation.at( 2 ) );
    q = rotation_quat * curr_pos * rotation_quat.inverse();

    std::cout << "current position = " << curr_pos << std::endl;
    std::cout << "rotation = " << rotation << std::endl;
    std::cout << "new position (using matrix)    = " << new_pos << std::endl;
    std::cout << "new position (with quaternion) = " << quat_to_point( q ) << std::endl;

    std::cout << "\nTest 4:\n";
    std::cout << "-------\n";

    rotation = { 0.0f, 45.0f, 45.0f, 0.0f };

    // Rotation using matrix.
    rot_matrix = transf_matrix( rotation );
    new_pos = rot_matrix * curr_pos;

    // Rotation with quaternion
    rotation_quat = deg_to_quat( rotation.at( 0 ), rotation.at( 1 ), rotation.at( 2 ) );
    q = rotation_quat * curr_pos * rotation_quat.inverse();

    std::cout << "current position = " << curr_pos << std::endl;
    std::cout << "rotation = " << rotation << std::endl;
    std::cout << "new position (using matrix)    = " << new_pos << std::endl;
    std::cout << "new position (with quaternion) = " << quat_to_point( q ) << std::endl;

    return 0;
}
