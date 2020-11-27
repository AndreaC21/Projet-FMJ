//#include "../include/libmatrix.hpp"
#include <iostream>

using namespace libmatrix;

#pragma region ClassVector

template<typename T,int N>
Vector<T,N>::Vector()
{
  //cout << "default constructor "<< endl;
  size = N;
  sequence = new T[size];

}
template<typename T,int N>
Vector<T,N>::Vector(std::initializer_list<T> l)
{
  size = N;
  sequence = new T[N];
  int i =0;
  for (auto elt : l)
  {
    sequence[i] = elt;
    i++;
  }
  //cout << "Vector constructor finish with list size " << l.size() << endl;
     
}
template<typename T,int N>
Vector<T,N>::~Vector()
{
  //std::cout << "destructor" << std::endl;
  //delete [] sequence;
}
template<typename T,int N>
T Vector<T,N>::at(int i) const
{
  try
   {
      if (i >= N ) throw std::string("invalid size ");
      else return sequence[i];
   }
   catch(std::string const& chaine)
   {
       std::cerr << chaine << std::endl;
   }
   return N;

}
template<typename T,int N>
Vector<T,N> Vector<T,N>::cross(Vector v)
{
  //u×v=〈u2v3−u3v2,u3v1−u1v3,u1v2−u2v1〉
  /*The cross product of a = (2,3,4) and b = (5,6,7)

    cx = aybz − azby = 3×7 − 4×6 = −3
    cy = azbx − axbz = 4×5 − 2×7 = 6
    cz = axby − aybx = 2×6 − 3×5 = −3
Answer: a × b = (−3,6,−3) 
*/
  Vector<T,N> result;
  try
   {
      if (N<3 ) throw std::string("not enought element ");
      else
      {
        result[0] = this->at(1)*v.at(2) - this->at(2)*v.at(1);
        result[1] = this->at(2)*v.at(0) - this->at(0)*v.at(2);
        result[2] = this->at(0)*v.at(1) - this->at(1)*v.at(0);

        return result;
      }
   }
   catch(std::string const& chaine)
   {
       std::cerr << chaine << std::endl;
   }
   return result;
}
template<typename T,int N>
bool Vector<T,N>::is_ortho(Vector v)
{
  /*
  dot product Ux*Vx + Uy*Vy + Uz*Vz
  if equal 0 = orthogonal
  */
  return (this->at(0)*v.at(0) + this->at(1)*v.at(1) +this->at(2)*v.at(2))==0;

}
template<typename T,int N>
bool Vector<T,N>::is_null()
{
  for ( int i =0; i<N ; ++i)
  {
    if ( isnan(this->at(i))) return true;
  }
  return false;
}
// trhow si c'est un int,char,unsigned int
// tester si il est float,deouble, long double
template<typename T,int N>
float Vector<T,N>::norm()
{
  //magnitude ou norm == racine(x²+y²+z²)
  return sqrt( pow( this->at(0), 2 ) + pow( this->at(1), 2 ) + pow(this->at(2),2)  );
}
template<typename T,int N>
bool Vector<T,N>::is_unit()
{
  // if magnitude == 1, vector is is_unit
  return norm()==1 ;
}

template<typename T,int N>
Vector<T,N> Vector<T,N>::to_unit()
{
  Vector<T,N> result;
  int magnitude = norm();

  result[0] = result.at(0) / magnitude;
  result[1] = result.at(1) / magnitude;
  result[2] = result.at(2) / magnitude;

  return result;
}

template<typename T,int N>
T& Vector<T,N>::operator[](int i)
{
  return sequence[i];
}
template<typename T,int N>
Vector<T,N> Vector<T,N>::operator+(const Vector v)
{
  Vector<T,N> result;
  for (int i=0 ; i<N ; ++i)
  {
    result[i] = this->at(i) + v.at(i);
  }
  return result;
}
template<typename T,int N>
Vector<T,N> Vector<T,N>::operator-(const Vector v)
{
  Vector<T,N> result;
  for (int i=0; i<N ; ++i)
  {
    result[i] = this->at(i) - v.at(i);
  }
  return result;
}
template<typename T,int N>
Vector<T,N> Vector<T,N>::operator-()
{
  Vector<T,N> result;
  for (int i=0; i<N ; ++i)
  {
    result.sequence[i] = - this->at(i);
  }
  return result;
}
template<typename T,int N>
Vector<T,N>& Vector<T,N>::operator+=(const Vector v)
{
  for (int i=0 ; i<N ; ++i)
  {
    this->sequence[i] = this->at(i) + v.at(i);
  }
  return *this;
}
template<typename T,int N>
Vector<T,N>& Vector<T,N>::operator-=(const Vector v)
{
  for (int i=0; i<N ; ++i)
  {
    this->sequence[i] = this->at(i) - v.at(i);
  }
  return *this;
}
template<typename T,int N>
void Vector<T,N>::operator=(const Vector v)
{
  for (int i=0; i<N ; ++i)
  {
    this->sequence[i] = v.at(i);
  }
}

