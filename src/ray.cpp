#include "ray.hpp"

Ray::Ray(Vector3D& start, Vector3D& direction)
    : start(start), dir(direction.norm())
{

}

void Ray::setStart(Vector3D& start)
{
    this->start = start;
}

Vector3D& Ray::getStart()
{
    return start;
}

void Ray::setDirection(Vector3D& direction)
{
    dir = direction.norm();
}

Vector3D& Ray::getDirection()
{
    return dir;
}

Ray::~Ray()
{

}

