#include "vector3D.hpp"
#include <cstdio>
#include <cmath>


Vector3D::Vector3D(double x, double y) : x(x), y(y) {}

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

void Vector3D::setXYZ(double x, double y, double z)
{
	this->x = x, this->y = y, this->z = z;
}

double Vector3D::dist(Vector3D &rhs)
{
    return sqrt((rhs.x-x)*(rhs.x-x) + (rhs.y-y)*(rhs.y-y) + (rhs.z-z)*(rhs.z-z));
}

Vector3D Vector3D::norm()
{
    double mod = sqrt(x*x + y*y + z*z);
    return Vector3D(x/mod, y/mod, z/mod);
}

double Vector3D::dot(Vector3D &rhs)
{
    return x*rhs.x + y*rhs.y + z*rhs.z;
}

Vector3D Vector3D::cross(Vector3D &rhs)
{
    return Vector3D(y*rhs.z - rhs.y*z, z*rhs.x - rhs.z*x, x*rhs.y - rhs.x*y);
}

Vector3D Vector3D::operator+(Vector3D rhs)
{
    return Vector3D(x+rhs.x, y+rhs.y, z+rhs.z);
}

Vector3D Vector3D::operator-(Vector3D rhs)
{
    return Vector3D(x-rhs.x, y-rhs.y, z-rhs.z);
}

Vector3D Vector3D::operator*(double n)
{
    return Vector3D(x*n, y*n, z*n);
}

void Vector3D::print(int precision)
{
    printf("%0.*f, %0.*f, %0.*f\n", precision, x, precision, y, precision, z);
}
