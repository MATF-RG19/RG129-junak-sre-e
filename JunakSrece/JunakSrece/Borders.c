#include "Borders.h"

//Osnova po kojoj se igrac i neprijatelji krecu
void osnova() {

	glPushMatrix();
	glColor3f(0.888, 0.736, 0.54);
	glScalef(500, 0.2, 20);
	glTranslatef(0.498, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
}
//Iscrtavanje ograde za podlogu kroz koju igrac ne moze da prodje
void ograda() {

	int boja = 0;

	for (int i = 0; i < 500; i += 1, boja++) {
		glPushMatrix();
		if (boja < 5)
			glColor3f(0.7, 0.2, 0);
		else {
			glColor3f(0, 0.6, 0.2);
			boja = 0;
		}
		glTranslatef(i, 0.5, -10);
		glutSolidCube(1);
		glPopMatrix();
	}

	boja = 0;

	for (int i = 0; i < 500; i += 1, boja++) {
		glPushMatrix();
		if (boja < 5)
			glColor3f(0.7, 0.2, 0);
		else {
			glColor3f(0, 0.6, 0.2);
			boja = 0;
		}
		glTranslatef(i, 0.5, 10);
		glutSolidCube(1);
		glPopMatrix();
	}

	for (int i = -10; i < 11; i += 1) {
		glPushMatrix();
		glColor3f(0.7, 0.2, 0);
		glTranslatef(-1, 0.5, i);
		glutSolidCube(1);
		glPopMatrix();
	}

	for (int i = -10; i < 11; i += 1) {
		glPushMatrix();
		glColor3f(0.7, 0.2, 0);
		glTranslatef(-500, 0.5, i);
		glutSolidCube(1);
		glPopMatrix();
	}
}
//Prva granica
void border1() {

	glPushMatrix();
	glColor3f(0.476, 0.544, 0.612);
	glTranslatef(20, 0.7, 0);
	glScalef(2, 4, 22);
	glutSolidCube(1);
	glPopMatrix();
}