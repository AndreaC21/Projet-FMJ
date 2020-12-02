#ifndef LIBGEOMETRY_HPP
#define LIBGEOMETRY_HPP

#include <iostream>
#include <cmath>
#include <type_traits>
#include <stdlib.h> // absolute
#include <cstring> // memcpy

using namespace std;
using namespace libmatrix;

namespace libgeometry {

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
    T re();
    Quaternion inverse() const;
    std::string to_string() const;
    Quaternion unit_quat()const;
    Matrix<T, 3, 3> rotation_matrix();
    Quaternion deg_to_quat( const T & x, const T & y, const T & z);
    T& operator[]( size_t i );
    T operator[]( size_t i ) const;
    bool operator==( const Quaternion & ) const;
    bool operator!=( const Quaternion & ) const;
    Quaternion operator+( const T & );
    Quaternion & operator+=( const T & );
    Quaternion & operator+=( const Quaternion& );
    Quaternion operator*(const T & );
    Quaternion operator*(const Quaternion& );
    Quaternion & operator*=( const T& );
    Quaternion & operator*=( const Quaternion& );
    /*Quaternion operator-() const;
    
    //Quaternion<T> operator+( const Quaternion<T> &, const Quaternion<T> & );
    
    */

   friend Quaternion operator*( const T& scalar, Quaternion& q )
   {
        return q*scalar;
   }
   friend Quaternion operator+( const T& scalar ,Quaternion& q )
   {
        return q+scalar;
   }
   friend std::ostream &operator<<(std::ostream &os, const Quaternion& q) 
   {
        os << q.to_string() << std::endl;
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
     Point(const Vector<T,N>&);
     Point(const Point&);
     ~Point();

     //bool is_behind( const Plane & ) const;
     //Direction length_to( const Point & ) const;
     //bool is_outside( const Shere & ) const;
     T x() const;
     T y() const;
     T z() const;
     T w() const;
     T at(int i) const;
     T& operator[] ( int i);
     Point operator +( const Point&);
     Point operator-(const Point&);
     Point operator-() const;
     Point& operator +=( const Point&);
     bool operator==( const Point<T, N> & ) const;
     bool operator!=( const Point<T, N> & ) const;

     friend std::ostream &operator<<(std::ostream &os, const Point& p) 
     {
          os << p.w() << " "  << p.x() << " " << p.y() << " " << p.z() << " " << std::endl;
          return os;
     }
     //Direction<T, N> operator-( const Point<T, N> &);
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
     Quaternion<T> operator*( const Quaternion<T> & q);
     bool operator==( const Direction<T, N> & ) const;
     bool operator!=( const Direction<T, N> & ) const;
     /*friend Point<T, N> operator+( const Point<T, N> & p, const Direction<T, N> & d)
     {

     }
     friend Quaternion<T> operator*( const Quaternion<T> & q, const Direction<T, 4> & d)
     {

     }
     friend std::ostream &operator<<(std::ostream &os, const Direction& p) 
     {
          os << p.w() << " "  << p.x() << " " << p.y() << " " << p.z() << " " << std::endl;
          return os;
     }*/
};
class LineSegment
{
     LineSegment( const Point<float, 4> & , const Direction<float, 4> & );
     LineSegment( const Point<float, 4> &, const Point<float, 4> & );

     //returns the starting point of the segment.
     Point<float, 4> begin() const;
     Point<float, 4> end() const;
     Direction<float, 4> dir() const;
     //float inter_coef( const Plane &) const;
    // Point<float, 4> inter( const Plane & ) const;

     friend std::ostream &operator<<( std::ostream & os, const LineSegment & ls)
     {
          os << std::endl;
          return os;
     }
};

}
#include "../src/libgeometry.tpp"
#endif