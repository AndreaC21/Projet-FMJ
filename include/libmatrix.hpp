#ifndef LIBMATRIX_HPP
#define LIBMATRIX_HPP

#include <iostream>
#include <cmath>
#include <type_traits>
#include <stdlib.h> // absolute
#include <cstring> // memcpy

using namespace std;

namespace libmatrix {
//class Matrix;
template<typename T,int N>
class Vector {
  private :
      int size;
      T* sequence;
  public:
        Vector();
        Vector(std::initializer_list<T> l);
        ~Vector();

        T at(int i) const ;
        Vector cross(Vector v);
        bool is_ortho(Vector v);
        bool is_null();
        bool is_unit();
        float norm();
        Vector to_unit(); // to modify with isfloatingpoint

        T& operator[] (int i); //permettre de mofifier la valeur
        Vector operator+(const Vector v);
        Vector operator-(const Vector v);
        Vector operator-(); // inverse
        Vector operator *(const float scalar);
        float operator *(const Vector v);
        
        Vector& operator+= (const Vector v);
        Vector& operator-= (const Vector v);
        
        void operator=(const Vector v);

        bool operator==(const Vector& v);

        //TODO
        //Vector operator *(const Matrix m);
        //friend Vector operator *(const Matrix& m,const Vector& v,);
        
       friend Vector operator*(const float scalar,const Vector &v)
        {
               // return v*scalar;
               Vector<T,N> result;
                for (int i=0; i<N ; ++i)
                {
                        result[i] = v.at(i) * scalar;
                }
                return result;
        }

        friend std::ostream &operator<<(std::ostream &os, const Vector &v) 
        {
                for (int i=0; i < N; ++i)
                {
                        os << v.at(i) << " ";
                }
                os << std::endl;
                return os;
        }
   

};
/*a b c
d e f
g h i
det(M) = (a*e*i) + (b*f*g) + (c*d*h) - (c*e*g) - (b*d*i) - (a*f*h)
https://codereview.stackexchange.com/questions/149669/c-operator-overloading-for-matrix-operations-follow-up
*/
template<typename T,int N,int M>
class Matrix {
      private :
      int n,m;
      T** sequence;
  public:
        Matrix();
        Matrix(const Matrix& m);
        Matrix(std::initializer_list<std::initializer_list<T>> l);
        ~Matrix();

        T at(int i,int j) const ;
        Matrix inverse();
        Matrix transpose();
        bool is_ortho();
        bool is_null();

        //dot et cross

        T* &operator[](int index); //permettre de modifier la valeur
        Matrix operator +(const Matrix& m);
        Matrix operator +=(const Matrix& m);
        Vector<T,N> operator *(const Vector<T,M>& v);
        Matrix operator *(const Matrix& m);
        Matrix operator *(const float scalar);
        
        bool operator ==(const Matrix m);
        
        //Matrix& operator*= ();
        //void operator=(const Matrix m);

        friend std::ostream &operator<<(std::ostream &os, const Matrix &m) 
        {
                for (int i=0; i < N; ++i)
                {
                        for (int j=0; j < M; ++j)
                        {
                                os << m.at(i,j) << " ";
                        }
                        os << std::endl;
                }
                os << std::endl;
                return os;
        }
        friend Matrix operator *(const float scalar, Matrix m)
        {
                return m*scalar;
        }
        friend Vector<T,N> operator *(const Vector<T,M>& v, Matrix m)
        {
                return m*v;
        }
};
bool almost_equals( float a, float b)
{
        return a==b;
}
template<typename T,int N>
float dot(Vector<T,N> v,Vector<T,N> u)
{
        return u*v;
}
template<typename T,int N>
Vector<T,N> dot(Vector<T,N> v, float scalar)
{
        return v*scalar;
}
template<typename T,int N>
Vector<T,N> dot(float scalar,Vector<T,N> v)
{
        return scalar*v;
}
template<typename T,int N>
Vector<T,N> cross(Vector<T,N> u,Vector<T,N> v)
{
        return u.cross(v);
}
// alias for operator *. The two operands are given as arguments. The operands may be scalars,
//vectors and matrices.
// cross(): alias pour method cross. The two operands are given as arguments.

using Vec2i = Vector<int,2>;
using Vec3i = Vector<int,3>;
using Vec4i = Vector<int,4>;
using Vec2r = Vector<double,2>;
using Vec3r = Vector<double,3>;
using Vec4r = Vector<double,4>;

using Mat33r = Matrix<float,3,3>;
using Mat44r = Matrix<float,4,4>;
using Mat33i = Matrix<int,3,3>;
using Mat44i = Matrix<int,4,4>;

// Vector zero
const Vec2i vect2izero = Vec2i({0,0});
const Vec3i vect3izero = Vec3i({0,0,0});
const Vec4i vect4izero = Vec4i({0,0,0,0});
const Vec2r vect2rzero = Vec2r({0.0,0.0});
const Vec3r vect3rzero = Vec3r({0.0,0.0,0.0});
const Vec4r vect4rzero = Vec4r({0,0,0,0});


// IdentityMat: 
const Mat33r Identity33r = Mat33r({{1,0,0},{0,1,0},{0,0,1}});
const Mat44r Identity44r = Mat44r({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}});
}

#include "../src/libmatrix.tpp"
#endif
