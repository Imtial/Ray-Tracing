#ifndef SHAPE_H
#define SHAPE_H

#include "vector3D.hpp"

class Shape
{
    private:
    protected:
        void printColor(int precision);
        void printCoeffs(int precision);
        void printShine();
    public:
        Vector3D reference_point;
        double height, width, length;
        double color[3];
        double coEfficients[4]; // reflection coefficients
        int shine; // exponent term of specular component
        
        Shape();
        virtual void draw() = 0;
        void setColor(double r, double g, double b);
        void setShine(int shine);
        void setCoEfficients(double ambient, double diffuse, double specular, double recursive);
        virtual void print(int precision);
        ~Shape();
};

#endif
