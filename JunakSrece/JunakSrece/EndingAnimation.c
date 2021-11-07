#include "EndingAnimation.h"

void ending_animation(int tp, double tq) {

	//iscrtava vesticu i kasnije povlaci sa scene
	glPushMatrix();
	if (tp >= 400 && tp < 425)
		glTranslatef(60, 0 - tq * 7, 0);
	else if (tp < 400)glTranslatef(60, 0, 0);
	final_boss();
	glPopMatrix();

	//iscrtava magicnu vesticiju zvezdu dva puta
	glPushMatrix();
	if ((tp > 301 && tp < 325) || (tp >= 350 && tp < 375))
		glTranslatef(65, 1, 0 - tq * 5);
	star();
	glPopMatrix();

	//animira stvaranje kante
	if (tp >= 332) {

		//kreira kantu za smece
		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(65, 0.7, -5);

		if (tp < 350)
			glScalef(1, 10 * tq, 1);
		else glScalef(1, 10, 1);

		glRotatef(90, -1, 0, 0);
		glutSolidTorus(0.1, 0.75, 30, 30);
		glPopMatrix();

		//Poklopac od kante
		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(64.5, 0.7, -3.5);
		glRotatef(100, -1, 0, 0);
		glRotatef(-38, 1, 0, 0);
		if (tp < 350)
			glScalef(1, 0.1 * tq, 1);
		else glScalef(1, 0.1, 1);
		glutSolidSphere(1, 30, 30);
		glPopMatrix();
	}

	//Postavlja Junaka srece u kantu
	if (tp >= 375) {
		glPushMatrix();
		glTranslatef(64.8, 0.2, -6);
		glScalef(0.01, 0.08, 0.07);
		bold_and_brash();
		glPopMatrix();
	}

	//Pravi portal
	if (tp > 390) {
		glPushMatrix();
		glColor3f(0.2, 0.75, 1);
		glTranslatef(65, 0.4, 0);
		glScalef(1.5, 0.3, 1.5);
		glutSolidSphere(1, 30, 30);
		glPopMatrix();
	}
}