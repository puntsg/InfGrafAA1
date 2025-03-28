#include <GL/glut.h>

float delta = 1.0f;
float alpha = 0.0f;
float beta = 0.0f;

float realTimeRotate = 0.0f;

int init(void) {

	glClearColor(0.0, 0.0, 0.0, 0.0);		//Background colour
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);			//Set geometry type
	//Set image proportion and axis lengths
	glOrtho(-5, 5, -5, 5, -5, 5);
	gluLookAt(
		0, 3, 0,
		0, 0, 0, 
		0, 0, -1
	);
	return 0;

}
void DrawPyramid(float height, float minX, float maxX, float minZ, float maxZ) {
	// Base
	glColor3f(1.0f, 1.0f, 1.0f); // blanc
	glBegin(GL_QUADS);
	glVertex3f(minX, 0, minZ);
	glVertex3f(minX, 0, maxZ);
	glVertex3f(maxX, 0, maxZ);
	glVertex3f(maxX, 0, minZ);
	glEnd();

	glBegin(GL_TRIANGLES);
	float midX = (minX + maxX) / 2.0f;
	float midZ = (minZ + maxZ) / 2.0f;

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(midX, height, midZ);
	glVertex3f(minX, 0, minZ);
	glVertex3f(minX, 0, maxZ);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(midX, height, midZ);
	glVertex3f(minX, 0, maxZ);
	glVertex3f(maxX, 0, maxZ);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(midX, height, midZ);
	glVertex3f(maxX, 0, maxZ);
	glVertex3f(maxX, 0, minZ);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(midX, height, midZ);
	glVertex3f(maxX, 0, minZ);
	glVertex3f(minX, 0, minZ);

	glEnd();
}

void viewPort1() {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(10, 10, 600, 600); // square (as the clipping view)  resolution 200x200 pixels
	glOrtho(-10, 10, -10, 10, -10,10);
	gluLookAt(
		0, 10, 0,
		0, 0, 0,
		0, 0, -1
	);
	glColor3f(1.0f, 0.0f, 0.0f); //red color
	glTranslatef(3, 0, 0);
	glRotatef(realTimeRotate, 0, 1, 0); // rotate 90 degrees
	glTranslatef(-3, 0, 0);
	glRotatef(-realTimeRotate*2, 0, 1, 0);
	glutWireSphere(1.0f, 20.0f, 20.0f);
}
void viewPort2() {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(900, 200, 500, 500); // square (as the clipping view)  resolution 200x200 pixels
	gluPerspective(60,1,1,100);
	gluLookAt(
		5, 5, 5,
		0, 0, 0,
		0, 1, 0
	);
	glColor3f(0.0f, 1.0f, 1.0f); 
	glScalef(delta, delta, delta);
	glutSolidCube(1.0f);

	glColor3f(1.0f, 1.0f, 0.0f); 
	glTranslatef(alpha, 0, beta);

	DrawPyramid(1.5f, -1, 1, -1, 1);
}


void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

	/* First viewport */
	viewPort1();

	/* Second viewport */
	viewPort2();

	glFlush();

}

void keyPressed_special(int key, int x, int y) {

	switch (key) {

	case GLUT_KEY_LEFT:

		beta += 1;
		break;

	case GLUT_KEY_RIGHT:

		beta -= 1;
		break;

	case GLUT_KEY_UP:

		alpha -= 1;
		break;

	case GLUT_KEY_DOWN:

		alpha += 1;
		break;

	default:

		break;
	}

	glutPostRedisplay();

}

void keyPressed(unsigned char key, int x, int y) {
	switch (key)
	{
	case '+':
		delta *= 1.1f;
		break;
	case '-':
		delta *= 0.9f;
		break;
	case 'r':
		realTimeRotate = 0;
		alpha = 0; beta = 0; delta = 1;
	default:
		break;
	}
	glutPostRedisplay();
}

void timer(int value) {
	realTimeRotate += (realTimeRotate > 360) ? -360.0f : 1.0f;

	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("AA1");
	init();
	glutSpecialFunc(keyPressed_special);
	glutKeyboardFunc(keyPressed);
	glutDisplayFunc(display);
	glutTimerFunc(20, timer, GetCurrentTime());
	glutMainLoop();

	return 0;

}
