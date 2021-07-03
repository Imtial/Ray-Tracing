#include "generalShape.hpp"
#include "light.hpp"
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

extern std::vector<Light*> lights;
extern std::vector<Shape*> shapes;

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
    double a = height;
    Vector3D &p = reference_point;
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    {
        glVertex3f(p.x +a, p.y +a, p.z -a);
        glVertex3f(p.x +a, p.y -a, p.z -a);
        glVertex3f(p.x -a, p.y -a, p.z -a);
        glVertex3f(p.x -a, p.y +a, p.z -a);
    }
    glEnd();
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

double GeneralShape::intersect(Ray& ray, double col[], int level)
{
    double eps = 0.000001;

    double A = surfaceCoeffs[0];
    double B = surfaceCoeffs[1];
    double C = surfaceCoeffs[2];
    double D = surfaceCoeffs[3];
    double E = surfaceCoeffs[4];
    double F = surfaceCoeffs[5];
    double G = surfaceCoeffs[6];
    double H = surfaceCoeffs[7];
    double I = surfaceCoeffs[8];
    double J = surfaceCoeffs[9];

    double xo = ray.getStart().x, yo = ray.getStart().y, zo = ray.getStart().z;
    double xd = ray.getDirection().x, yd = ray.getDirection().y, zd = ray.getDirection().z;

    double a = A*xd*xd + B*yd*yd + C*zd*zd + D*xd*yd + E*xd*zd + F*yd*zd;
    double b = 2 * (A*xo*xd + B*yo*yd + C*zo*zd) + D * (xo*yd + yo*xd) + E * (xo*zd + zo*xd)
                + F * (yo*zd + zo*yd) + G*xd + H*yd + I*zd;
    double c = A*xo*xo + B*yo*yo + C*zo*zo + D*xo*yo + E*xo*zo + F*yo*zo + G*xo + H*yo + I*zo + J;

    double discrim = b*b - 4*a*c;

    double t1 = -1, t2 = -1, t = -1;

    if (a < eps && a > -eps) t = -c / b;


    if (discrim >= 0)
    {
        t1 = (-b - sqrt(discrim)) / (2*a);
        t2 = (-b + sqrt(discrim)) / (2*a);

        if (t1 >= 0 && t2 < 0)
        {
            Vector3D ip1 = ray.getStart() + ray.getDirection() * t1;
            Vector3D ip1Dist = ip1 - reference_point;

            if ( (length > 0 && abs(ip1Dist.x) <= length) || 
                 (width > 0 && abs(ip1Dist.y) <= width) || 
                 (height > 0 && abs(ip1Dist.z) <= height) )
                t = t1;
        }
        else if (t2 >= 0 && t1 < 0)
        {
            Vector3D ip2 = ray.getStart() + ray.getDirection() * t2;
            Vector3D ip2Dist = ip2 - reference_point;

            if ( (length > 0 && abs(ip2Dist.x) <= length) || 
                 (width > 0 && abs(ip2Dist.y) <= width) || 
                 (height > 0 && abs(ip2Dist.z) <= height) )
                t = t2;
        }
        else if (t1 >= 0 && t2 >= 0)
        {
            Vector3D ip1 = ray.getStart() + ray.getDirection() * t1;
            Vector3D ip1Dist = ip1 - reference_point;
            Vector3D ip2 = ray.getStart() + ray.getDirection() * t2;
            Vector3D ip2Dist = ip2 - reference_point;

            if ((length > 0 && abs(ip1Dist.x) <= length && abs(ip2Dist.x) <= length) ||
                (width > 0 && abs(ip1Dist.y) <= width && abs(ip2Dist.y) <= width) ||
                (height > 0 && abs(ip1Dist.z) <= height && abs(ip2Dist.z) <= height))
                t = (t1 < t2) ? t1 : t2;

            else if ( (length > 0 && abs(ip1Dist.x) <= length) || 
                 (width > 0 && abs(ip1Dist.y) <= width) || 
                 (height > 0 && abs(ip1Dist.z) <= height) )
                t = t1;

            else if ( (length > 0 && abs(ip2Dist.x) <= length) || 
                 (width > 0 && abs(ip2Dist.y) <= width) || 
                 (height > 0 && abs(ip2Dist.z) <= height) )
                t = t2;

            else 
                t = -1;
        }
    }

/* 
    double xo = ray.getStart().x, yo = ray.getStart().y, zo = ray.getStart().z;
    double xd = ray.getDirection().x, yd = ray.getDirection().y, zd = ray.getDirection().z;

    double a = A*xd*xd + B*yd*yd + C*zd*zd + D*xd*yd + E*xd*zd + F*yd*zd;
    double b = 2 * (A*xo*xd + B*yo*yd + C*zo*zd) + D * (xo*yd + yo*xd) + E * (xo*zd + zo*xd)
                + F * (yo*zd + zo*yd) + G*xd + H*yd + I*zd;
    double c = A*xo*xo + B*yo*yo + C*zo*zo + D*xo*yo + E*xo*zo + F*yo*zo + G*xo + H*yo + I*zo + J;

    double discrim = b*b - 4*a*c;

    double t1 = -1, t2 = -1, t = -1;

    if (a < eps && a > -eps) t = -c / b;

    if (discrim >= 0)
    {
        t1 = (-b - sqrt(discrim)) / (2*a);
        t2 = (-b + sqrt(discrim)) / (2*a);

        if(t2 >= 0 && t1 < 0)
        {
            Vector3D ip2 = ray.getStart() + ray.getDirection() * t2;
            Vector3D ip2Dist = ip2 - reference_point;
            
            if(length > 0)
            {
                if(abs(ip2Dist.x) > length)
                    return -1.0;

                else
                {
                    t = t2;
                }
            }

            if(width > 0)
            {
                if(abs(ip2Dist.y) > width)
                    return -1.0;

                else
                {
                    t = t2;
                }
            }

            if(height > 0)
            {
                if(abs(ip2Dist.z) > height)
                    return -1.0;

                else
                {
                    t = t2;
                }
            }
        }

        else if(t1 >= 0 && t2 < 0)
        {
            t = t1;
        }

        else if(t1 >= 0 && t2 >= 0)
        {
            Vector3D ip1 = ray.getStart() + ray.getDirection() * t1;
            Vector3D ip2 = ray.getStart() + ray.getDirection() * t2;

            Vector3D ip1Dist = ip1 - reference_point;
            Vector3D ip2Dist = ip2 - reference_point;
            
            if(length > 0)
            {
                if(abs(ip1Dist.x) > length && abs(ip2Dist.x) > length)
                    return -1.0;

                if(abs(ip1Dist.x) > length)
                    t = t2;

                else if(abs(ip2Dist.x) > length)
                    t = t1;

                else
                    t = std::min(t1, t2);
            }

            if(width > 0)
            {
                if(abs(ip1Dist.y) > width && abs(ip2Dist.y) > width)
                    return -1.0;

                if(abs(ip1Dist.y) > width)
                    t = t2;

                else if(abs(ip2Dist.y) > width)
                    t = t1;

                else
                    t = std::min(t1, t2);
            }

            if(height > 0)
            {
                if(abs(ip1Dist.z) > height && abs(ip2Dist.z) > height)
                    return -1.0;

                if(abs(ip1Dist.z) > height)
                    t = t2;

                else if(abs(ip2Dist.z) > height)
                    t = t1;

                else
                    t = std::min(t1, t2);
            }

        }

    } */

    if (t > 0 && level > 0)
    {
        Vector3D intersectionPoint = ray.getStart() + ray.getDirection() * t;
        Vector3D normalAtPoint = Vector3D(
            2*A*intersectionPoint.x + D*intersectionPoint.y + E*intersectionPoint.z + G,
            2*B*intersectionPoint.y + D*intersectionPoint.x + F*intersectionPoint.z + H,
            2*C*intersectionPoint.z + E*intersectionPoint.x + F*intersectionPoint.y + I
        ).norm();

        illuminate(ray, col, level, intersectionPoint, normalAtPoint);
    }

    return t;

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

