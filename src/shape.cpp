#include "shape.hpp"
#include "light.hpp"
#include <vector>
#include <cstdio>
#include <cmath>

extern std::vector<Shape*> shapes;
extern std::vector<Light*> lights;

Shape::Shape()
{

}

char* Shape::type()
{
    return (char*) "Shape\n";
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

void Shape::illuminate(Ray& ray, double col[], int level, 
                        Vector3D& intersectionPoint, Vector3D& normalAtIntersection)
{
    double pointColor[3];
    for (int i = 0; i < 3; i++)
        pointColor[i] = color[i] * coEfficients[0];
    
    for (Light * light : lights)
    {
        Vector3D lightRayDir = intersectionPoint - light->getPosition();
        Ray lightRay(light->getPosition(), lightRayDir);
        double tLight = (intersectionPoint.x - lightRay.getStart().x) / lightRay.getDirection().x;
        bool isObscured = false;
        for (Shape * shape : shapes)
        {
            double tl = shape->intersect(lightRay, NULL, 0);
            if (tl > 0 && floor(tl) < floor(tLight))
            {
                isObscured = true;
                break;
            }
        }
        if (!isObscured)
        {
            double lambert = normalAtIntersection.dot(lightRay.getDirection());
            if (lambert < 0) lambert = 0;
            Vector3D rayR = lightRay.getDirection() - normalAtIntersection * (2 * lambert);
            double phong = rayR.dot(ray.getDirection());
            if (phong < 0) phong = 0;
            for (int i = 0; i < 3; i++)
                pointColor[i] += light->getColor()[i] * color[i] * coEfficients[1] * lambert
                                + light->getColor()[i] * coEfficients[2] * pow(phong, shine);
        }
    }
    for (int i = 0; i < 3; i++) 
        col[i] = pointColor[i];

    if (level < 5)
    {
        double lambert = normalAtIntersection.dot(ray.getDirection());
        Vector3D reflDir = ray.getDirection() - normalAtIntersection * (2 * lambert);
        Vector3D reflRaySrc = intersectionPoint + reflDir;
        Ray reflRay(reflRaySrc, reflDir);
        double tr, tMin = 9999999;
        Shape * nearest = NULL;
        for (Shape * shape : shapes)
        {
            tr = shape->intersect(reflRay, NULL, 0);
            if (tr > 0 && tr < tMin)
            {
                tMin = tr;
                nearest = shape;
            }
        }
        if (nearest != NULL)
        {
            double reflColor[3];
            nearest->intersect(reflRay, reflColor, level + 1);
            for (int i = 0; i < 3; i++)
                col[i] += reflColor[i] * coEfficients[3];
        }
    }
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

double Shape::intersect(Ray &ray, double col[], int level)
{
    return -1;
}

void Shape::print(int precision)
{
    printf("%s", type());
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

