#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

int i=0;

static void room(){

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
static void slika(){

	glPushMatrix();
		glColor3f(0.6, 0.2, 0);
		glTranslatef(-3, 7.4, -2);
		glScalef(0.025, 2.3, 1.7);
		glutSolidCube(2);
	glPopMatrix();

}
static void stubovi(){
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
static void portal(){

	glPushMatrix();
		glColor3f(0.2, 0.75, 1);
		glTranslatef(-4, 3, 5);
		glRotatef(90,0,1,0);
		glScalef(0.2, 3, 2);
		glutSolidSphere(1, 30, 30);
	glPopMatrix();

}
static void story(int tp){

	glPushMatrix();
		if(tp < 100)
			glColor3f(0.612, 0.612, 1);
		else {
			i = tp%20;
			if(i<=10)
				glColor3f(1,0,0);
			else glColor3f(0,0,1);
		}
		room();
	glPopMatrix();

	glPushMatrix();
		slika();
		stubovi();

		if(tp > 100)
			portal();
	glPopMatrix();

}
