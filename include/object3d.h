// object3d.h

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <vector>


class Object3D
{
    private:

        // sommet 
        vector<Point3r> vertices;
        // list indice f 1 2 3 -> 1 = sommet1,..
        vector<Triangle*> faces;

        float distance(Point3r a, Point3r b) const;

    public:

        Object3D(std::vector<Point3r> v,std::vector<Vec3i> f);
        Object3D(const Object3D&);

        //Returns the bounding sphere.
        Sphere bsphere() const;

        //Returns the n-th face of the object, where n is given as argument.
        Triangle face( unsigned int ) const;

        //Returns the number of faces of the object.
        unsigned int num_faces() const;

        //Adds a face to the object. The three integers given as arguments correspond to three vertices in its list of vertexes.
        void add_face( unsigned int, unsigned int, unsigned int ) ;
};

#include "../src/object3d.tpp"
#endif
