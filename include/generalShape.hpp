#ifndef GENERALSHAPE_H
#define GeneralShape_H

#include "shape.hpp"

class GeneralShape : protected Shape
{
    private:
        double surfaceCoeffs[10];
    public:
        GeneralShape(double a, double b, double c, double d, double e,
                    double f, double g, double h, double i, double j);
        void draw();
        void setSurfaceCoeffs(double a, double b, double c, double d, double e,
                            double f, double g, double h, double i, double j);
        double (&getSurfaceCoeffs())[10];
        void setSurfaceCoeff(double coeff, int index);
        void setSurfaceCoeff(double coeff, char coeffLabel);
        double getSurfaceCoeff(int index);
        double getSurfaceCoeff(char coeffLabel);
        void print(int precision);
        ~GeneralShape();
};

#endif
