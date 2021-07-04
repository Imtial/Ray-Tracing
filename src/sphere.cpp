#include "sphere.hpp"
#include <GL/glut.h>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define PI  3.141592653589793

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
    double radius = length;
    int stacks = radius * 2;
    int slices = radius * 2;
    if (stacks < 10) stacks = 10;
    if (slices < 10) slices = 10;

    Vector3D points[stacks + 1][slices + 1];

    //generate points

	for(int i = 0; i <= stacks; i++)
	{
		double h = radius * sin( ((double)i/(double)stacks) * (PI/2) );
		double r = radius * cos( ((double)i/(double)stacks) * (PI/2) );
		for(int j = 0; j <= slices; j++)
		{
			points[i][j].x = r * cos( ((double)j/(double)slices) * 2*PI ) + reference_point.x;
			points[i][j].y = r * sin( ((double)j/(double)slices) * 2*PI ) + reference_point.y;
			points[i][j].z = h;
		}
	}

    //draw quads using generated points
    glColor3f(color[0], color[1], color[2]);
	for(int i = 0; i < stacks; i++)
	{
        // glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(int j = 0; j < slices; j++)
		{
			glBegin(GL_QUADS);
            {    
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z + reference_point.z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z + reference_point.z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z + reference_point.z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z + reference_point.z);
					
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z + reference_point.z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z + reference_point.z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z + reference_point.z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z + reference_point.z);	
			}
            glEnd();
		}
	}
}

double Sphere::intersect(Ray& ray, double col[], int level)
{
    Vector3D CA = ray.getStart() - getCenter();
    Vector3D& B = ray.getDirection();
    double r = getRadius();

    double a = B.dot(B);
    double b = 2 * B.dot(CA);
    double c = (CA).dot(CA) - r * r;

    double det = b*b - 4*a*c;

    // double t = -1;
    // if (det >= 0) t = (-b - sqrt(det)) / (2*a);
    // if (t < 0) t = -1;

    double t = -1, t1 = -1, t2 = -1;

    if (det >= 0)
    {
        t1 = (-b - sqrt(det)) / (2*a);
        t2 = (-b + sqrt(det)) / (2*a);
        if (t1 > 0.0)
            t = t1;
        else if (t2 > 0.0)
            t = t2;
    }

    if (t > 0 && level > 0)
    {
        Vector3D intersectionPoint = ray.getStart() + ray.getDirection() * t;
        Vector3D normalAtPoint = (intersectionPoint - getCenter()).norm();
        illuminate(ray, col, level, intersectionPoint, normalAtPoint);
    }

    return t;
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

