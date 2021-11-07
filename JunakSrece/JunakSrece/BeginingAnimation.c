#include "BeginingAnimation.h"

int i = 0;

//Iscrtaava zidove i pod prostorije u pocetnoj animaciji
static void room() {

	//desni zid
	glPushMatrix();
	//glColor3f(1,1,1);
	glTranslatef(-5, 10, 5);
	glScalef(3, 1, 0.01);
	glutSolidCube(20);
	glPopMatrix();
	//levi zid
	glPushMatrix();
	//glColor3f(1,1,1);
	glTranslatef(-5, 10, -10);
	glScalef(3, 1, 0.01);
	glutSolidCube(20);
	glPopMatrix();
	//zadnji zid
	glPushMatrix();
	//glColor3f(1,1,1);
	glTranslatef(5, 10, 0);
	glScalef(0.01, 1, 3);
	glutSolidCube(20);
	glPopMatrix();
	//dno
	glPushMatrix();
	glColor3f(0.368, 0.236, 0.036);
	glScalef(3, 0.1, 3);
	glutSolidCube(10);
	glPopMatrix();

}
// Iscrtava ram slike
static void slika() {

	glPushMatrix();
	glColor3f(0.6, 0.2, 0);
	glTranslatef(-3, 7.4, -2);
	glScalef(0.025, 2.3, 1.7);
	glutSolidCube(2);
	glPopMatrix();

}
// Iscrtava stubove
static void stubovi() {
	//levi stub
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(-1, 2, -5.5);
	glScalef(1, 3, 1);
	glutSolidCube(1);
	glPopMatrix();
	//desni stub
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(-1, 2, 0.5);
	glScalef(1, 3, 1);
	glutSolidCube(1);
	glPopMatrix();
	//prednja traka
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(-1, 2, -2.5);
	glScalef(0.2, 0.2, 5);
	glutSolidCube(1);
	glPopMatrix();
	//leva traka
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(2, 2, -5.5);
	glScalef(5, 0.2, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	//desna traka
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(2, 2, 0.5);
	glScalef(5, 0.2, 0.2);
	glutSolidCube(1);
	glPopMatrix();
}
// Iscrtava portal koji kasnije pravi vestica
static void portal() {

	glPushMatrix();
	glColor3f(0.2, 0.75, 1);
	glTranslatef(-4, 3, 5);
	glRotatef(90, 0, 1, 0);
	glScalef(0.2, 3, 2);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

}
// Menjanje boje zidova i isrtavanje portala 
void story(int tp, double tq) {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-30, 14, 0, 0, 1, 0, 0, 1, 0);

	glPushMatrix();
	if (tp < 100)
		glColor3f(0.612, 0.612, 1);
	else {
		i = tp % 20;
		if (i <= 10)
			glColor3f(1, 0, 0);
		else glColor3f(0, 0, 1);
	}
	room();
	glPopMatrix();

	glPushMatrix();
	slika();
	stubovi();

	if (tp > 100)
		portal();
	glPopMatrix();

	//crta sliku dok ne bude ukradena
	if (tp < 75) {
		glPushMatrix();
		glTranslatef(-4, 5.5, -3.5);
		glScalef(0.01, 0.117, 0.13);
		bold_and_brash();
		glPopMatrix();
	}

	//leva kugla na stubu
	glPushMatrix();
	glColor3f(1, 0.2, 0.2);
	glTranslatef(-1, 4.15, -5.5);
	glutSolidSphere(0.65, 30, 30);
	glPopMatrix();

	//desna kugla na stubu
	glPushMatrix();
	glColor3f(1, 0.2, 0.2);
	if (tp > 150)
		glTranslatef(-1 - 4 * tq, 4.15 - 2 * tq, 0.5 + 6 * tq);
	else
		glTranslatef(-1, 4.15, 0.5);
	if (tp > 140) {
		glRotatef(180, 0, 1, 0);
		player_look();
	}
	else glutSolidSphere(0.65, 30, 30);
	glPopMatrix();

	//vestica
	if (tp < 130) {
		glPushMatrix();
		if (tp < 50)
			glTranslatef(-25 + 15 * tq, 1, -2.5);
		else if (tp > 100 && tp < 130)
			glTranslatef(-10, 1, -2.5 + 10 * tq);
		else
			glTranslatef(-10, 1, -2.5);
		final_boss();
		glPopMatrix();
	}

	//zvezda koja krade sliku
	glPushMatrix();
	if (tp < 75 && tp > 50)
		glTranslatef(-5, 2 + 6 * tq, -2.5);
	star();
	glPopMatrix();

	//zvezda koja pravi portal
	glPushMatrix();
	if (tp >= 75 && tp < 100)
		glTranslatef(-5, 2.5, -2.5 + 7 * tq);
	glRotatef(90, 0, 1, 0);
	star();
	glPopMatrix();

}