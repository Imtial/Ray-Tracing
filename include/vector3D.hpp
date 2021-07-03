#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D {

public:
    double x, y, z;
    Vector3D() {x = 0, y = 0, z = 0;}
    Vector3D(double x, double y);
    Vector3D(double x, double y, double z);
	void setXYZ(double x, double y, double z);
    double dist(Vector3D &rhs);
    double abs();
    Vector3D norm();
    double dot(const Vector3D &rhs);
    Vector3D cross(const Vector3D &rhs);
    Vector3D operator+(const Vector3D &rhs);
    Vector3D operator-(const Vector3D &rhs);
    Vector3D operator*(double n);
    bool operator==(Vector3D& rhs);
	void print(int precision = 7);
};

#endif