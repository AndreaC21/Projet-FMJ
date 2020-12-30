
Mat44r Camera::get_transf_matrix() const
{
    // Camera orientation in radians (360 degrees = (2 * pi) radians).
    Vec4r a
    {
        this->curr_orient.im()[0]* pi / 180.0f,
        this->curr_orient.im()[1]* pi / 180.0f,
        this->curr_orient.im()[2]* pi / 180.0f,
        0.0f
    };
            
    // Camera transformation matrices.
    Mat44r t1
    { 
        { 1.0f,      0.0f,       0.0f, 0.0f },
        { 0.0f, cos(a[0]), -sin(a[0]), 0.0f },
        { 0.0f, sin(a[0]),  cos(a[0]), 0.0f },
        { 0.0f,      0.0f,       0.0f, 1.0f }
    };

    Mat44r t2
    {
        {  cos(a[1]), 0.0f,  sin(a[1]), 0.0f },
        {       0.0f, 1.0f,       0.0f, 0.0f },
        { -sin(a[1]), 0.0f,  cos(a[1]), 0.0f },
        {       0.0f, 0.0f,       0.0f, 1.0f }
    };

    Mat44r t3
    {
        { cos(a[2]), -sin(a[2]), 0.0f, 0.0f },
        { sin(a[2]),  cos(a[2]), 0.0f, 0.0f },
        {      0.0f,       0.0f, 1.0f, 0.0f },
        {      0.0f,       0.0f, 0.0f, 1.0f }
    };       

    // Calculates final transformation matrix.
    return t1 * (t2 * t3);
}
bool Camera::outside_fov( const Sphere &s ) const
{
    return true;
}
bool Camera::sees( Triangle &t ) const
{
    return true;
}
LineSegment Camera::visible_part( const LineSegment &l ) const
{
    return LineSegment(l.begin(),l.end());
}
Vec4r Camera::get_curr_pos() const
{
    return this->curr_pos;
}
Quatr Camera::get_curr_orient() const
{
    return this->curr_orient;
}
float Camera::get_curr_viewer_dist() const
{
    return this->curr_viewer_dist;
}
