#ifndef GENERALSHAPE_H
#define GeneralShape_H

#include "shape.hpp"

class GeneralShape : public Shape
{
    private:
        double surfaceCoeffs[10];
    public:
        GeneralShape(double a, double b, double c, double d, double e,
                    double f, double g, double h, double i, double j,
                    Vector3D& cube_ref_point, double length, double width, double height);
        char* type();
        void draw();
        void setSurfaceCoeffs(double a, double b, double c, double d, double e,
                            double f, double g, double h, double i, double j);
        double (&getSurfaceCoeffs())[10];
        void setSurfaceCoeff(double coeff, int index);
        void setSurfaceCoeff(double coeff, char coeffLabel);
        double getSurfaceCoeff(int index);
        double getSurfaceCoeff(char coeffLabel);
        double intersect(Ray& ray, double col[], int level);
        void print(int precision = 2);
        ~GeneralShape();
};

#endif
