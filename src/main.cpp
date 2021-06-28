#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/glut.h>
#include "vector3D.hpp"
using namespace std;

#define PI  3.141592653589793
#define DEG2RAD(a) a * PI / 180.0
#define RAD2DEG(a) a * 180.0 / PI

float cameraAngle;
double rot_x, rot_y, rot_z, rot_cyl;

Vector3D pos, l, r, u;

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

void init(){
	//codes for initialization
	// drawgrid=0;
	// drawaxes=1;
	cameraAngle=0.0;
	cameraAngle=3 * PI / 4;
	rot_x = 0.0;
	rot_y = 0.0;
	rot_z = 0.0;
	rot_cyl = 0.0;

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
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1':
			cameraAngle = -0.1;
			l = l * cos(cameraAngle) + l.cross(u) * sin (cameraAngle);
			r = l.cross(u);
			break;

        case '2':
            cameraAngle = 0.1;
			l = l * cos(cameraAngle) + l.cross(u) * sin (cameraAngle);
			r = l.cross(u);
            break;
        
        case '3':
            cameraAngle = 0.1;
			l = l * cos(cameraAngle) + r.cross(l) * sin (cameraAngle);
			u = r.cross(l);
            break;
        case '4':
			cameraAngle = -0.1;
			l = l * cos(cameraAngle) + r.cross(l) * sin (cameraAngle);
			u = r.cross(l);
			break;
		case '5':
			cameraAngle = -0.1;
			u = u * cos(cameraAngle) + l.cross(u) * sin (cameraAngle);
			r = l.cross(u);
			break;
		case '6':
			cameraAngle = +0.1;
			u = u * cos(cameraAngle) + l.cross(u) * sin (cameraAngle);
			r = l.cross(u);
			break;

		case 'q':
			// rotate counter-clockwise around u vector
			if (rot_y < 60) rot_y += 10;
			break;
		case 'w':
			// rotate clockwise around u vector
			if (rot_y > -60) rot_y -= 10;
			break;
		case 'e':
			// rotate counter-clockwise to open sphere
			if (rot_x > -60) rot_x -= 10;
			break;
		case 'r':
			// rotate clockwise to open sphere
			if (rot_x < 60) rot_x += 10;
			break;
		case 'a':
			if (rot_cyl < 60) rot_cyl += 10;
			break;
		case 's':
			if (rot_cyl > -60) rot_cyl -= 10;
			break;
		case 'd':
			if (rot_z < 60) rot_z += 10;
			break;
		case 'f':
			if (rot_z > -60) rot_z -= 10;
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
            pos.z += 5;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos.z -= 5;
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
	drawGrid();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

int depth, dim;
void loadData(bool print)
{
	ifstream fin("scene.txt");
	fin >> depth >> dim;

	int objCount;
	fin >> objCount;

	for (int i = 0; i < objCount; i++)
	{
		
	}
	
	fin.close();
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	// glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}