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
        //float f = roundf( (sequence[i]* 1000) / 1000) ;
        s+= std::to_string(this[0][i])+" ";
    }
    return s;
}
template<typename T>
std::string Quaternion<T>::to_string_angle() const
{
    int precision = 1000;

    Quaternion<T> u = this->unit_quat();

    float x( (int) (u.im().at(0) * precision) / precision);
    float y(roundf( (u.im().at(1) * precision) / precision));
    float z(roundf( (u.im().at(2) * precision) / precision));
    cout << x << endl;
    return std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(z)+"";
   
}
template<typename T>
Vector<T,3> Quaternion<T>::im() const
{
    return Vector<T,3>{sequence[1],sequence[2],sequence[3]};
}
template<typename T>
T Quaternion<T>::re() const
{
    return sequence[0];
}
template<typename T>
Quaternion<T> Quaternion<T>::inverse() const
{
    // |z|^2 
    Quaternion<T> result;
    float n = norm();
    result[0] = this->re() / n;
    for (int i=0 ; i<3 ; ++i)
    {
        result[i+1] = -this->im()[i] / n;
    }
   // Quaternion<T> r(this->conjugate() * 1/this->norm());
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
Quaternion<T> Quaternion<T>::deg_to_quat( const T & x, const T & y, const T & z)
{
    return deg_to_quat(x,y,x);
    /*if( x > 360 || x < -360 ) x = x%360;
    if( y > 360 || y <-360  ) y = y%360;
    if( z > 360 || z < -360 ) z = z%360; */

/*
    Quaternion<T> result;
    
    // angle est en radian
    float rotX,rotY,rotZ,rotW, angle ;
    rotW = rotX = rotY = rotZ = angle = 0.0f;
    double pi = 2*acos(0.0);
    if ( x != 0.0f ) { angle = x * pi / 180.0f ; rotX = sinf(angle / 2); rotW = cosf(angle / 2); }
    if ( y != 0.0f ) { angle = y * pi / 180.0f ; rotY = sinf(angle / 2); rotW+= cosf(angle / 2); }
    if ( z != 0.0f ) { angle = z * pi / 180.0f ; rotZ = sinf(angle / 2); rotW+= cosf(angle / 2); }

   
    result[0] = rotW;
    result[1] = rotX;
    result[2] = rotY;
    result[3] = rotZ;
    
    return result;
    */
}

// /

template<typename T>
Matrix<T,4,4> Quaternion<T>::rotation_matrix()
{
    Quaternion copie(this->unit_quat());
    Matrix<T,4,4> result;

    result[0][0] =  1 - 2* pow(copie[2],2) - 2*pow(copie[3],2);
    result[0][1] =  2*copie[1]*copie[2] - 2*copie[3]*copie[0];
    result[0][2] =  2*copie[1]*copie[3] + 2*copie[2]*copie[0];
    result[1][0] =  2*copie[1]*copie[2] + 2*copie[3]*copie[0];
    result[1][1] =  1 - 2* pow(copie[1],2) - 2*pow(copie[3],2);
    result[1][2] =  2*copie[1]*copie[3] - 2*copie[2]*copie[0];
    result[2][0] =  2*copie[1]*copie[3] - 2*copie[2]*copie[0];
    result[1][2] =  2*copie[1]*copie[3] + 2*copie[2]*copie[0];
    result[2][2] =  1 - 2* pow(copie[1],2) - 2*pow(copie[2],2);
    
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
void Quaternion<T>::operator=( const Quaternion& q ) const
{
    sequence[0] = q.re();
    sequence[1] = q.im()[0];
    sequence[2] = q.im()[1];
    sequence[3] = q.im()[2];
}

template<typename T>
bool Quaternion<T>::operator!=( const Quaternion& q ) const
{
    return !(*this==q);
}

template<typename T>
Quaternion<T>  Quaternion<T>::operator-() const
{
    Quaternion<T> result;
    result[0] = this->w();
    for (int i=1 ; i<4 ; ++i)
    {
        result[i] = -sequence[i];
    }
    
    return result;
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
Quaternion<T>& Quaternion<T>::operator+=( const Vec4r& )
{

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
Quaternion<T> Quaternion<T>::operator*(const Vector<T,4>& v)
{
    Vec3r u {v.at(0),v.at(1),v.at(2)};
    Vec3r z = cross(this->im(),u);
    Quaternion result(this->re(), z);
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

#pragma region Point
template <typename T, int N>
Point<T,N>::Point()
{
    sequence = new T[N];
    for ( int i=0 ; i<N ; ++i)
    {
        sequence[i] = 0;
    }
}
template <typename T, int N>
Point<T,N>::Point(const Vector<T,N>& v)
{
    sequence = new T[N];
    for ( int i=0 ; i<N ; ++i)
    {
        sequence[i] = v.at(i);
    }
}
template <typename T, int N>
Point<T,N>::Point(const float& w, const float& x, const float& y, const float& z)
{
    //cout << "construct4"<<endl;
    sequence = new T[N];
    sequence[0] = w;
    sequence[1] = x;
    sequence[2] = y;
    sequence[3] = z;
}
template <typename T, int N>
Point<T,N>::Point(const float&x, const float&y, const float&z)
{
   // cout << "construct3"<<endl;
    sequence = new T[4];
    sequence[0] = 0;
    sequence[1] = x;
    sequence[2] = y;
    sequence[3] = z;
}
template <typename T, int N>
Point<T,N>::Point(const Point& p)
{
    //cout << "Constructeur copie Point" << endl;
    sequence = new T[N];
    for ( int i=0 ; i<N ; ++i)
    {
        sequence[i] = p.at(i);
    }
}

template <typename T, int N>
template <int M>
Point<T,N>::Point(const Point<T,M>& p)
{
    sequence = new T[N];
    if ( M < N) // passer de point3 a point4
    {
        if ( M==3)
        {
            sequence[0] = 0; //w
            sequence[1] = p.x();
            sequence[2] = p.y();
            sequence[3] = p.z();
        }
        else if(M==2)
        {
            sequence[0] = 0; //w
            sequence[1] = p.x();
            sequence[2] = p.y();
            sequence[3] = 0;
        }
       
    }
    else if ( M> N)
    {
        sequence[0] = p.x();
        sequence[1] = p.y();
        sequence[2] = p.z();
    }
    //cout << "Constructeur copie Point" << endl;
}
template <typename T, int N>
Point<T,N>::~Point()
{
    //cout << "Destructeur point:" << *this << endl;
    delete [] sequence ;
}
template <typename T, int N>
T Point<T,N>::at(int i) const
{
    return sequence[i];
}
template <typename T, int N>
T Point<T,N>::w() const
{
    return sequence[0];
}
template <typename T, int N>
T Point<T,N>::x() const
{
    return sequence[1];
}
template <typename T, int N>
T Point<T,N>::y() const
{
    return sequence[2];
}
template <typename T, int N>
T Point<T,N>::z() const
{
    return sequence[3];
}
template <typename T, int N>
std::string Point<T,N>::to_string() const
{
    return "x: "+std::to_string(x())+"y: "+std::to_string(y())+"z: "+std::to_string(z())+"w: "+std::to_string(w());
}
template <typename T, int N>
bool Point<T,N>::is_outside( const Sphere& s ) const
{
  //( inside (px-cx)² + (py-cy)² + (pz-cz)² ) < R²
  return !((pow(this->x() - s.getCenter().x(),2) + pow(this->y() - s.getCenter().y(),2) + pow(this->z() - s.getCenter().z(),2) ) < pow(s.getRadius(),2) ) ;
}
template <typename T, int N>
bool Point<T,N>::is_behind( const Plane &p )
{
    float x = *this*p.perpendicularVector() + p.d();
    return x<0;
}
template <typename T, int N>
Direction<T,N>  Point<T,N>::length_to( const Point &p ) const
{
    Direction<T,N> result;
    result[0] = 0;
    result[1] = this->x() - p.x();
    result[2] = this->y() - p.y();
    result[3] = this->z() - p.z();
    return result;
}
template <typename T, int N>
T& Point<T,N>::operator[] ( int i)
{
    return sequence[i];
}
template <typename T, int N>
Point<T,N> Point<T,N>::operator +( const Point& p)
{
    Point<T,N> result;
    for ( int i =0 ; i < N ; ++i)
    {
        result[i] = this->at(i) + p.at(i);
    }
    return result;
}

template <typename T, int N>
Point<T,N> Point<T,N>::operator-() const
{
    Point<T,N> result;
    for ( int i =0 ; i < N ; ++i)
    {
        result[i] =  -this->at(i);
    }
    return result;
}
template <typename T, int N>
float Point<T,N>::operator*(const Vec3r& v)
{
  float result = 0;
  for (int i=0; i<3 ; ++i)
  {
    result+=this->at(i) * v.at(i);
  }
  return result;
}
template <typename T, int N>
Point<T,N>& Point<T,N>::operator +=( const Point&p)
{
    for ( int i =0 ; i < N ; ++i)
    {
        this[0][i] = this->at(i) + p.at(i);
    }
    return *this;
}
template <typename T, int N>
bool Point<T,N>::operator==( const Point & p) const
{
    for ( int i =0 ; i < N ; ++i)
    {
        if ( this->at(i) != p.at(i) ) return false;
    }
    return true;
}
template <typename T, int N>
bool Point<T,N>::operator!=( const Point& p) const
{
    return !(*this==p);
}
template <typename T, int N>
void Point<T,N>::operator=(const Point& p)
{
    for ( int i =0 ; i < N ; ++i)
    {
        this[0][i] = p.at(i) ;
    }
}

#pragma endregion

#pragma region Direction

template <typename T, int N>
Direction<T,N>::Direction()
{
    sequence = new T[N];
    for ( int i=0 ; i<N ; ++i)
    {
        sequence[i] = 0;
    }
}
template <typename T, int N>
Direction<T,N>::Direction(const Vector<T,N>& v)
{
    sequence = new T[N];
    for ( int i=0 ; i<N ; ++i)
    {
        sequence[i] = v.at(i);
    }
}
template <typename T, int N>
Direction<T,N>::Direction(const Direction& p)
{
    //cout << "Constructeur copie Direction" << endl;
    sequence = new T[N];
    for ( int i=0 ; i<N ; ++i)
    {
        sequence[i] = p.at(i);
    }
}
template <typename T, int N>
Direction<T,N>::~Direction()
{
    //cout << "Destructeur Direction: " << *this << endl;
    delete [] sequence ;
}
template <typename T, int N>
T Direction<T,N>::at(int i) const
{
    return sequence[i];
}
template <typename T, int N>
T Direction<T,N>::w() const
{
    return sequence[0];
}
template <typename T, int N>
T Direction<T,N>::x() const
{
    return sequence[1];
}
template <typename T, int N>
T Direction<T,N>::y() const
{
    return sequence[2];
}
template <typename T, int N>
T Direction<T,N>::z() const
{
    return sequence[3];
}
template <typename T, int N>
T& Direction<T,N>::operator[] ( int i)
{
    return sequence[i];
}
template <typename T, int N>
Point<T, N> Direction<T,N>::operator+( const Point<T, N> &)
{ 
 return Point<T,N>();
}
template <typename T, int N>
float Direction<T,N>::operator*(const Direction& d)
{
  float result = 0;
  for (int i=0; i<N ; ++i)
  {
    result+=this->at(i) * d.at(i);
  }
  return result;
}
/*
template <typename T, int N>
Quaternion<T> Direction<T,N>::operator*( const Quaternion<T> & q)
{

}
*/
template <typename T, int N>
bool Direction<T,N>::operator==( const Direction<T, N> & d) const
{
    for  (int i=0 ; i < N ; ++i)
    {
        if (this->at(i) != d.at(i) ) return false;
    }
    return true;
}
template <typename T, int N>
bool Direction<T,N>::operator!=( const Direction<T, N> & d) const
{
    return !(*this==d);
}
#pragma endregion

#pragma region Plane

Plane::Plane()
{
    point = Point<float,4>();
}
Plane::Plane(const Point<float,4>&p, float f)
{
    point = *new Point<float,4>(p);
}
Plane::~Plane()
{
   
}
float Plane::d() const
{
    return point.w();
}
Vec3r Plane::perpendicularVector() const
{
    return Vec3r{point.x(),point.y(),point.z()}.to_unit();
}
Point<float,4> Plane::originPoint() const
{
    return point;
}

std::string Plane::to_string() const
{
    return this->point.to_string();
}
#pragma endregion

#pragma region LineSegment

LineSegment::LineSegment( const Point<float, 4> &a, const Point<float, 4> &b )
{
    d = *new Point<float,4>(a);
    e = *new Point<float,4>(b);
    direction = *new Direction<float,4>(e-d);
}
LineSegment::LineSegment( const Point<float, 4> &a, const Direction<float, 4> &b )
{
    d = *new Point<float,4>(a);
    direction = *new Direction<float,4>(b);
    e = *new Point<float,4>(direction - d);
}
LineSegment::LineSegment(const LineSegment& ls)
{
    d = ls.begin();
    e = ls.end();
    direction = ls.dir();
}
LineSegment::~LineSegment()
{
    //cout << "Destructeur LineSegment" << endl;
}
Point<float, 4> LineSegment::begin() const{ return d;}
Point<float, 4> LineSegment::end() const{  return e;}

Vec2r LineSegment::begin_to_xy() const {return Vec2r {this->begin().x(),this->begin().y()};}
Vec2r LineSegment::end_to_xy() const {return Vec2r {this->end().x(),this->end().y()};}

Direction<float, 4> LineSegment::dir() const
{
    return direction;
}

float LineSegment::inter_coef( const Plane &p) const
{
    return this->begin()*p.perpendicularVector();// + p.d();
}
Point<float, 4> LineSegment::inter( const Plane &p ) const
{
    float coef = inter_coef(p);
    if (coef==0) //parrellele
    {
        return Point<float,4>();
    }
    Point<float, 4> result;
    result[1] = p.originPoint().x() / coef;
    result[2] = p.originPoint().y() / coef;
    result[3] = p.originPoint().z() / coef;
    result[0] = p.originPoint().w() / coef;
    return result;
}
#pragma endregion

#pragma region Sphere

Sphere::Sphere( const Point<float,4>& c, float r) // center,radius
{
    center = *new Point<float,4>(c);
    radius = r;
}

Sphere::~Sphere()
{
    //delete [] center;
}
Point<float,4> Sphere::getCenter() const
{
    return center;
}
float Sphere::getRadius() const
{
    return radius;
}

bool Sphere::is_behind( const Plane &p ) const
{
    // distance origin,point p du plan < rayon
    float distance_centre_origin = sqrt(pow(getCenter().x() - p.originPoint().x(),2) + pow(getCenter().y() - p.originPoint().y(),2) + pow(getCenter().z() - p.originPoint().z(),2));

    //false = pas d'intersection entre la sphere et le plan
    return distance_centre_origin > this->getRadius();
}
#pragma endregion

#pragma region Rectangle

Rectangle::Rectangle()
{
    sequence = new Point<float,4>[4];
}
Rectangle::Rectangle( const Point<float, 4> &a, const Point<float, 4> &b,const Point<float, 4> &c, const Point<float, 4> &d )
{
    sequence = new Point<float,4>[4];

    sequence[0] = *new Point<float,4>(a);
    sequence[1] = *new Point<float,4>(b);
    sequence[2] = *new Point<float,4>(c);
    sequence[3] = *new Point<float,4>(d);

}
Rectangle::Rectangle ( const Rectangle& r)
{
    //cout << "Constructeur copie Rectangle" << endl;
    sequence = new Point<float,4>[4];

    sequence[0] = r.at(0);
    sequence[1] = r.at(1);
    sequence[2] = r.at(2);
    sequence[3] = r.at(3);

}
Rectangle::~Rectangle()
{
    //cout << "Destructeur Rectangle: " << endl;
   
    delete [] sequence;
    //cout << "Destructeur Rectangle Fin" << endl;
}
     
Point<float,4> Rectangle::at(int i) const
{
    return sequence[i];
}
#pragma endregion

#pragma region Triangle
Triangle::Triangle( const Point<float, 4> &a, const Point<float, 4> &b, const Point<float, 4> & c)
{
    sequence = new Point<float,4>[3];

    sequence[0] = *new Point<float,4>(a);
    sequence[1] = *new Point<float,4>(b);
    sequence[2] = *new Point<float,4>(c);
}
Triangle::Triangle(const Triangle& t)
{
    sequence = new Point<float,4>[3];
    sequence[0] = t.p0();
    sequence[1] = t.p1();
    sequence[2] = t.p2();
}
Triangle::~Triangle()
{
    delete[] sequence;
}
Point<float,4> Triangle::p0() const
{
    return sequence[0];
}
Point<float,4> Triangle::p1() const
{
    return sequence[1];
}
Point<float,4> Triangle::p2() const
{
    return sequence[2];
}
LineSegment Triangle::c0_1() const
{
    return LineSegment(p0(),p1());
}
LineSegment Triangle::c1_2() const
{
    return LineSegment(p1(),p2());
}
LineSegment Triangle::c0_2() const
{
    return LineSegment(p0(),p2());
}
float Triangle::cote(Point<float,4> a, Point<float,4> b) const
{
    return sqrt(pow(a.x()-b.x(),2)+pow(a.y()-b.y(),2)+pow(a.z()-b.z(),2));
}
Point<float, 4> Triangle::bary( const Point<float, 4> &p ) const
{
    if (area()==0 ) return Point<float,4>();

    float a_12 = area(p,p1(),p2());
    float a_20 = area(p,p2(),p0());
    float a_01 = area(p,p0(),p1());
    float a = area();

    return Point<float,4>(0,a_12/a,a_20/a,a_01/a);

}
float Triangle::area() const
{
    float a = cote(p0(),p1());
    float b = cote(p1(),p2());
    float c = cote(p2(),p0());

    float p = (a+b+c)/2;

     //formule de Heron
   return sqrt( p* (p-a)* (p-b) * (p-c) );
}
float Triangle::area(const Point<float, 4> &v0,const Point<float, 4> &v1,const Point<float, 4> &v2) const
{
    float a = cote(v1,v2);
    float b = cote(v0,v1);
    float c = cote(v2,v0);
     //formule de Heron
   return sqrt( ((a+b+c)/2) * (((a+b+c)/2)-a)* (((a+b+c)/2)-b) * (((a+b+c)/2)-c) );
}
Point<float, 4> Triangle::center() const
{
    return Point4rZero;
}
Direction<float, 4> Triangle::normal() const
{
    /*
    n= cross( (v1 -v0),(v2-v0) ) */

    Direction<float, 4> dir_e_01 = p0() - p1();
    Direction<float, 4> dir_e_02 = p0() - p2();
    //Direction<float, 4> e_012 = p2() - p1();

    Vector<float,3> e_01{dir_e_01.x(),dir_e_01.y(),dir_e_01.z()};
    Vector<float,3> e_02{dir_e_02.x(),dir_e_02.y(),dir_e_02.z()};
    
    Vector<float,3> d = cross(e_01,e_02);
    
    Vector<float,4> result {0,d.at(0),d.at(1),d.at(2)};
    return Direction<float,4>(result);

    //return dot()

}
XYBBox Triangle::xybbox() const
{
    float min_x = p0().x();
    if ( p1().x() < min_x ) min_x = p1().x();
    if ( p2().x() < min_x ) min_x = p2().x();

    float min_y = p0().y();
    if ( p1().y() < min_y ) min_y = p1().y();
    if ( p2().y() < min_y ) min_y = p2().y();

    float max_x = p0().x();
    if ( p1().x() > max_x ) max_x = p1().x();
    if ( p2().x() > max_x ) max_x = p2().x();

    float max_y = p0().y();
    if ( p1().y() > max_y ) max_y = p1().y();
    if ( p2().y() > max_y ) max_y = p2().y();

    return XYBBox(Point<float,4>(0,min_x,max_y,0),Point<float,4>(0,max_x,min_y,0));

}

#pragma endregion

#pragma region XYBBox
XYBBox::XYBBox( const Point<float,4> &a, const Point<float,4> &b )
{
    sequence = new Point<float,4>[2];

    sequence[0] = *new Point<float,4>(a); // upper left
    sequence[1] = *new Point<float,4>(b); // lower right
   
}

XYBBox::~XYBBox()
{
    delete[] sequence;
}
float XYBBox::xmax() const
{
    return sequence[0].x();
}
float XYBBox::ymax() const
{
    return sequence[1].y();
}
float XYBBox::xmin() const
{
    return sequence[1].x();
}
float XYBBox::ymin() const
{
    return sequence[0].y();
}
#pragma endregion