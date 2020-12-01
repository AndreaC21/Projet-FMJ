using namespace libgeometry;

#pragma region Quaternion

template<typename T>
Quaternion<T>::Quaternion()
{
  sequence = new T[4];
  for ( int i =0 ; i < 4 ; ++i)
  {
    sequence[i] = 0;
  }
}
template<typename T>
Quaternion<T>::Quaternion( const T& w, const T& x, const T &y, const T& z)
{
    sequence = new T[4];
    sequence[0] = w;
    sequence[1] = x;
    sequence[2] = y;
    sequence[3] = z;
}
template<typename T>
Quaternion<T>::Quaternion( const T & w, const Vector<T,3> & v)
{
    sequence = new T[4];
    sequence[0] = w;
    sequence[1] = v.at(0);
    sequence[2] = v.at(1);
    sequence[3] = v.at(2);
}
template<typename T>
Quaternion<T>::Quaternion( const Quaternion& q)
{
    sequence = new T[4];
    sequence[0] = q[0];
    sequence[1] = q[1];
    sequence[2] = q[2];
    sequence[3] = q[3];
}
template<typename T>
Quaternion<T>::~Quaternion()
{
    delete [] sequence;
}
template<typename T>
T& Quaternion<T>::operator[]( size_t i )
{
    return sequence[i];
}

template<typename T>
T Quaternion<T>::operator[]( size_t i ) const
{
    return sequence[i];
}
template<typename T>
Quaternion<T> Quaternion<T>::conjugate() const
{
    return Quaternion(sequence[0],-sequence[1],-sequence[2],-sequence[3]);
}
template<typename T>
float Quaternion<T>::norm() const
{
    float result = 0;
    for (int i=0 ; i<4 ; ++i)
    {
        result+= pow(sequence[i], 2 );
    }
    return result;
}
// return |Q|
template<typename T>
T Quaternion<T>::squared_norm() const
{
    return sqrt(norm());
}
template<typename T>
std::string Quaternion<T>::to_string() const
{
    std::string s("\n");
    for (int i=0 ; i<4 ; ++i)
    {
        s+= std::to_string(sequence[i])+" ";
    }
    return s;
}
template<typename T>
Vector<T,3> Quaternion<T>::im() const
{
    return Vector<T,3>{sequence[1],sequence[2],sequence[3]};
}
template<typename T>
T Quaternion<T>::re()
{
    return sequence[0];
}
template<typename T>
Quaternion<T> Quaternion<T>::inverse() const
{
    // |z|^2 
    Quaternion<T> result;
    float n = norm();
    result[0] = sequence[0] / n;
    for (int i=1 ; i<4 ; ++i)
    {
        result[i] = -sequence[i] / n;
    }
    return result;
}
template<typename T>
Quaternion<T> Quaternion<T>::unit_quat()const
{
    Quaternion result;
    float sn = squared_norm();
    for (int i=0 ; i < 4 ; ++i)
    {
        result[i] = this[0][i] / sn;
    }
    return result;
}
template<typename T>
bool Quaternion<T>::operator==( const Quaternion& q ) const
{
    for (int i=0; i<4 ; ++i)
    {
        if (this[0][i] != q[i]) return false;
    }
    return true;
}
template<typename T>
bool Quaternion<T>::operator!=( const Quaternion& q ) const
{
    return !(*this==q);
}
template<typename T>
Quaternion<T> Quaternion<T>::operator+( const T & scalar)
{
    Quaternion<T> result;
    for (int i=0; i<4 ; ++i)
    {
        result[i] = this[0][i] + scalar;
    }
    return result;
}
template<typename T>
Quaternion<T>& Quaternion<T>::operator+=( const T& scalar )
{
    for (int i=0; i<4 ; ++i)
    {
        this[0][i]+= scalar;
    }
    return *this;
}
template<typename T>
Quaternion<T>& Quaternion<T>::operator+=( const Quaternion& q )
{
    for (int i=0; i<4 ; ++i)
    {
        this[0][i]+= q[i];
    }
    return *this;
}
template<typename T>
Quaternion<T> Quaternion<T>::operator*(const T& scalar )
{
    Quaternion<T> result;
    for (int i=0; i<4 ; ++i)
    {
        result[i] = this[0][i] * scalar;
    }
    return result;
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion& q)
{
    Quaternion<T> result;
    Quaternion<T> copie(*this);
    
    result[0] = copie[0]*q[0] - copie[1] * q[1] - copie[2] * q[2] - copie[3] * q[3];
    result[1] = copie[0]*q[1] + copie[1] * q[0] + copie[2] * q[3] - copie[3] * q[2];
    result[2] = copie[0]*q[2] - copie[1] * q[3] + copie[2] * q[0] + copie[3] * q[1];
    result[3] = copie[0]*q[3] + copie[1] * q[2] - copie[2] * q[1] + copie[3] * q[0];

    return result;
}
template<typename T>
Quaternion<T>& Quaternion<T>::operator*=( const T&  scalar)
{
    this[0][0] *= scalar;
    this[0][1] *= scalar;
    this[0][2] *= scalar;
    this[0][3] *= scalar;
    return *this;
}
template<typename T>
Quaternion<T>& Quaternion<T>::operator*=( const Quaternion& q )
{
    //(w1w2−x1x2−y1y2−z1z2)+ (w1x2+x1w2+y1z2−z1y2)i+ (w1y2−x1z2+y1w2+z1x2)j+ (w1z2+x1y2−y1x2+z1w2)k
    Quaternion<T> copie(*this);
    
    this[0][0] = copie[0]*q[0] - copie[1] * q[1] - copie[2] * q[2] - copie[3] * q[3];
    this[0][1] = copie[0]*q[1] + copie[1] * q[0] + copie[2] * q[3] - copie[3] * q[2];
    this[0][2] = copie[0]*q[2] - copie[1] * q[3] + copie[2] * q[0] + copie[3] * q[1];
    this[0][3] = copie[0]*q[3] + copie[1] * q[2] - copie[2] * q[1] + copie[3] * q[0];

    return *this;
}
# pragma endregion