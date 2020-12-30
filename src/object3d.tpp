Object3D::Object3D(std::vector<Point3r> v,std::vector<Vec3i> f)
{
    this->vertices = v;
    for ( int i = 0; i < f.size() ; ++i)
    {
        add_face(f[i].at(0),f[i].at(1),f[i].at(2));
    }
}
Object3D::Object3D(const Object3D& o)
{
    this->vertices = o.vertices;
    this->faces = o.faces;
}

float Object3D::distance(Point3r a, Point3r b) const
{
    return sqrt(pow(a.x()-b.x(),2)+pow(a.y()-b.y(),2)+pow(a.z()-b.z(),2));
}
Sphere Object3D::bsphere() const
{
    float max = 0.0f;
    int indice_v0 = 0;
    int indice_v1 = 0;
    for ( int i=0; i < this->vertices.size() ; ++i)
    {
        for ( int j=0; j < this->vertices.size() ; ++j)
        {
            if (float m=distance(this->vertices[i],this->vertices[j]) > max)
            {
                max = m;
                indice_v0 = i;
                indice_v1 = j;
            }
        }
    }
    Vec3r v0 { this->vertices[indice_v0].x(),this->vertices[indice_v0].y(),this->vertices[indice_v0].z() };
    Vec3r v1 { this->vertices[indice_v1].x(),this->vertices[indice_v1].y(),this->vertices[indice_v1].z() };
    
    //c= (v0+v1)*1/2
    Point3r c( (v0+v1)*0.5f);
    Point<float,4> center(0,c.x(),c.y(),c.z());
    //r=|v1−c| //point - point
    float radius = distance(v1,c);
    return Sphere(center,radius);
}

Triangle Object3D::face( unsigned int i ) const
{
    return *this->faces[i];
}

unsigned int Object3D::num_faces() const
{
    return this->faces.size();
}

void Object3D::add_face( unsigned int v1, unsigned int v2, unsigned int v3)
{
    Point<float,4> a(this->vertices[v1-1]);// dans le fichier vertice 1 fait reference au sommet 0 en memoire donc -1
    Point<float,4> b(this->vertices[v2-1]);
    Point<float,4> c(this->vertices[v3-1]);
    
    this->faces.push_back( new Triangle(a,b,c));
}