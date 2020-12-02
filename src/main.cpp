//#include <iostream>
#include "../include/libmatrix.hpp"
#include "../include/libgeometry.hpp"
#include <vector>

using namespace libmatrix;
using namespace libgeometry;
using namespace std;

int main()
{
    /*
    Quaternion<float> q (4,1,2,3);
    cout << q << endl;
    cout << q[0] << endl;
    cout << q.conjugate() << endl;
    cout << q.norm() << endl;
    cout << "re: " << q.re() << " im: " << q.im()<< endl;
    cout << q.inverse() << endl;

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

   Point<float,4> p(Vec4r{1,4,5,2});
   Point<float,4> p2(Vec4r{0,1,-3,2});
   cout << p << p2 << endl;
   cout << "-p : "<< -p << endl;
   cout << "p!=p2 : " << std::boolalpha << (p!=p2) << endl;
    p+= p2;
    cout << "p+=p2 " << p << endl;
cout << "finished" << endl;
return 0;
}