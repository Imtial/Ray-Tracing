#include "shape.hpp"
#include <cstdio>

Shape::Shape()
{

}

void Shape::setColor(double r, double g, double b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Shape::setShine(int shine)
{
    this->shine = shine;
}

void Shape::setCoEfficients(double ambient, double diffuse, double specular, double recursive)
{
    coEfficients[0] = ambient;
    coEfficients[1] = diffuse;
    coEfficients[2] = specular;
    coEfficients[3] = recursive;
}

void Shape::printColor(int precision)
{
    printf("color[r g b]: ");
    for (int i = 0; i < 3; i++) printf("%0.*lf ", precision, color[i]);
    printf("\n");
}

void Shape::printCoeffs(int precision)
{
    printf("co-efficients[ambient, diffuse, specular, recursive]: ");
    for (int i = 0; i < 4; i++) printf("%0.*lf ", precision, coEfficients[i]);
    printf("\n");
}

void Shape::printShine()
{
    printf("shine = %d\n", shine);
}

void Shape::print(int precision)
{
    printf("Reference Point = ");
    reference_point.print(precision);
    printf("height = %0.*lf, width = %0.*lf, length = %0.*lf\n", precision, height, precision, width, precision, length);
    printColor(precision);
    printCoeffs(precision);
    printShine();
}

Shape::~Shape()
{

}

