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

double determinant(double a1, double b1, double c1,
                   double a2, double b2, double c2,
                   double a3, double b3, double c3)
{
   return a1 * (b2*c3 - b3*c2) - b1 * (a2*c3 - a3*c2) + c1 * (a2*b3 - a3*b2); 
}

double Triangle::intersect(Ray& ray, double col[], int level)
{
    Vector3D AB = points[1] - points[0];
    Vector3D AC = points[2] - points[0];

    Vector3D h = ray.getDirection().cross(AC);

    double a = AB.dot(h);

    
    if (a > -0.00001 && a < 0.00001) return -1.0;
    double f = 1 / a;
    
    Vector3D s = ray.getStart() - points[0];
    
    double u = f * h.dot(s);
    if (u < 0.0 || u > 1.0)
        return -1.0;
    
    Vector3D q = s.cross(AB);
    double v = f * ray.getDirection().dot(q);

    if (v < 0.0 || (u + v) > 1.0)
        return -1.0;
    
    double t = f * q.dot(AC);

    if (t > 0 && level > 0)
    {
        Vector3D intersectionPoint = ray.getStart() + ray.getDirection() * t;
        Vector3D normalAtPoint = (AB.cross(AC)).norm();
        illuminate(ray, col, level, intersectionPoint, normalAtPoint);        
    }
    return t;
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

