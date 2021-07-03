#ifndef RAY_H
#define Ray_H

#include "vector3D.hpp"

class Ray
{
    private:
        Vector3D start;
        Vector3D dir;
    public:
        Ray(Vector3D& start, Vector3D& direction);
        void setStart(Vector3D& start);
        Vector3D& getStart();
        void setDirection(Vector3D& direction);
        Vector3D& getDirection();
        ~Ray();
};

#endif
