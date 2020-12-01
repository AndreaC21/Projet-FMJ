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
    
    
    Quaternion deg_to_quat( const T & x, const T & y, const T & z);
    Matrix<T, 4, 4> rotation_matrix( const Quaternion<T> & );
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


}
#include "../src/libgeometry.tpp"
#endif