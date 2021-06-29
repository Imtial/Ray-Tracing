#include "triangle.hpp"
#include <GL/glut.h>
#include <cstdio>

Triangle::Triangle(double x1, double y1, double z1,
                   double x2, double y2, double z2,
                   double x3, double y3, double z3)
                   : points{
                    Vector3D(x1, y1, z1), 
                    Vector3D(x2, y2, z2), 
                    Vector3D(x3, y3, z3)
                    }
{

}

Triangle::Triangle(Vector3D& p1, Vector3D& p2, Vector3D& p3)
                    : points{p1, p2, p3}
{

}

char* Triangle::type()
{
    return (char*) "Triangle\n";
}

void Triangle::draw()
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < 3; i++)
            glVertex3f(points[i].x, points[i].y, points[i].z);
    }
    glEnd();
}

void Triangle::setPoints(double x1, double y1, double z1,
                        double x2, double y2, double z2,
                        double x3, double y3, double z3)
{
    points[0] = Vector3D(x1, y1, z1);
    points[1] = Vector3D(x2, y2, z2);
    points[2] = Vector3D(x3, y3, z3);
}

void Triangle::setPoints(Vector3D& p1, Vector3D& p2, Vector3D& p3)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

Vector3D (&Triangle::getPoints())[3]
{
    return points;
}

void Triangle::setPoint(Vector3D& p, int i)
{
    if (i < 0 || i > 2) printf("[%s:%d] error: index out of range!\n", __FILE__, __LINE__);
    else points[i] = p;
}

Vector3D& Triangle::getPoint(int i)
{
    if (i < 0 || i > 2) 
    {
        printf("[%s:%d] error: index out of range! returning 1st point.\n", __FILE__, __LINE__);
        return points[0];
    }
    return points[i];
}

void Triangle::print(int precision)
{
    printf("%s", type());
    printf("p1 = "); points[0].print(precision);
    printf("p2 = "); points[1].print(precision);
    printf("p3 = "); points[2].print(precision);
    printColor(precision);
    printCoeffs(precision);
    printShine();
    printf("\n");
}

Triangle::~Triangle()
{

}

