#include "EnemyBush.h"

//Parametri koji sluze za proveru da li je igrac pogodjen od strane neprijatelja ili ne
double xkor, zkor;
//Pomocni parameter za animaciju kretanja pucnja
int counter = 50;
//Parametar koji se koristi za kretanje neprijateljevog pucnja
double movement_counter = 0;


//Proverava da li je igrac pogodjen od strane neprijatelja broj 2
static void bush_hit_or_miss(double player_x, double player_z) {

	if (player_x + 0.5 >= xkor && player_x - 0.5 <= xkor && player_z + 0.5 >= zkor && player_z - 0.5 <= zkor) {
		player_x = 15;
		player_z = 0;
		damage++;
	}
}
void enemyBush(double player_x, double player_z) {
	damage= 0;
	//Naredna tri for-a i dva objekta su zbunje(neprijatelji) iz drugog sektora koji ne mogu biti ubijeni
	for (int i = 0; i < 3; i++) {

		glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(20 + i * 12, 0.7, -5 + i * 3);
		glRotatef(45, 0, 1, 0);
		bushDesign();
		glPopMatrix();

		glPushMatrix();
		bush_shoot(20 + i * 12, -5 + i * 3, player_x, player_z);
		glPopMatrix();
	}
	for (int i = 0; i < 4; i++) {

		glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(25 + i * 8, 0.7, 8);//7
		glRotatef(45, 0, 1, 0);
		bushDesign();
		glPopMatrix();

		glPushMatrix();
		bush_shoot(25 + i * 8, 7, player_x, player_z);
		glPopMatrix();
	}
	for (int i = 0; i < 4; i++) {

		glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(30 + i * 8, 0.7, -7 + i % 2 * 3);
		glRotatef(45, 0, 1, 0);
		bushDesign();
		glPopMatrix();

		glPushMatrix();
		bush_shoot(30 + i * 8, -7 + i % 2 * 3, player_x, player_z);
		glPopMatrix();
	}
	//Zbun 
	glPushMatrix();
	glColor3f(1, 0.512, 456);
	glTranslatef(26, 0.7, 2);
	glRotatef(45, 0, 1, 0);
	bushDesign();
	glPopMatrix();

	glPushMatrix();
	bush_shoot(26, 2, player_x, player_z);
	glPopMatrix();

	//Drugi zbun
	glPushMatrix();
	glColor3f(1, 0.512, 456);
	glTranslatef(52, 0.7, 3);
	glRotatef(45, 0, 1, 0);
	bushDesign();
	glPopMatrix();

	glPushMatrix();
	bush_shoot(52, 3, player_x, player_z);
	glPopMatrix();
}
//Dizajn izgleda novih neprijatelja
void bushDesign() {

	glPushMatrix();
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-135, 0, 1, 0);
	glutSolidCone(1, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glutSolidCone(1, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glutSolidCone(1, 1.5, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(135, 0, 1, 0);
	glutSolidCone(1, 1.5, 30, 30);
	glPopMatrix();

}

void bush_shoot(int x, int z, double player_x, double player_z) {

	counter++;
	movement_counter = counter % 550;
	
	//Jedan pucanj koji ide x koordinatom nadole
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.8);
	glTranslatef(xkor=x- movement_counter /70.0, 0.7, zkor=z);//x-10*p22/50.0
	glScalef(0.5, 0.1, 0.1);
	glutSolidCube(2);

	bush_hit_or_miss(player_x, player_z);

	glPopMatrix();

	//Pucanj gde se menja z koordina udesno 
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.8);
	glTranslatef(xkor = x, 0.7, zkor = z + movement_counter /100.0);//15*p22/40.0
	glScalef(0.1, 0.1, 0.5);

	//Ovaj if sluzi da se pucanj ne iscrtava kada dodirne levi ili desni zid
	if (zkor > -9.5 && zkor < 9.5) {
		glutSolidCube(2);

		bush_hit_or_miss(player_x, player_z);
	}
	glPopMatrix();

	//Pucanj gde je x koordinata ista a menja se z koordinata (ulevo)
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.8);
	glTranslatef(xkor=x, 0.7, zkor=z- movement_counter /100.0);//zkor=z-15*p22/30.0
	glScalef(0.1, 0.1, 0.5);

	//Ovaj if sluzi da se pucanj ne iscrtava kada dodirne levi ili desni zid
	if (zkor > -9.5 && zkor < 9.5) {
		glutSolidCube(2);

		bush_hit_or_miss(player_x, player_z);
	}
	glPopMatrix();

	//Jedan pucanj koji ide x koordinatom nagore
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.8);
	glTranslatef(xkor = x + movement_counter /100.0, 0.7, zkor=z);//xkor = x + 10*p22/20.0
	glScalef(0.5, 0.1, 0.1);
	glutSolidCube(2);

	bush_hit_or_miss(player_x, player_z);
	glPopMatrix();

	//glutPostRedisplay();
}