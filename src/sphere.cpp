#include "sphere.hpp"
#include <cstdio>

Sphere::Sphere(Vector3D &center, double radius)
{
    reference_point = center;
    length = radius;
}

char* Sphere::type()
{
    return (char*) "Sphere\n";
}

void Sphere::draw()
{
    printf("Sphere::draw() yet to be implemented");
}

void Sphere::setRadius(double radius)
{
    length = radius;
}

double Sphere::getRadius()
{
    return length;
}

void Sphere::setCenter(Vector3D& center)
{
    reference_point = center;
}

Vector3D& Sphere::getCenter()
{
    return reference_point;
}

void Sphere::print(int precision)
{
    printf("%s", type());
    printf("center = ");
    reference_point.print(precision);
    printf("radius = %0.*lf\n", precision, length);
    printColor(precision);
    printCoeffs(precision);
    printShine();
    printf("\n");
}

Sphere::~Sphere()
{

}

