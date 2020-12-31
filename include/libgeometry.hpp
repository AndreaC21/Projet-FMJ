#ifndef LIBGEOMETRY_HPP
#define LIBGEOMETRY_HPP

#include <iostream>
#include <cmath>
#include <type_traits>
#include <stdlib.h> // absolute
#include <cstring> // memcpy
#include "../include/libmatrix.hpp"

using namespace std;
using namespace libmatrix;

namespace libgeometry {

class Plane;
template <typename T, int N>
class Direction;
class Sphere;
class XYBBox;

//w,x,y,z
template<typename T>
class Quaternion
{
    private :
      T* sequence;
    public:

    Quaternion();
    Quaternion( const T& w , const T& x, const T& y, const T& z );
    Quaternion( const T& x, const Vector<T,3>& v );
    Quaternion( const Quaternion& q);
    ~Quaternion();
    Quaternion conjugate() const;
    float norm() const; 
    T squared_norm() const;
    Vector<T,3> im() const;
    T re() const;
    Quaternion inverse() const;
    std::string to_string() const;
    Quaternion unit_quat()const;
    Matrix<T, 4, 4> rotation_matrix();
    Quaternion deg_to_quat( const T & x, const T & y, const T & z); //TO-DO
    T& operator[]( size_t i );
    T operator[]( size_t i ) const;
    bool operator==( const Quaternion & ) const;
    bool operator!=( const Quaternion & ) const;
    Quaternion operator+( const T & );
    Quaternion & operator+=( const T & );
    Quaternion & operator+=( const Quaternion& );
    Quaternion operator*(const T & );
    Quaternion operator*(const Quaternion& );
    Quaternion operator*(const Vector<T,4>& v);
    Quaternion & operator*=( const T& );
    Quaternion & operator*=( const Quaternion& );
    void operator=( const Quaternion& q ) const;
    
    Quaternion operator-() const; 

   friend Quaternion operator*( const T& scalar, Quaternion& q )
   {
        return q*scalar;
   }
   friend Quaternion operator*( const Vector<T,4>& v, Quaternion& q )
   {
        return q*v;
   }
   friend Quaternion operator+( const T& scalar ,Quaternion& q )
   {
        return q+scalar;
   }
   friend std::ostream &operator<<(std::ostream &os, const Quaternion& q) 
   {
        os << q.re()<< " " << q.im() << std::endl;
        return os;
   }
   friend std::istream operator>>( std::istream &is , const Quaternion<T> & )
   {
        float w,x,y,z;
        is >> w >> x >> y >> z;
        return is;
   }

};

//<w,x,y,z>
template <typename T, int N>
class Point
{
     private:
          T* sequence;
     public:
     Point();
     Point(const float&, const float&, const float&, const float&);
     Point(const float&, const float&, const float&);
     Point(const Vector<T,N>&);
     template <int M>
     Point<T,N>(const Point<T,M>& p);
     Point(const Point&);
     ~Point();

     bool is_behind( const Plane & );
     Direction<T,N> length_to( const Point & ) const;
     bool is_outside( const Sphere& ) const;
     T x() const;
     T y() const;
     T z() const;
     T w() const;
     T at(int i) const;
     T& operator[] ( int i);
     Point operator +( const Point&);
     //Point operator-(const Point&);
     Point operator-() const;
     Point operator*( const float& scalar);
     float operator*(const Vec3r& v);
     Point& operator +=( const Point&);
     bool operator==( const Point<T, N> & ) const;
     bool operator!=( const Point<T, N> & ) const;
     void operator=(const Point& v);

     friend Direction<T, N> operator-( const Point<T, N> &a, const Point<T, N> &b )
     {
          Direction<T,N> result;
          for ( int i =0 ; i < N ; ++i)
          {
               result[i] = b.at(i) - a.at(i);
          }
          return result;
     }
     
