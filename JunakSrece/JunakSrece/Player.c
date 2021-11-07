#include "Player.h"

void player_look() {

	glColor3f(1, 0.2, 0.2);

	//glava i telo
	glPushMatrix();
	glTranslatef(0, 0.3, 0);
	glutSolidSphere(0.65, 30, 30);
	glPopMatrix();
	//desno uvo
	glPushMatrix();
	glTranslatef(0, 0.8, 0.3);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.2, 0.8, 30, 30);
	glPopMatrix();
	//levo uvo
	glPushMatrix();
	glTranslatef(0, 0.8, -0.3);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.2, 0.8, 30, 30);
	glPopMatrix();
	//desno oko
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.35, 0.7, 0.3);
	glutSolidSphere(0.1, 30, 30);
	glPopMatrix();
	//levo oko
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.35, 0.7, -0.3);
	glutSolidSphere(0.1, 30, 30);
	glPopMatrix();

}
void bullet_look() {

	glPushMatrix();
	glColor3f(0, 0, 0);
	glScalef(0.1, 1, 1);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();
}