//#include <iostream>
#include "../include/libmatrix.hpp"
#include "../include/libgeometry.hpp"
#include <vector>

using namespace libmatrix;
using namespace libgeometry;
using namespace std;

int main()
{
    
    Quaternion<float> q (4,1,2,3);
    cout << q << endl;
    cout << q[0] << endl;
    cout << q.conjugate() << endl;
    cout << q.norm() << endl;
    cout << "re: " << q.re() << " im: " << q.im()<< endl;
    cout << q.inverse() << endl;

    /*
    Quaternion<float> q1 (4,1,2,3);
    Quaternion<float> q2 (4,9,2,-3);
    cout << q1 << "\n" << q2 << endl;
    cout << "q==q1 " << boolalpha << (q==q1) << endl;
    cout << "q==q2 " << boolalpha << (q==q2) << endl;
    cout << "q1!=q2 " << boolalpha << (q1!=q2) << endl;

    Quaternion<float> q3 (4,1,2,3);
    Quaternion<float> q4 (4,1,2,3);
    cout << "q3 " <<q3 << endl;
    cout << "q3+2 " << q3+2 << endl;
    cout << "2+q3 " << 2+q3 << endl;
    q3+=2;
    cout << "q3+=2 " << q3 << endl;
    cout << "q3*2 " << q3*2 << endl;
    cout << "2*q3 " << 2*q3 << endl;
    cout << "q3*q4 " << q3*q4 << endl;
    cout << "\nq3*=q4 " << (q3*=q4) << endl;
    cout << "q3*=2 " << (q3*=2) << endl;

    cout << "q3.unit_quad() " << (q3.unit_quat()) << endl;

    Quaternion<float> q5(1,4,5,3);
    cout << q5 << endl;
    cout << q5.rotation_matrix() << endl;

    */

   //Point<float,4> p(Vec4r{1,4,5,2});
   //Point<float,4> p2(Vec4r{0,1,-3,2});
   /*cout << p << p2 << endl;
   cout << "-p : "<< -p << endl;
   cout << "p!=p2 : " << std::boolalpha << (p!=p2) << endl;
    p+= p2;
    cout << "p+=p2 " << p << endl;*/

    Point<float,4> a(Vec4r{1,4,5,2});
    Point<float,4> b(Vec4r{0,1,-3,2});
    Point<float,4> c(Vec4r{0,5,1,-1});
    Point<float,4> d(Vec4r{1,8,3,4});

    Rectangle r{a,b,c,d};
    cout << "r:" << r << endl;
    Triangle t{a,b,c};
    cout << "t:" << t <<endl;
    cout << "t.area(): " << t.area() << endl;
    Point<float,4> e(Vec4r{0,1,1,0});
    Point<float,4> f(Vec4r{0,2,3,0});
    Point<float,4> g(Vec4r{0,3,1,0});
    Point<float,4> p(Vec4r{0,2,2,0});
    Triangle t2{e,f,g};
    cout << "t2:" << t2 <<endl;
    cout << "t2.xybbox()" << t2.xybbox() <<endl;
    cout << "t2.bary({0,2,2,0}): " << t2.bary(p) <<endl;
    Point<float,4> v0(Vec4r{0,0,0,0});
    Point<float,4> v1(Vec4r{0,0,-1,0});
    Point<float,4> v2(Vec4r{0,1,0,0});
    Triangle t3{v0,v1,v2};
    cout << "t3:" << t3 <<endl;
    cout << "t3.normal() : " << t3.normal() <<endl;
    /*
    Sphere s(a,2);
    cout << "s:\n" << s << endl;
    cout << "b.is_outside(s): " << std::boolalpha <<b.is_outside(s) << endl;
    cout << "a.is_outside(s): " << std::boolalpha <<a.is_outside(s) << endl;
    Plane p(a,2);
    cout << p << endl;
    cout << "b.is_behind(p): " << std::boolalpha << b.is_behind(p) << endl;
    LineSegment ls(a,b);
    cout << "ls.inter_coef(p): " << ls.inter_coef(p)<< endl;
    cout << "ls.inter(p): " << ls.inter(p)<< endl;
    */


cout << "finished" << endl;
return 0;
}