     friend Point<T, N> operator-( const Direction<T, N> &a, const Point<T, N> &b )
     {
          Point<T,N> result;
          for ( int i =0 ; i < N ; ++i)
          {
               result[i] = a.at(i) - b.at(i);
          }
          return result;
     }
     friend std::ostream &operator<<(std::ostream &os, const Point& p) 
     {
          os << p.w() << " "  << p.x() << " " << p.y() << " " << p.z() << " " << std::endl;
          return os;
     }
     
     std::string informations() const
     {
          return to_string(this->x())+" "+to_string(this->y())+" "+to_string(this->z())+"\n";
     }
     
};

template <typename T, int N>
class Direction
{
     private:
          T* sequence;
     public:
     Direction();
     Direction(const Vector<T,N>&);
     Direction(const Direction&);
     ~Direction();

     T x() const;
     T y() const;
     T z() const;
     T w() const;
     T at(int i) const;
     T& operator[] ( int i);

     Point<T, N> operator+( const Point<T, N> &);
     Quaternion<T> operator*( const Quaternion<T> & q); // TO DO
     float operator*(const Direction& d);
     Direction operator-(const Direction& d);
     bool operator==( const Direction<T, N> & ) const;
     bool operator!=( const Direction<T, N> & ) const;
     friend Point<T, N> operator+( const Point<T, N> & p, const Direction<T, N> & d)
     {
          Point<T,N> result;
          for ( int i =0 ; i < N ; ++i)
          {
               result[i] = p.at(i) + d.at(i);
          }
          return result;
     }
     /*
     TO DO
     friend Quaternion<T> operator*( const Quaternion<T> & q, const Direction<T, 4> & d)
     {

     }
     */
     friend std::ostream &operator<<(std::ostream &os, const Direction& p) 
     {
          os << p.w() << " "  << p.x() << " " << p.y() << " " << p.z() << " " << std::endl;
          return os;
     }
};

class LineSegment
{
     private:
          Point<float,4> d,e;
          Direction<float,4> direction;
     public:
     LineSegment( const Point<float, 4> & , const Direction<float, 4> & );
     LineSegment( const Point<float, 4> &, const Point<float, 4> & );
     LineSegment(const LineSegment& ls);
     ~LineSegment();

     //returns the starting point of the segment.
     Point<float, 4> begin() const;

     //returns the ending point of the segment.
     Point<float, 4> end() const;

     Vec2r begin_to_xy() const;
     Vec2r end_to_xy() const;
     //returns the direction of the segment.
     Direction<float, 4> dir() const;
     float inter_coef( const Plane &) const;
     Point<float, 4> inter( const Plane & ) const;

     friend std::ostream &operator<<( std::ostream & os, const LineSegment & ls)
     {
          os << ls.begin() <<"\n" << ls.end() << endl;
          return os;
     }
};

class Plane
{
     private:
          Point<float,4> point;
     public:

     Plane();
     Plane(const Point<float,4>&, float);
     Point<float,4> originPoint()const;
     ~Plane();

     float d() const;
     Vec3r perpendicularVector() const;
     friend std::ostream &operator<<( std::ostream & os, const Plane & p)
     {
          os << std::endl;
          return os;
     }
};

class Sphere
{
     private:
          Point<float,4> center;
          float radius;
     public:

     Sphere(const Point<float,4>& , float); // center,radius
     ~Sphere();
     Point<float,4> getCenter() const;
     float getRadius() const;
     bool is_behind( const Plane & ) const; // TO COMPLETE

     friend std::ostream &operator<<( std::ostream & os, const Sphere & s)
     {
          os << s.getCenter() << s.getRadius() << std::endl;
          return os;
     }
};

class Rectangle
{
     private:
          Point<float,4>* sequence;
     public:

