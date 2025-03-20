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

void viewPort1() {
	glLoadIdentity();
	glViewport(10, 10, 600, 600); // square (as the clipping view)  resolution 200x200 pixels

	glColor3f(1.0f, 0.0f, 0.0f); //red color
	glTranslatef(3, 0, 0);
	glRotatef(realTimeRotate, 0, 1, 0); // rotate 90 degrees
	glTranslatef(-3, 0, 0);
	glutWireSphere(1.0f, 20.0f, 20.0f);
}
void viewPort2() {
	glLoadIdentity();
	glViewport(900, 200, 500, 500); // square (as the clipping view)  resolution 200x200 pixels

	glColor3f(0.0f, 1.0f, 0.0f); //greencolor
	glScalef(delta, delta, delta);
	glutSolidCube(1.0f);
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

		alpha += 1;
		break;

	case GLUT_KEY_DOWN:

		alpha -= 1;
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
