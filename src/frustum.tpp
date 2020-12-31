
//Returns if the point given as argument is outside the field of vision.
bool Frustum::outside( const Point<float, 4> & ) const
{
    return false;
}

// Returns if the sphere given as argument is completely outside the field of vision.
bool  Frustum::outside( const Sphere & ) const
{
    return false;
}

// Returns the intersection between the segment and the field of vision (visible part).
LineSegment  Frustum::inter( const LineSegment & ) const
{
    return LineSegment(Point4rZero,Point4rZero);
}

//Updates the position of the field of vision, where h is the horizontal resolution, v is the vertical resolution 
//and e is the distance between the projection plane and the camera.
void  Frustum::update( float h, float v, float e )
{

}