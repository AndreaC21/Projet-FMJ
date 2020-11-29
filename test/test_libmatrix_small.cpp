// by Tiago de Lima <tiago.delima@univ-artois.fr>
//
// Tests libmatrix functionalities.

#include <array>
#include <vector>
#include <iostream>
#include "unit_test.hpp"
#include "../include/libmatrix.hpp"

using namespace libmatrix;

using uint = unsigned int;

int test_at()
{
    Mat33i a;
    Mat44i b;
    TestVector test_vec
    {
        { "a.at( 0, 0 ) == 0", a.at( 0, 0 ) == 0 },
        { "b.at( 0, 0 ) == 0", b.at( 0, 0 ) == 0 },
    };

    return run_tests( "at()", test_vec );
}
int test_is_null()
{
    Vec2i a;
    Vec3i b;
    Vec2r g { NAN , 0 };

    Mat33r j
    {
        { 0, 1, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };
    

    TestVector test_vec
    {
        { "a.is_null()", a.is_null() == false },
        { "b.is_null()", b.is_null() == false },
        { "g.is_null()", g.is_null() == true },
        { "j.is_null()", j.is_null() == false },
    };

    return run_tests( "is_null()", test_vec );
}

int test_is_unit()
{
    std::vector<Vec3r> t
    {
        { 0, 0, 1 },
        { 0, 1, 0 },
        { 1, 0, 0 },
        { 0.5f * static_cast<float>( sqrt(2.0f) ), 0.5f * static_cast<float>( sqrt(2.0f) ), 0 },
    };

    TestVector test_vec;
    for( size_t i { 0 }; i < t.size(); ++i )
    {
        test_vec.push_back( { "t[" + std::to_string(i) + "].is_unit()", t[i].is_unit() == true } );
    }

    return run_tests( "is_unit()", test_vec );
}

int test_norm()
{
    std::vector<Vec3r> v
    {
        { 0, 1, 2 },
        { 1, 2, 3 },
      };
    TestVector test_vec
    {
        {"v[0].norm() == sqrt( 5.0f )", almost_equals( v[0].norm(), sqrt( 5.0f ) ) },
        {"v[1].norm() == sqrt( 14.0f )", almost_equals( v[1].norm(), sqrt( 14.0f ) ) },
      };

    return run_tests( "norm()", test_vec );
}

int test_operator_sub()
{
    std::vector<Vec3r> v
    {
        { 0, 0, 1 },
        { 0.5f, 0.5f, 0.5f },
        { 0.5f * static_cast<float>( sqrt(2.0f) ), 0.5f * static_cast<float>( -sqrt(2.0f) ), 1.0f }
    };

    v[0][1] = 3;
    v[1][2] = 7;
    v[2][0] = 8;

    TestVector test_vec
    {
        {"v[0][1] == 3", v[0][1] == 3},
        {"v[1][2] == 7", v[1][2] == 7},
        {"v[2][0] == 8", v[2][0] == 8},
    };

    return run_tests( "operator[]", test_vec);
}

int test_operator_putout()
{
    std::cout << "Testing <<..." << std::endl;

    std::vector<Vec3r> v
    {
        { 0, 0, 1 },
        { 0.5f, 0.5f, 0.5f },
        { 0.5f * static_cast<float>( sqrt(2.0f) ), 0.5f * static_cast<float>( -sqrt(2.0f) ), 1.0f }
    };
    std::cout <<
        v[0] << std::endl <<
        v[1] << std::endl <<
        v[2] << std::endl;
    Vec4r a { 1.0f, 3.5f, 1.2f, 4.4f };
    Vec4r b { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4r c { 0.0f, 1.5f, -1.8f, 0.4f };
    std::cout <<
        a << std::endl <<
        b << std::endl <<
        c << std::endl;
    Mat33r m
    {
        { 0, 0, 1 },
        { 0.5f, 0.5f, 0.5f },
        { 0.5f * static_cast<float>( sqrt(2.0f) ), 0.5f * static_cast<float>( -sqrt(2.0f) ), 1.0f }
    };
    std::cout << m << std::endl;

    std::cout << std::endl;

    return 0;
}

int test_operator_plus()
{
    std::vector<Vec3r> v
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.1f, 0.0f, 0.1f },
        { 0.2f, 0.0f, 0.2f },
    };
    Mat33r m1
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f }
    };
    Mat33r m2
    {
        { 3.0f, 0.0f, 1.0f },
        { 3.1f, 0.0f, 1.1f },
        { 0.5f, 0.5f, 0.5f }
    };
    Mat33r m3
    {
        { 3.0f, 0.0f, 1.0f },
        { 3.1f, 0.0f, 1.1f },
        { 0.5f, 0.5f, 0.5f }
    };
    TestVector test_vec
    {
        { "v[0] + v[1] == v[1]", v[0] + v[1] == v[1] },
        { "v[0] + v[2] == v[2]", v[0] + v[2] == v[2] },
        { "v[1] + v[1] == v[2]", v[1] + v[1] == v[2] },
        { "m1 + m2 == m3", m1 + m2 == m3 }
    };

    return run_tests( "operator+( Vector )", test_vec );
}

