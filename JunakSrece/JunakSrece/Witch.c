#include "Witch.h"

void final_boss() {

	//telo
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(5, 1, 0);
	glScalef(1, 1, 0.75);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1, 1.5, 30, 30);
	glPopMatrix();

	//glava
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(5, 2.3, 0);
	glutSolidSphere(0.4, 40, 40);
	glPopMatrix();

	//sesir
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(5, 2.6, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.4, 1.5, 40, 40);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(5, 2.6, 0);
	glScalef(1, 0.1, 1);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	//senka
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslatef(5, 0.35, 0);
	glScalef(1, 0.1, 1);
	glutSolidSphere(0.75, 30, 30);
	glPopMatrix();

}
void star() {

	glPushMatrix();
	glColor3f(1, 1, 0);
	//glScalef(0.3, 0.3, 0.3);
	glutSolidCube(0.25);
	glPopMatrix();

	//gornji siljak
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, 0.15, 0);
	glRotatef(90, -1, 0, 0);
	glutSolidCone(0.15, 0.3, 20, 20);
	glPopMatrix();

	//donji siljak
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, -0.15, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(0.15, 0.3, 20, 20);
	glPopMatrix();

	//desni
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, 0, 0.15);
	glutSolidCone(0.15, 0.3, 20, 20);
	glPopMatrix();

	//levi
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, 0, -0.15);
	glRotatef(180, 1, 0, 0);
	glutSolidCone(0.15, 0.3, 20, 20);
	glPopMatrix();

}
