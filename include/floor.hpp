#ifndef FLOOR_H
#define Floor_H

#include "shape.hpp"

class Floor : public Shape
{
    private:
    public:
        Floor(double floorWidth, double tileWidth);
        void draw();
        char* type();
        void setTileWidth(double tileWidth);
        double getTileWidth();
        double intersect(Ray& ray, double col[], int level);
        void print(int precision);
        ~Floor();
};

#endif
