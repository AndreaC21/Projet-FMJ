// by Andréa Carpentier 
// using Tiago De Lima template
// Tests libmatrix functionalities.

#include <array>
#include <vector>
#include <iostream>
#include "unit_test.hpp"
#include "../include/libmatrix.hpp"

using namespace libmatrix;

using uint = unsigned int;

int test_is_ortho_Vector()
{
   Vec3i u {1,0,0};
   Vec3i v {0,1,0};
   Vec3i w {4,2,3};

    TestVector test_vec
    {
        { "u.is_ortho(v)=", u.is_ortho(v)== true},
        { "u.is_ortho(w)=", u.is_ortho(w)== false},
    };

    return run_tests( "Vector.is_ortho()", test_vec );
}
int test_inverse()
{

Mat33r m {{2,3,8},{6,0,-3},{-1,3,2}};
Mat33r r {
    {(float)1/15,(float)2/15,(float)-1/15},
    {(float)-1/15,(float)4/45,(float)2/5},
    {(float)2/15,(float)-1/15,(float)-2/15}
    };
TestVector test_vec
    {
        { "m.inverse()==r", m.inverse()== r},
    };

    return run_tests( "Matrix.inverse()", test_vec );
}
int test_transpose()
{

Mat33r m {{2,3,8},{6,0,-3},{-1,3,2}};
Mat33r r {{2,6,-1},{3,0,3},{8,-3,2}};
TestVector test_vec
    {
        { "m.transpose()==r", m.transpose()== r},
    };

    return run_tests( "Matrix.transpose()", test_vec );
}
int test_is_ortho_Matrix()
{
    Mat33r m {{0,0,1},{1,0,0},{0,1,0}};
    Mat33r m2 {{5,1,2},{1,5,-2},{2,-2,2}};
    TestVector test_vec
    {
        { "m.is_ortho()==true", m.is_ortho()== true},
        { "m2.is_ortho()==false", m2.is_ortho()== false},
    };

    return run_tests( "Matrix.is_ortho()", test_vec );
}

int test_operator_mult_Matrix()
{
    Mat33i m {{1,-1,2},{0,-3,1},{1,-2,4}};
    Vec3i v1{2,1,-1};
    Vec3i v2{-1,-4,-4};

    TestVector test_vec
    {
        { "m*v1==v2", m*v1== v2},
    };

    return run_tests( "Matrix*Vector", test_vec );

}

int main()
{
    int nb_test = 5;
    int failures { 0 };

    failures += test_is_ortho_Vector();
    failures += test_inverse();
    failures += test_transpose();
    failures += test_is_ortho_Matrix();
    failures += test_operator_mult_Matrix();
    
    if( failures > 0 )
    {
        std::cout << "Total failures : " << failures <<"/"<< nb_test << std::endl;
        std::cout << "TEST FAILED!!" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Success!" << std::endl;
         std::cout << (nb_test-failures) <<"/"<< nb_test << std::endl;
        return 0;
    }
}
