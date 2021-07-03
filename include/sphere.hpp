#ifndef SPHERE_H
#define Sphere_H

#include "shape.hpp"

class Sphere : public Shape
{
    private:
    public:
        Sphere(Vector3D &center, double radius);
        char* type();
        void setRadius(double radius);
        double getRadius();
        void setCenter(Vector3D& center);
        Vector3D& getCenter();
        double intersect(Ray& ray, double col[], int level);
        void draw();
        void print(int precision = 2);
        ~Sphere();
};

#endif
