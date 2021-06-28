#ifndef LIGHT_H
#define Light_H

#include "vector3D.hpp"

class Light
{
    private:
        Vector3D light_pos;
        double color[3];
    public:
        Light(double x, double y, double z, double r, double g, double b);
        Light(Vector3D& pos, double r, double g, double b);
        void setPosition(Vector3D& pos);
        Vector3D& getPosition();
        void setColor(double r, double g, double b);
        double (&getColor())[3];
        void print(int precision = 2);
        ~Light();
};

#endif
