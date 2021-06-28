#include "generalShape.hpp"
#include <cstdio>

GeneralShape::GeneralShape(double a, double b, double c, double d, double e,
                        double f, double g, double h, double i, double j,
                        Vector3D& cube_ref_point, double length, double width, double height)
                        : surfaceCoeffs{a, b, c, d, e, f, g, h, i, j}
{
    reference_point = cube_ref_point;
    this->length = length;
    this->width = width;
    this->height = height;
}

char* GeneralShape::type()
{
    return (char*) "General\n";
}

void GeneralShape::draw()
{
    printf("GeneralShape::draw() is yet to be implemented\n");
}

void GeneralShape::setSurfaceCoeffs(double a, double b, double c, double d, double e,
                                double f, double g, double h, double i, double j)

{
    surfaceCoeffs[0] = a, surfaceCoeffs[1] = b, surfaceCoeffs[2] = c, surfaceCoeffs[3] = d,
    surfaceCoeffs[4] = e, surfaceCoeffs[5] = f, surfaceCoeffs[6] = g, surfaceCoeffs[7] = h,
    surfaceCoeffs[8] = i, surfaceCoeffs[9] = j; 
}

double (&GeneralShape::getSurfaceCoeffs())[10]
{
    return surfaceCoeffs;
}

void GeneralShape::setSurfaceCoeff(double coeff, int index)
{
    if (index < 0 || index > 9) printf("[%s:%d] error: index out of range!\n", __FILE__, __LINE__);
    else surfaceCoeffs[index] = coeff;
}

double GeneralShape::getSurfaceCoeff(int index)
{
    if (index < 0 || index > 9)
    {
        printf("[%s:%d] error: index out of range! returning negative value.\n", __FILE__, __LINE__);
        return -1;
    }
    return surfaceCoeffs[index];
}

void GeneralShape::setSurfaceCoeff(double coeff, char coeffLabel)
{
    int index = coeffLabel - 'a';
    if (index < 0 || index > 9) printf("[%s:%d] error: index out of range!\n", __FILE__, __LINE__);
    else surfaceCoeffs[index] = coeff;
}

double GeneralShape::getSurfaceCoeff(char coeffLabel)
{
    int index = coeffLabel - 'a';
    if (index < 0 || index > 9)
    {
        printf("[%s:%d] error: index out of range! returning negative value.\n", __FILE__, __LINE__);
        return -1;
    }
    return surfaceCoeffs[index];
}

void GeneralShape::print(int precision)
{
    printf("%s", type());
    printf("Surface coefficients: ");
    for (int i = 0; i < 10; i++) printf("%0.*lf ", precision, surfaceCoeffs[i]);
    printf("\n");
    printf("Cubic reference point: ");
    reference_point.print(precision);
    printf("length = %0.*lf, width = %0.*lf, height = %0.*lf\n", precision, length, precision, width, precision, height);
    printColor(precision);
    printCoeffs(precision);
    printShine();
    printf("\n");
}


GeneralShape::~GeneralShape()
{

}

