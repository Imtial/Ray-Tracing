#include "floor.hpp"
#include <cstdio>
#include <cmath>
#include <GL/glut.h>

Floor::Floor(double floorWidth, double tileWidth)
{
    reference_point = Vector3D(-floorWidth / 2, -floorWidth / 2, 0);
    length = tileWidth;
}

void Floor::draw()
{
    double refX = reference_point.x;
    double refY = reference_point.y;

    int stepsX = refX * (-2) / length;
    int stepsY = refY * (-2) / length;

    for (int i = 0; i < stepsX; i++)
    {
        for (int j = 0; j < stepsY; j++)
        {
            if ((i + j) % 2) glColor3f(0.1, 0.1, 0.1);
            else glColor3f(0.9, 0.9, 0.9);

            glBegin(GL_QUADS);
            {
                glVertex3f(refX + i*length, refY + j*length, 0);
                glVertex3f(refX + (i + 1)*length, refY + j*length, 0);   
                glVertex3f(refX + (i + 1)*length, refY + (j + 1)*length, 0);
                glVertex3f(refX + i*length, refY + (j + 1)*length, 0);
            }
            glEnd();
        }
    }
}

char* Floor::type()
{
    return (char*) "Floor\n";
}

void Floor::setTileWidth(double tileWidth)
{
    length = tileWidth;
}

double Floor::getTileWidth()
{
    return length;
}

double Floor::intersect(Ray& ray, double col[], int level)
{
    Vector3D o(0, 0, 0);
    Vector3D n(0, 0, 1);

    double t = -1;
    double denominator = ray.getDirection().dot(n);

    if (abs(denominator) > 0.000001) 
    {
        Vector3D ro = o - ray.getStart();
        t = ro.dot(n) / denominator;
    }

    if (t > 0 && level > 0)
    {

        Vector3D intersectionPoint = ray.getStart() + ray.getDirection() * t;
        intersectionPoint.z = 0;

        if (intersectionPoint.x >= reference_point.x &&
            intersectionPoint.x <= -reference_point.x &&
            intersectionPoint.y >= reference_point.y &&
            intersectionPoint.y <= -reference_point.y)
        {
            // take the floor
            int row = floor((intersectionPoint.x - reference_point.x) / getTileWidth());
            int col = floor((intersectionPoint.y - reference_point.y) / getTileWidth());

            if ((row + col) % 2) this->setColor(0.1, 0.1, 0.1);
            else this->setColor(0.9, 0.9, 0.9);
        }
        else return -1;

        Vector3D& normalAtPoint = n;
        illuminate(ray, col, level, intersectionPoint, normalAtPoint);

    }
    return t;
}

void Floor::print(int precision)
{
    printf("%s", type());
    printf("Reference Point = ");
    reference_point.print(precision);
    printf("tile width = %0.*lf\n", precision, length);
    printColor(precision);
    printCoeffs(precision);
    printShine();
}

Floor::~Floor()
{

}

