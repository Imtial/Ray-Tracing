#include "sphere.hpp"
#include <GL/glut.h>
#include <cstdio>
#include <cmath>

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
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z + radius);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z + radius);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z + radius);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z + radius);
					
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z + radius);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z + radius);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z + radius);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z + radius);	
			}
            glEnd();
		}
	}
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

