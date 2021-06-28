#ifndef TRIANGLE_H
#define Triangle_H

#include "shape.hpp"

class Triangle : public Shape
{
    private:
        Vector3D points[3];
    public:
        Triangle(double x1, double y1, double z1,
                 double x2, double y2, double z2,
                 double x3, double y3, double z3);
        Triangle(Vector3D& p1, Vector3D& p2, Vector3D& p3);
        char* type();
        void draw();
        void setPoints(double x1, double y1, double z1,
                       double x2, double y2, double z2,
                       double x3, double y3, double z3);
        void setPoints(Vector3D& p1, Vector3D& p2, Vector3D& p3);
        Vector3D (&getPoints())[3];
        void setPoint(Vector3D& p, int i);
        Vector3D& getPoint(int i);
        void print(int precision = 2);
        ~Triangle();
};

#endif
