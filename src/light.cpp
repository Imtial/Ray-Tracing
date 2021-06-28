#include "light.hpp"
#include <cstdio>

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

