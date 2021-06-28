#ifndef SPHERE_H
#define Sphere_H

#include "shape.hpp"

class Sphere : protected Shape
{
    private:
    public:
        Sphere(Vector3D &center, double radius);
        void setRadius(double radius);
        double getRadius();
        void setCenter(Vector3D& center);
        Vector3D& getCenter();
        void draw();
        void print(int precision);
        ~Sphere();
};

#endif
