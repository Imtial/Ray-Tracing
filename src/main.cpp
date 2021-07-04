#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #include <windows.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include "vector3D.hpp"
#include "shape.hpp"
#include "floor.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "generalShape.hpp"
#include "light.hpp"
#include "bitmap_image.hpp"
using namespace std;

typedef vector<Shape*> VS;
typedef vector<Light*> VL;

#define PI  3.141592653589793
#define DEG2RAD(a) a * PI / 180.0
#define RAD2DEG(a) a * 180.0 / PI

#define WIN_HEIGHT	500
#define WIN_WIDTH	500
#define VIEWANGLE	80

float cameraAngle;
double rot_x, rot_y, rot_z, rot_cyl;

int depth, dim;
Vector3D pos, l, r, u;

VS shapes;
VL lights;


void drawAxes()
{
	glBegin(GL_LINES);{
		glColor3f(1.0, 0.3, 0.3); // RED X
		glVertex3f( 200,0,0);
		glVertex3f(-200,0,0);

		glColor3f(0.2, 0.4, 1.0); // BLUE Y
		glVertex3f(0,-200,0);
		glVertex3f(0, 200,0);

		glColor3f(0.0, 0.9, 0.2); // GREEN Z
		glVertex3f(0,0, 200);
		glVertex3f(0,0,-200);
	} glEnd();
}

void drawGrid()
{
	int i;
	
	glColor3f(0.6, 0.6, 0.6);	//grey
	glBegin(GL_LINES);{
		for(i=-8;i<=8;i++){

			if(i==0)
				continue;	//SKIP the MAIN axes

			//lines parallel to Y-axis
			glVertex3f(i*10, -90, 0);
			glVertex3f(i*10,  90, 0);

			//lines parallel to X-axis
			glVertex3f(-90, i*10, 0);
			glVertex3f( 90, i*10, 0);
		}
	} glEnd();	
}

void capture()
{
	double winHeight = WIN_HEIGHT, winWidth = WIN_WIDTH;
	double imgWidth = dim, imgHeight = dim;

	bitmap_image image(imgWidth, imgHeight);

	double planeDistance = (winHeight / 2.0) / tan( DEG2RAD(VIEWANGLE)/2.0 );

	Vector3D topLeft = pos + l*planeDistance - r*(winWidth / 2) + u*(winHeight / 2);

	double du = winWidth / imgWidth;
	double dv = winHeight / imgHeight;

	// Choose middle of the grid cell
	topLeft = topLeft + r*(0.5*du) - u*(0.5*dv);

	for (int i = 0; i < imgWidth; i++)
	{
		for (int j = 0; j < imgHeight; j++)
		{
			Vector3D curPx = topLeft + r*(du*i) - u*(dv*j);
			Vector3D rayDir = curPx - pos;
			Ray ray(pos, rayDir);

			double color[3] = {0, 0, 0};
			Shape * nearest = NULL;
			
			double t, tMin = 9999999;
			for (Shape * shape : shapes)
			{
				t = shape->intersect(ray, color, 0);
				
				if (t > 0 && t < tMin)
				{
					tMin = t;
					nearest = shape;
				}
			}
			if (nearest != NULL) nearest->intersect(ray, color, 1);
			for (int i = 0; i < 3; i++)
				if (color[i] > 1) color[i] = 1;
			image.set_pixel(i, j, color[0]*255, color[1]*255, color[2]*255);
		}
	}
	printf("Image saved.\n");
	image.save_image("out.bmp");
}