     Rectangle();
     Rectangle( const Point<float, 4>& , const Point<float, 4> &,const Point<float, 4> &, const Point<float, 4> & );
     Rectangle( const Rectangle& );
     ~Rectangle();
     Point<float,4> at(int i) const;
     friend std::ostream &operator<<( std::ostream & os, const Rectangle& r)
     {
          os << std::endl;
          os << r.at(0) << r.at(1) << r.at(2)<< r.at(3) ;
          return os;
     }
};

class Triangle
{
     private:
         Point<float,4> *sequence;
     public:
     Triangle( const Point<float, 4> &, const Point<float, 4> &, const Point<float, 4> & );
     Triangle(const Triangle& t);
     ~Triangle();
     float cote( Point<float,4> a, Point<float,4>) const ;
     float area() const; // returns the area of the triangle.
     float area(const Point<float, 4> &v0,const Point<float, 4> &v1,const Point<float, 4> &v2) const;
     Point<float, 4> bary( const Point<float, 4> & ) const;
     Point<float, 4> center() const;
     Direction<float, 4> normal() const; //normal vector
     Point<float, 4> p0() const;
     Point<float, 4> p1() const;
     Point<float, 4> p2() const;

     LineSegment c0_1() const;
     LineSegment c1_2() const;
     LineSegment c0_2() const;

     std::string informations() const
     {
          return this->p0().informations()+this->p1().informations()+this->p2().informations();
     }

     XYBBox xybbox() const;

     friend std::ostream &operator<<( std::ostream & os, Triangle & t)
     {
          os << std::endl;
          os << t.p0() << t.p1() << t.p2();
          return os;
     }
};

//Implements a 2D bounding box. That is, a 2D rectangle laying on the x-y plane.
class XYBBox
{
     private:
          Point<float,4>* sequence;
     public:
     //constructs a XYBBox such that the upper left and lower right corners are the points given as arguments.
     XYBBox( const Point<float,4> &, const Point<float,4> & );
     ~XYBBox();
     float xmax() const; //returns the maximum x coordinate.
     float ymax() const; //returns the maximum y coordinate.
     float xmin() const; //returns the minimum x coordinate.
     float ymin() const; //returns the minimum y coordinate.

     friend std::ostream &operator<<( std::ostream & os, const XYBBox & b)
     {
          os << std::endl;
          os << "(" << b.xmin() << ","<< b.ymax() << ") (" << b.xmax() << "," << b.ymin() << ")" << endl;
          return os;
     }
};


using Quatr = Quaternion<float>;
using Point4r = Point<float,4>;
using Point3r = Point<float,3>;
using Point2r = Point<float,2>;
const Point4r Point4rZero = Point4r(0.0f,0.0f,0.0f,0.0f);
const Point3r Point3rZero = Point3r(0.0f,0.0f,0.0f);

using real=float;
const real pi { 3.14159265 };

Quaternion<real> deg_to_quat( const float& x, const float& y, const float& z)
{
     Vec3r r{ x * pi / 180.0f /2, y * pi / 180.0f /2,z * pi / 180.0f /2};

     Vec4r a_x{1,1,1,1};
     Vec4r a_y{1,1,1,1};
     Vec4r a_z{1,1,1,1};

     if ( r[0]!=0.0f) {a_x = {cosf(r[0]), sinf(r[0]),sinf(r[0]),  cosf(r[0]) }; }
     if ( r[1]!=0.0f) {a_y = {cosf(r[1]), sinf(r[1]),sinf(r[1]),  cosf(r[1]) }; }
     if ( r[2]!=0.0f) {a_z = {cosf(r[2]), sinf(r[2]),sinf(r[2]),  cosf(r[2]) }; }

     Vec4r s;
     s[0] = cosf(r[0]) * cosf(r[1]) *cosf(r[2]); // w
     if ( !almost_equals(x,0.0f)){ s[1] = a_x.at(1) * a_y.at(1)* a_z.at(1) ;/* x */}
     if ( !almost_equals(y,0.0f)) s[2] = a_x.at(2) * a_y.at(2)* a_z.at(2); // y
     if ( !almost_equals(z,0.0f)) s[3] = a_x.at(3) * a_y.at(3)* a_z.at(3);  // z

     Quaternion<real> result(s.at(0),{s.at(1),s.at(2),s.at(3)});

     return result;
}


}
#include "../src/libgeometry.tpp"
#endif