#include <stdlib.h>
#include <math.h>

#ifdef __linux__ 
#include <GL/glut.h>
#elif _WIN32
#include <glut.h>
#endif

#include <stdio.h>
#include <time.h>

static void final_boss(){

//telo
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(5,1,0);
		glScalef(1,1,0.75);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(1, 1.5, 30, 30);
	glPopMatrix();

//glava
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(5,2.3,0);
		glutSolidSphere(0.4,40,40);
	glPopMatrix();

//sesir
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(5, 2.6, 0);
		glRotatef(-90,1,0,0);
		glutSolidCone(0.4, 1.5, 40, 40);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(5, 2.6, 0);
		glScalef(1, 0.1, 1);
		glutSolidSphere(1, 30, 30);
	glPopMatrix();

//senka
	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glTranslatef(5,0.35,0);
		glScalef(1,0.1,1);
		glutSolidSphere(0.75, 30, 30);
	glPopMatrix();

}
static void bullet_look(){

	glPushMatrix();
		glColor3f(0,0,0);
		glScalef(0.1, 1, 1);
		glutSolidSphere(0.2,30,30);
	glPopMatrix();
}
static void star(){

	glPushMatrix();
		glColor3f(1,1,0);
		//glScalef(0.3, 0.3, 0.3);
		glutSolidCube(0.25);
	glPopMatrix();

	//gornji siljak
	glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(0, 0.15, 0);
		glRotatef(90, -1, 0, 0);
		glutSolidCone(0.15, 0.3, 20, 20);
	glPopMatrix();

//donji siljak
	glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(0, -0.15, 0);
		glRotatef(90, 1, 0, 0);
		glutSolidCone(0.15, 0.3, 20, 20);
	glPopMatrix();

//desni
	glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(0, 0, 0.15);
		glutSolidCone(0.15, 0.3, 20, 20);
	glPopMatrix();

//levi
	glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(0, 0, -0.15);
		glRotatef(180, 1, 0, 0);
		glutSolidCone(0.15, 0.3, 20, 20);
	glPopMatrix();

}
static void wall_of_death(){

	for(int i=0; i<10; i++){
		glPushMatrix();
			glTranslatef(1*i,0,0);
			glRotatef(180,0,1,0);
			glutSolidCone(0.5, 1, 30, 30);
		glPopMatrix();
	}
}
static void player_look(){

glColor3f(1, 0.2, 0.2);

//glava i telo
	glPushMatrix();
		glTranslatef(0, 0.3, 0);
		glutSolidSphere(0.65, 30, 30);
	glPopMatrix();
//desno uvo
	glPushMatrix();
		glTranslatef(0, 0.8, 0.3);
		glRotatef(-90,1,0,0);
		glutSolidCone(0.2, 0.8, 30, 30);
	glPopMatrix();
//levo uvo
	glPushMatrix();
		glTranslatef(0, 0.8, -0.3);
		glRotatef(-90,1,0,0);
		glutSolidCone(0.2, 0.8, 30, 30);
	glPopMatrix();
//desno oko
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0.35, 0.7, 0.3);
		glutSolidSphere(0.1, 30, 30);
	glPopMatrix();
//levo oko
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0.35, 0.7, -0.3);
		glutSolidSphere(0.1, 30, 30);
	glPopMatrix();

}