void init(){
	//codes for initialization
	// drawgrid=0;
	// drawaxes=1;
	cameraAngle = 3*PI / 4;

    pos.x = 50, pos.y = 50, pos.z = 5;
    u.x = 0, u.y = 0, u.z = 1;
    r.x = cos(cameraAngle), r.y = sin(cameraAngle), r.z = 0;
    l.x = cos(cameraAngle + PI / 2), l.y = sin(cameraAngle + PI / 2), l.z = 0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(VIEWANGLE,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1':
			cameraAngle = -0.1;
			// l = l * cos(cameraAngle) + l.cross(u) * sin (cameraAngle);
			l = (l * cos(cameraAngle) + r * sin(cameraAngle)).norm();
			r = (l.cross(u)).norm();
			break;

        case '2':
            cameraAngle = 0.1;
			l = (l * cos(cameraAngle) + r * sin (cameraAngle)).norm();
			r = (l.cross(u)).norm();
            break;
        
        case '3':
            cameraAngle = 0.1;
			l = (l * cos(cameraAngle) + u * sin (cameraAngle)).norm();
			u = (r.cross(l)).norm();
            break;
        case '4':
			cameraAngle = -0.1;
			l = (l * cos(cameraAngle) + u * sin (cameraAngle)).norm();
			u = (r.cross(l)).norm();
			break;
		case '5':
			cameraAngle = -0.1;
			u = (u * cos(cameraAngle) + r * sin (cameraAngle)).norm();
			r = (l.cross(u)).norm();
			break;
		case '6':
			cameraAngle = +0.1;
			u = (u * cos(cameraAngle) + r * sin (cameraAngle)).norm();
			r = (l.cross(u)).norm();
			break;
		case '0':
			printf("u=%lf, r=%lf, l=%lf\n", u.abs(), r.abs(), l.abs());
			printf("u.l=%lf, l.r=%lf, r.u=%lf\n", u.dot(l), l.dot(r), r.dot(u));
			u.print(); (r.cross(l)).print();
			l.print(); (u.cross(r)).print();
			r.print(); (l.cross(u)).print();
			break;
		case 's':
			capture();
			break;
		default:
			break;
	}
    glutPostRedisplay();
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			pos = pos - l * 2;
			break;
		case GLUT_KEY_UP:		// up arrow key
			pos = pos + l * 2;
			break;

		case GLUT_KEY_RIGHT:
			pos = pos + r * 2;
			break;
		case GLUT_KEY_LEFT:
			pos = pos - r * 2;
			break;

		case GLUT_KEY_PAGE_UP:
            pos = pos + u * 2;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos = pos - u * 2;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
    glutPostRedisplay();
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
	glutPostRedisplay();
}

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	// l = l * cos(cameraAngle) + l.cross(u) * sin (cameraAngle);
	
	gluLookAt(pos.x, pos.y, pos.z,
            pos.x+l.x, pos.y+l.y, pos.z+l.z,
            u.x, u.y, u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects
	drawAxes();
	// drawGrid();
	for (Shape * shape : shapes) shape->draw();
	for (Light * light : lights) light->draw();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void clearMemory()
{
	for (Shape *shape : shapes) delete shape;
	for (Light *light : lights) delete light;
	shapes.clear();
	lights.clear();
}

void loadData(bool print = false)
{
	ifstream fin("scene-test.txt");
	fin >> depth >> dim;

	Shape * floor = new Floor(1000, 20);
	floor->setCoEfficients(0.3, 0.3, 0.2, 0.3);
	floor->setShine(5);
	shapes.push_back(floor);

	int objCount;
	fin >> objCount;

	for (int i = 0; i < objCount; i++)
	{
		string objName;
		fin >> objName;
		if (objName == "sphere")
		{
			double center1, center2, center3;
			fin >> center1 >> center2 >> center3;
			double radius;
			fin >> radius;
			double r, g, b;
			fin >> r >> g >> b;
			double amb, dif, spec, rec;
			fin >> amb >> dif >> spec >> rec;
			int shine;
			fin >> shine;

			Vector3D center(center1, center2, center3);
			Shape * sphere = new Sphere(center, radius);
			sphere->setColor(r, g, b);
			sphere->setCoEfficients(amb, dif, spec, rec);
			sphere->setShine(shine);

			shapes.push_back(sphere);
		}
		else if (objName == "triangle")
		{
			double x1, y1, z1, x2, y2, z2, x3, y3, z3;
			fin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			double r, g, b;
			fin >> r >> g >> b;
			double amb, dif, spec, rec;
			fin >> amb >> dif >> spec >> rec;
			int shine;
			fin >> shine;

			Shape * triangle = new Triangle(x1,y1,z1,  x2,y2,z2,  x3,y3,z3);
			triangle->setColor(r, g, b);
			triangle->setCoEfficients(amb, dif, spec, rec);
			triangle->setShine(shine);

			shapes.push_back(triangle);
		}
		else if (objName == "general")
		{
			double a, b, c, d, e, f, g, h, i, j;
			fin >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j;
			double x, y, z, length, width, height;
			fin >> x >> y >> z >> length >> width >> height;
			double red, green, blue;
			fin >> red >> green >> blue;
			double amb, dif, spec, rec;
			fin >> amb >> dif >> spec >> rec;
			int shine;
			fin >> shine;

			Vector3D cube_ref_point(x, y, z);
			Shape * general = new GeneralShape(a, b, c, d, e, f, g, h, i, j,
									cube_ref_point, length, width, height);
			general->setColor(red, green, blue);
			general->setCoEfficients(amb, dif, spec, rec);
			general->setShine(shine);

			shapes.push_back(general);
		}
	}

	int lightCount;
	fin >> lightCount;

	for (int i = 0; i < lightCount; i++)
	{
		double x, y, z;
		fin >> x >> y >> z;
		double r, g, b;
		fin >> r >> g >> b;

		Light * light = new Light(x, y, z, r, g, b);
		lights.push_back(light);
	}

	// for (Shape * shape : shapes) shape->print();
	// for (Light * light : lights) light->print();
	
	fin.close();
}

int main(int argc, char **argv){

	loadData();

	glutInit(&argc,argv);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("OpnGL Ray Tracing");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	// glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	clearMemory();

	return 0;
}