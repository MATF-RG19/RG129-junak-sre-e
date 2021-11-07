#include "Key.h"

void key_design() {

	glPushMatrix();
	glTranslatef(5.2, 0.2, 0.2);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.1, 0.4, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5, 0.2, -0.2);
	glRotatef(45, 0, 1, 0);
	glScalef(0.2, 0.1, 1.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5, 0.2, -0.5);
	glRotatef(-45, 0, 1, 0);
	glScalef(0.1, 0.1, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.4, 0.2, -0.85);
	glRotatef(-45, 0, 1, 0);
	glScalef(0.1, 0.1, 0.6);
	glutSolidCube(1);
	glPopMatrix();

}