template<typename T,int N>
Vector<T,N> Vector<T,N>::operator*(const float scalar)
{
  Vector<T,N> result;
  for (int i=0; i<N ; ++i)
  {
    result[i] = this->at(i) * scalar;
  }
  return result;
}
template<typename T,int N>
float Vector<T,N>::operator *(const Vector v)
{
  float result = 0;
  for (int i=0; i<N ; ++i)
  {
    result+=this->at(i) * v.at(i);
  }
  return result;
}
template<typename T,int N>
bool Vector<T,N>::operator==(const Vector& v)
{
  for (int i=0; i<N ; ++i)
  {
    if ( this->at(i) != v.at(i)) 
    {
      //cout << this->at(i)<< v.at(i)<< endl;
      return false;
    }
  }
  return true;
}

#pragma endregion


#pragma region ClassMatrix

template<typename T,int N,int M>
Matrix<T,N,M>::Matrix()
{
  /* Allocation dynamique */
  sequence = new T*[N];
  for (int i=0; i < N; ++i)
  {
    sequence[i] = new T[M];
  }
    
  //sequence = new T[N][M];
}
template<typename T,int N,int M>
Matrix<T,N,M>::Matrix(const Matrix& m)
{
  
  sequence = new T*[N];
  for (int i=0; i < N; ++i)
  {
    sequence[i] = new T[M];
    for (int j=0; j < M; ++j)
    {
      sequence[i][j] = m.at(i,j);
    }
  }
  //cout << "constructor par copie : fin" << endl;
}
template<typename T,int N,int M>
Matrix<T,N,M>::Matrix(std::initializer_list<std::initializer_list<T>> l)
{
  sequence = new T*[N];
  
  for (int i=0; i < N; ++i)
  {
    sequence[i] = new T[M];
  }
  int i=0;
  int j=0;
  for (auto row : l)
  {
    //cout << i << endl;
    for (auto elt : row)
    {
      sequence[i][j] = elt;
      j++;
    }
    i++;
    j = 0;
  }
  //cout << "Matrix constructor finish with list size " << l.size() << endl;
}
template<typename T,int N,int M>
Matrix<T,N,M>::~Matrix()
{
  for ( int i=0 ; i< M ; ++i)
  {
    //delete [] sequence[i];
  }
  delete [] sequence;
}
template<typename T,int N,int M>
T Matrix<T,N,M>::at(int i, int j) const
{
  try
   {
      if (i >= N ) throw std::string("invalid size i");
      if (j >= M ) throw std::string("invalid size j");
      else return sequence[i][j];
   }
   catch(std::string const& chaine)
   {
       std::cerr << chaine << std::endl;
   }
   return N;
}

