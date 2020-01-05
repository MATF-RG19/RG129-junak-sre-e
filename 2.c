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

//a1,a2,a3 su koordinate igraca
double a1=0,a2=0.5,a3=0;

//w, a su parametri za pomeraj igraca
double w=0,a=0;

//pomocna promenljiva kako bi se znalo da li se vrsi kretanje levo/desno ili napred/nazad
int pick_key=0, move_player=0;

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Junak srece");

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
	

	glClearColor(0.153, 0.153, 0.255, 0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LINE_SMOOTH);

	glutMainLoop();	

	return 0;
}

/* Program reaguje na tastere:

	esc
		-izlazi iz programa

	w/W
		-pomera igraca napred

	a/A
		-pomera igraca ulevo

	d/D
		-pomera igraca udesno

	s/S
		-pomera igraca unazad
*/
static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
	case 27:
		exit(0);
		break;
	case 'w':
	case 'W':
		pick_key=0;
		w = 0.3;
		move_player = 1;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		pick_key = 1;
		a = -0.3;
		move_player = 1;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		pick_key = 1;
		a = 0.3;
		move_player = 1;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		pick_key = 0;
		w = -0.3;
		move_player = 1;
		glutPostRedisplay();
		break;
	}
}
static void init_lights()
{
    GLfloat light_position[] = { 1, 15, 5, 0 };
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
static void on_reshape(int width, int height){

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,(float) width/height, 1, 1000);

}

//Za sada timer funkcija nema posebnu ulogu
static void on_timer(int id){

	if(id != TIMER_ID){
		return;
	}

	glutPostRedisplay();

}
static void osnova(){

	glPushMatrix();

		glColor3f(0.7, 0.7, 0.7);
		glScalef(700, 0.2, 20);
		glTranslatef(0.498,0,0);
		glutSolidCube(1);
	

	glPopMatrix();	
}
//Iscrtavanje ograde za podlogu kroz koju igrac ne moze da prodje
static void ograda(){

	int boja=0;

	for(int i=0; i<700; i+= 1, boja++){
		glPushMatrix();
		if (boja < 5)
			glColor3f(0.7, 0.2, 0);
		else{
			glColor3f(0, 0.6, 0.2);
			boja = 0;
		}
		glTranslatef(i, 0.5, -10);
		glutSolidCube(1);
		glPopMatrix();
	}

	boja=0;

	for(int i=0; i<700; i+= 1, boja++){
		glPushMatrix();
		if (boja < 5)
			glColor3f(0.7, 0.2, 0);
		else{
			glColor3f(0, 0.6, 0.2);
			boja = 0;
		}
		glTranslatef(i, 0.5, 10);
		glutSolidCube(1);
		glPopMatrix();
	}

	for(int i=-10; i<11; i+= 1){
		glPushMatrix();
		glColor3f(0.7, 0.2, 0);
		glTranslatef(-1, 0.5, i);
		glutSolidCube(1);
		glPopMatrix();
	}

	for(int i=-10; i<11; i+= 1){
		glPushMatrix();
		glColor3f(0.7, 0.2, 0);
		glTranslatef(-700, 0.5, i);
		glutSolidCube(1);
		glPopMatrix();
	}

	
}
static void igrac(){

	glPushMatrix();

		glColor3f(0.804, 0.522, 0.247);

//Prvi if sluzi da pomeri igraca samo kad je pritisnut neki od tastera za pomeranje igraca

		if (move_player == 1){

			if(pick_key == 0)
				a1 += w;
			else 	
				a3 += a;

			glTranslatef(a1 = a1 + 0, a2=0.7, a3 += 0);

			move_player =0;
		}
		else glTranslatef(a1, a2, a3);

	// onemogucava igracu da se krece van granica ograde

		if (a3 < -9)
			a3 = -9;
		if (a3 > 9)
			a3 = 9;	
		if (a1 < 0)
			a1 =0;
		if (a1 > 699)
			a1 = 699;


		//printf("%f %f\n", a1, w);
		
		glutSolidCube(1);


	glPopMatrix();

}
static void on_display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	init_lights();

	// Podesavanje kamere i tacke gledista tako da prati kretanje igraca

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-20+a1, 10, 0+a3, 0+a1, 3, 0+a3, 0, 1, 0);

	//Osnova
	glPushMatrix();
		osnova();
	glPopMatrix();

	//Ograda
	glPushMatrix();
		ograda();
	glPopMatrix();

	//Igrac
	glPushMatrix();
		igrac();
	glPopMatrix();

	glutSwapBuffers();
}
