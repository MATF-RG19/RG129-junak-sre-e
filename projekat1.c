#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 20

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Junak srece");

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);

	glClearColor(0.153, 0.153, 0.255, 0);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();	

	return 0;
}

/* Program reaguje na tastere:

	esc
		-izlazi iz programa

*/
static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
	case 27:
		exit(0);
		break;
	}
}
static void on_reshape(int width, int height){

	glViewport(0, 0, width, height);
	
//Podesavanje projekcije - bice manjih izmena
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1, 20);
	
}

//Za sada timer funkcija nema posebnu ulogu
static void on_timer(int id){

	if(id != TIMER_ID){
		return;
	}

	glutPostRedisplay();

}
static void on_display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Podesavanje projekcije - podlozno izmenama 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1, 20);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

	// Objekat koji predstavlja igraca

	glColor3f(0.804, 0.522, 0.247);
	glutSolidCube(1);

	glutSwapBuffers();
	
}


























