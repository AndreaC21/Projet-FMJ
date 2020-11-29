//#include <iostream>
#include "../include/libmatrix.hpp"
#include <vector>

using namespace libmatrix;
using namespace std;

int main()
{
    
    //Mat33r m;

    std::vector<Vec3r> v
    {
        { 0, 0, 1 },
        { 0.5f, 0.5f, 0.5f },
        { 0.5f * static_cast<float>( sqrt(2.0f) ), 0.5f * static_cast<float>( -sqrt(2.0f) ), 1.0f }
    };

    v[0][1] = 3;

   /* TestVector test_vec
    {
        {"v[0][1] == 3", v[0][1] == 3},
        {"v[1][2] == 7", v[1][2] == 7},
        {"v[2][0] == 8", v[2][0] == 8},
    };
    */
/*
 Vec3i v;
 Vec3i u;
 
 u[0] = 1; u[1] = 0; u[2] = 0;
 v[0] = 0; v[1] = 1; v[2] = 0;

std::cout << "\nu= "<< u << "v= "<< v << std::endl;
std::cout << "u.is_ortho(v)=" << std::boolalpha <<u.is_ortho(v) << std::endl;

u[0] = 4; u[1] = 2; u[2] = 3;
v[0] = 1; v[1] = 1; v[2] = 0;

std::cout << "\nu= "<< u << "v= "<< v << std::endl;
std::cout << "u.is_ortho(v)=" << std::boolalpha <<u.is_ortho(v) << std::endl;

u[0] = 1; u[1] = 0; u[2] = 0;
v[0] = 1; v[1] = 5; v[2] = 0;
std::cout << "\nu= "<< u << "v= "<< v<< std::endl;
std::cout << "u.norm() ="<<u.norm() << " u.is_unit()=" << std::boolalpha <<u.is_unit() << std::endl;
std::cout << "v.norm() ="<<v.norm() << " v.is_unit()=" << std::boolalpha <<v.is_unit() << std::endl;
v.to_unit();
std::cout << "v.to_unit() "<< "v= "<< v<< std::endl;


u[0] = 1; u[1] = 2; u[2] = 3;
v[0] = 4; v[1] = 5; v[2] = 6;
std::cout << "\nu= "<< u << "v= "<< v << std::endl;
u+=v;
std::cout << "u+=v -> u=" << u<< std::endl;
u-=v;
std::cout << "u-=v -> u=" << u << std::endl;
u=-u;
std::cout << "u=-u -> u=" << u << std::endl;
u=u+v;
std::cout << "u=u+v-> u=" << u << std::endl;
u=u*2;
std::cout << "u=u*2-> u=" << u << std::endl;
u=-2*u;
std::cout << "u=-2*u-> u=" << u << std::endl;

std::cout << "Probleme : destructor call twice " << std::endl;

std::cout << u << std::endl;


// MATRIX

Mat33r m = Mat33r({{2,3,8},{6,0,-3},{-1,3,2}});
Mat33r r {
    {(float)1/15,(float)2/15,(float)-1/15},
    {(float)-1/15,(float)4/45,(float)2/5},
    {(float)2/15,(float)-1/15,(float)-2/15}
    };

std::cout <<"m.inverse()==r: " <<boolalpha << (m.inverse() ==r)<< std::endl;
std::cout <<"r:\n" <<r << std::endl;

std::cout << "m inverse :\n"<<m.inverse() << std::endl;

std::cout << "m transpose :\n"<<m.transpose() << std::endl;


Mat33r m2 = Mat33r({{0,0,1},{1,0,0},{0,1,0}});
//Mat33r m2 = Mat33r({{5,1,2},{1,5,-2},{2,-2,2}});
std::cout <<"m:\n" <<m2 << std::endl;
std::cout << "m inverse :\n"<<m2.inverse() << std::endl;
std::cout << "m transpose :\n"<<m2.transpose() << std::endl;
std::cout <<"m.is_ortho() ::" <<m2.is_ortho() << std::endl;

Matrix<int,2,2> m3 = *new Matrix<int,2,2>({{1,2},{3,4}});
Matrix<int,2,2> m4 = *new Matrix<int,2,2>({{5,6},{7,8}});
std::cout <<"m3:\n" <<m3 << "m4:\n" << m4 << std::endl;
std::cout <<"m3*m4\n" <<m3*m4<< std::endl;

Mat33r m5 = Mat33r({{1,3,4},{1,0,2},{1,2,1}});
Mat33r m6 = Mat33r({{0,0,0,},{7,5,1},{2,1,3}});
std::cout <<"m5:\n" <<m5 << "m6:\n" << m6 << std::endl;
std::cout <<"m5+m6\n" <<m5+m6<< std::endl;
std::cout <<"m5+=m6"<< std::endl;
m5+=m6;
std::cout <<"m5:\n" <<m5 <<endl;

Mat33i m7 {{1,-1,2},{0,-3,1},{1,-2,4}};
Vec3i v1{2,1,-1};
Vec3i v2{-1,-4,-4};
std::cout <<"m7:\n" <<m7 << std::endl;
std::cout <<"v1:\n" <<v1<< std::endl;
std::cout <<"m7*v1\n" <<m7*v1<< std::endl;

std::cout <<"m5:\n" <<m5<< std::endl;
std::cout <<"m5*2\n" <<m5*2<< std::endl;
std::cout <<"2*m5\n" <<2*m5<< std::endl;

*/
cout << "finished" << endl;
return 0;
}