template<typename T,int N,int M>
Matrix<T,N,M> Matrix<T,N,M>::inverse()
{
  Matrix<T,N,M> idMat= Identity33r;
  Matrix<T,N,M> copie(*this);
  //else if (N==4) idMat = Identity44r;
for( int i=0; i< M; ++i)
{
  // Trouver le plus grand 
  T max = 0;
  int j = 0;

  // cherche max absolute value
  for (int h = 0; h < M; ++h)
  {
    if (abs(copie.at(h,i)) > max) 
    {
      max = copie.at(h,i);
      j = h;
    }
  }
  // on echange i et j
  T* tempo = new T[M];
  memcpy(tempo,copie[i], sizeof(T) * M );
  memcpy(copie[i],copie[j], sizeof(T) * M );
  memcpy(copie[j],tempo, sizeof(T) * M );
  
  memcpy(tempo,idMat[i], sizeof(T) * M );
  memcpy(idMat[i],idMat[j], sizeof(T) * M );
  memcpy(idMat[j],tempo, sizeof(T) * M );

  float multi = 1 / max;

  //cout << "Apres echange " << endl;
  //cout << *this << endl;

  // mutiplie par 1/M'
  for ( int h = 0 ; h < N ; ++h)
  {
    //cout << *this[i][h] << endl;
    copie[i][h] = copie.at(i,h) * multi;
    idMat[i][h] = idMat.at(i,h) * multi;
  }
   //cout << "Apres multiplication de 1/M" << endl;
   //cout << *this << endl;
   //cout << "0,2: " <<this->at(0,2) << endl;


   // pour toutes les lignes ( r) !=  i
   // r = r + ri*(this(i,j))
  for ( int r = 0 ; r < N ; ++r)
  {
    //cout << this->at(i,r) << endl;
    if (r!=i)
    {
      
      T val = - copie.at(r,i);
      for ( int h= 0 ; h < N ; ++h)
      {
        tempo[h] = copie.at(i,h) * val;
      }
      for ( int h= 0 ; h < N ; ++h)
      {   
        copie[r][h] = copie.at(r,h) + tempo[h];
      }
      // meme calcul mais avec la matrice identite
      for ( int h= 0 ; h < N ; ++h)
      {
        tempo[h] = idMat.at(i,h) * val;
      }
      for ( int h= 0 ; h < N ; ++h)
      {   
        idMat[r][h] = idMat.at(r,h) + tempo[h];
      } 
    }
  }
}
return idMat;
}
template<typename T,int N,int M>
Matrix<T,N,M> Matrix<T,N,M>::transpose()
{
  Matrix<T,N,M> result;
  
  for ( int i=0 ; i < N ; ++i)
  {
    for ( int j=0 ; j < M ; ++j)
    {
     result[j][i] = this->at(i,j);
    }
  }

  return result;
}
template<typename T,int N,int M>
bool Matrix<T,N,M>::is_ortho()
{
  return transpose()==inverse();
  //return((transpose() * *this )== Identity33r);
}
template<typename T,int N,int M>
bool Matrix<T,N,M>::is_null()
{
  for (int i=0; i < N; ++i)
  {
    for (int j=0; j < M; ++j)
    {
      if ( isnan(this->at(i,j))) return true;
    }
  }
  return false;
}
template<typename T,int N,int M>
T* & Matrix<T,N,M>::operator[](int index)  // overloading operator []
{
  return sequence[index];
}
template<typename T,int N,int M>
bool Matrix<T,N,M>::operator ==(const Matrix m)
{
  for (int i=0; i < N; ++i)
  {
    for (int j=0; j < M; ++j)
    {
      if ( this->at(i,j)!=m.at(i,j)) return false;
    }
  }
  return true;
}
template<typename T,int N,int M>
Matrix<T,N,M> Matrix<T,N,M>::operator*(const Matrix& m)
{
  Matrix<T,N,M> result;
  for (int i=0; i < N; ++i)
  {
    for (int j=0; j < M; ++j)
    {
      T value = 0;
      for (int h=0; h < M; ++h)
      {
        value += this->at(i,h) * m.at(h,j);
      }
      result[i][j] = value;
    }
  }
  return result;
}
template<typename T,int N,int M>
Vector<T,N> Matrix<T,N,M>::operator *(const Vector<T,M>& m)
{
  Vector<T,N> result;
  for (int i=0; i < N; ++i)
  {
    T value = 0;
    for (int j=0; j < M; ++j)
    {
      value += this->at(i,j) * m.at(j);
    }
    result[i] = value;
  }
  return result;
}
template<typename T,int N,int M>
Matrix<T,N,M> Matrix<T,N,M>::operator *(const float scalar)
{
  Matrix<T,N,M> result;
  for (int i=0; i < N; ++i)
  {
    for (int j=0; j < M; ++j)
    {
      result[i][j] = this->at(i,j) * scalar;
    }
  }
  return result;
}

template<typename T,int N,int M>
Matrix<T,N,M> Matrix<T,N,M>::operator+(const Matrix& m)
{
  Matrix<T,N,M> result;
  for (int i=0; i < N; ++i)
  {
    for (int j=0; j < M; ++j)
    {
      result[i][j] = this->at(i,j) + m.at(i,j);
    }
  }
  return result;
}
template<typename T,int N,int M>
Matrix<T,N,M> Matrix<T,N,M>::operator+=(const Matrix& m)
{
  for (int i=0; i < N; ++i)
  {
    for (int j=0; j < M; ++j)
    {
      this[0][i][j] = this->at(i,j) + m.at(i,j);
    }
  }
  return *this;
}
#pragma endregion
/*
int main()
{

 Vec3i u = Vec3i({1,3,4});
 Vec3i v;
 v[0] = 2; v[1] = 7; v[2] = -5;

 Vec3i r = u.cross(v);
 std::cout << r.at(0) << std::endl;

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

Mat33r m({{2,3,8},{6,0,-3},{-1,3,2}});


m[0][0]= 1;
m[0][1] = 5;
m[0][2] = 9;

std::cout <<"m:\n" <<m << std::endl;

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

Matrix<int,2,3> m7 = *new Matrix<int,2,3>({{1,-1,2},{0,-3,1}});
Vec3i v1({2,1,0});
std::cout <<"m7:\n" <<m7 << std::endl;
std::cout <<"v1:\n" <<v1<< std::endl;
std::cout <<"m7*v1\n" <<m7*v1<< std::endl;

std::cout <<"m5:\n" <<m5<< std::endl;
std::cout <<"m5*2\n" <<m5*2<< std::endl;
std::cout <<"2*m5\n" <<2*m5<< std::endl;


Vec4r a { 1.0f, 3.5f, 1.2f, 4.4f };
Vec4r b { 2.0f, 7.0f, 2.4f, 8.8f };

float x =1.0f;
float y =2.0f;

cout <<"dot( a, x ) " << dot( a, x )<< endl;
cout << "dot( a, y )"<<dot( y, a ) <<endl;
cout << "dot( a, b )"<<dot( b, a ) <<endl;
Vec4r a1 { 0, 1, 2, 3 };
Vec4r a2{ 3, 4, 5, 6 };
cout << "cross( v0, v1)= "<< cross( a1, a2 ) << endl;
cout << "finished" << endl;
return 0;
}
*/
//bool isofloatingpoint  type_track