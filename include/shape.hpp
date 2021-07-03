#ifndef SHAPE_H
#define SHAPE_H

#include "vector3D.hpp"
#include "ray.hpp"

class Shape
{
    private:
    protected:
        void illuminate(Ray& ray, double col[], int level, Vector3D& intersectionPoint, Vector3D& normalAtIntersection);
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
        virtual char* type();
        virtual void draw() = 0;
        void setColor(double r, double g, double b);
        void setShine(int shine);
        void setCoEfficients(double ambient, double diffuse, double specular, double recursive);
        virtual double intersect(Ray& ray, double col[], int level);
        virtual void print(int precision = 2);
        virtual ~Shape();
};

#endif
