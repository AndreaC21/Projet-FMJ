// by Andréa Carpentier 
// using Tiago De Lima template
// Tests libgeometry functionalities.

#include <array>
#include <vector>
#include <iostream>
#include "unit_test.hpp"
#include "../include/libgeometry.hpp"
#include "../include/libmatrix.hpp"

using namespace libmatrix;
using namespace libgeometry;

using uint = unsigned int;

int test_conjugate()
{
    Quaternion<float> q (4,1,2,3);
    Quaternion<float> q2 (4,-1,-2,-3);
    TestVector test_conjugate
    {
        { "q.conjugate() = q2", q.conjugate()==q2 },
    };
    return run_tests( "Quaternion.conjugate()=)Quaternion", test_conjugate );
}

int test_norm()
{
    Quaternion<float> q (4,1,2,3);
    int n = 30;
    TestVector test_norm
    {
        { "q.norm() = 30", q.norm()==n, }
    };
    return run_tests( "Quaternion.norm()", test_norm );
}
int test_re_im()
{
    Quaternion<float> q (4,1,2,3);
    float r = 4;
    Vector<float,3> im {1,2,3};
    TestVector test_re_im
    {
        { "q.re()", q.re()==r, },
        { "q.im()", q.im()==im, }
    };
    return run_tests( "q.re() - q.im()", test_re_im );
}
int test_inverse()
{
    Quaternion<float> q (4,1,2,3);
    Quaternion<float> q2 (0.1333333,-0.03333333,-0.066667,-0.1000000);

    TestVector test_inverse
    {
        { "q.inverse()", q.inverse()==q2, }
    };
    return run_tests( "q.inverse()", test_inverse );
}

int main()
{
    int nb_test = 4;
    int failures { 0 };

    failures += test_conjugate();
    failures += test_norm();
    failures += test_re_im();
    failures += test_inverse();
    
   
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
