#include "light.hpp"
#include <GL/glut.h>
#include <cstdio>
#include <cmath>

Light::Light(double x, double y, double z, double r, double g, double b)
            : light_pos(x, y, z), color{r, g, b}
{

}

Light::Light(Vector3D& pos, double r, double g, double b)
            : light_pos(pos), color{r, g, b}
{

}

void Light::setPosition(Vector3D& pos)
{
    light_pos = pos;
}

Vector3D& Light::getPosition()
{
    return light_pos;
}

void Light::setColor(double r, double g, double b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b; 
}

double (&Light::getColor())[3]
{
    return color;
}

void Light::draw()
{
    double radius = 1.0;
    int stacks = 8;
    int slices = 8;
    double pi = 3.14159;

    Vector3D points[stacks + 1][slices + 1];

    //generate points

	for(int i = 0; i <= stacks; i++)
	{
		double h = radius * sin( ((double)i/(double)stacks) * (pi/2) );
		double r = radius * cos( ((double)i/(double)stacks) * (pi/2) );
		for(int j = 0; j <= slices; j++)
		{
			points[i][j].x = r * cos( ((double)j/(double)slices) * 2*pi ) + light_pos.x;
			points[i][j].y = r * sin( ((double)j/(double)slices) * 2*pi ) + light_pos.y;
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
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z + light_pos.z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z + light_pos.z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z + light_pos.z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z + light_pos.z);
					
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z + light_pos.z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z + light_pos.z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z + light_pos.z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z + light_pos.z);	
			}
            glEnd();
		}
	}
}

void Light::print(int precision)
{
    printf("source: ");
    light_pos.print(precision);

    printf("color[r g b]: ");
    for (int i = 0; i < 3; i++) printf("%0.*lf ", precision, color[i]);
    printf("\n");
}

Light::~Light()
{

}