int test_operator_pluseq()
{
    std::vector<Vec3r> v
    {
        { 0.1f, 0.0f, 0.1f },
        { 0.0f, 0.1f, 0.0f },
        { 0.2f, 0.0f, 0.2f },
    };
    v[0] += v[0];
    v[1] += v[0];
    TestVector test_vec
    {
        { "v[0] == v[2]", v[0] == v[2] },
    };

    return run_tests( "operator+=( Vector )", test_vec );
}

int test_operator_minus1()
{
    std::vector<Vec3r> v
    {
        { 1, 2, 3 },
        { -1, -2, -3 },
    };
    TestVector test_vec
    {
        { "-v[0] == v[1]", -v[0] == v[1] },
        { "-v[1] == v[0]", -v[1] == v[0] },
    };

    return run_tests( "operator-()", test_vec );
}
int test_operator_minus2()
{
    Vec4r a { 1.0f, 3.5f, 1.2f, 4.4f };
    Vec4r b { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4r c { 0.0f, 1.5f, -1.8f, 0.4f };
    TestVector test_vec
    {
        { "a - b == c", a - b == c }
    };

    return run_tests( "operator-( Vector )", test_vec );
}

int test_dot1()
{
    Vec4r a { 1.0f, 3.5f, 1.2f, 4.4f };
    Vec4r b { 2.0f, 7.0f, 2.4f, 8.8f };
   
    float x=1.0f;
    float y=2.0f;
    TestVector test_vec
    {
        { "dot( a, x ) == a", dot( a, x ) == a },
        { "dot( a, y ) == b", dot( a, y ) == b },
    };
    TestVector test_vec2
    {
        { "dot( x, a ) == a", dot( x, a ) == a },
        { "dot( y, a ) == b", dot( y, a ) == b },
        
    };

    return run_tests( "dot( Vector, scalar )", test_vec ) +
           run_tests( "dot( scalar, Vector )", test_vec2 );
           
}

int test_dot2()
{
    Vec4r a { 1.0f, 3.0f, 1.0f, 4.0f };
    Vec4r b { 2.0f, 7.0f, 2.4f, 8.8f };
    float x = 60.6f;
    TestVector test_vec
    {
        { "dot( a, b ) == x", dot( a, b ) == x },
    };

    return run_tests( "dot( Vector, Vector )", test_vec );
 }

int test_cross()
{
	Vec4r v0 { 0, 1, 2, 3 };
	Vec4r v1 { 3, 4, 5, 6 };
	Vec4r v2 { 5 - 8, 6 - 0, 0 - 3, 0 };
    TestVector test_vec
    {
        { "cross( v0, v1 ) == v2", cross( v0, v1 ) == v2 },
    };

    return run_tests( "cross( Vector, Vector )", test_vec );
}

int test_operator_mult()
{
    Mat33r m1
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f }
    };
    Mat33r m2
    {
        { 3.0f, 0.0f, 1.0f },
        { 3.1f, 0.0f, 1.1f },
        { 0.5f, 0.5f, 0.5f }
    };
    Mat33r m3
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f }
    };
    TestVector test_vec
    {
        { "m1 * m2 == m3", m1 * m2 == m3 }
    };

    return run_tests( "operator*( Matrix )", test_vec );
}
int main()
{
    int nb_test = 14;
    int failures { 0 };

    failures += test_at();
    
    failures += test_operator_sub();
    failures += test_is_null();
    failures += test_is_unit();
    failures += test_norm();
    failures += test_operator_plus();
    failures += test_operator_pluseq();
    failures += test_operator_minus1();
    failures += test_operator_minus2();
    failures += test_dot1();
    failures += test_dot2();
    failures += test_cross();
    failures += test_operator_mult();
    
    failures += test_operator_putout();
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
