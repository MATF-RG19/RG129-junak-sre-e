#include <stdlib.h>
#include <math.h>

#ifdef __linux__ 
#include <GL/glut.h>
#elif _WIN32
#include <glut.h>
#endif

#include <stdio.h>
#include <time.h>

double z=1;

static void bold_and_brash(){
	/*
35 11, 12, 13, 14,
34 10, 11, 11, 12, 13, 14, 15
33 9 10 11 12 13 14 15 16
32 8 9 10 11 12 13 14 15 16
31 7 8 9 10 11 12 13 14 15 16
30 7 8 9 10 11 12 13 14 15
29 5 6 7 8 9 10 11 12 13 14 15
28 4 5 6 7 8 9 10 11 12 13 14
27 3 4 5 6 7 8 9 10 11 12 13 14 15

26 2 3 4 5 6   10 11 12 13 14 15 16
25 1 2 3 4 5   11 12 13 14 15 16 17
24 1 2 3 4     12 13 14 15 16 17 18
23 2 3         12 13 14 15 16 17 18 19
22 11 12 13 14 15 16 17 18 19
21 11 12 13 14 15 16 17 18 19 20
20 11 12 13 14 15 16 17 18 19 20
19 11 12 13 14 15 16 17 18 19 20
18 11 12 13 14 15 16 17 18 19 20
17 10 11 12 13 14 15 16 17 18 19 20
16 9 10 11 12 13 14 15 16 17 18 19 20 21
15 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22
14 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
13 11 12 13 14 15 16 17    19 20 21 22
12 10 11 12 13 14 15 16    20 21
11 9 10 11 12 13 14 15 16 
10 8 9 10 11 12 13 14 15 16
9 7 8 9 10    14 15 16 17
8 6 7 8 9     15 16 17
7 6 7 8       15 16 17 18
6 5 6 7 8     15 16 17 18
5 5 6 7 8     16 17 18
4 5 6 7 8 9   16 17 18 19
3 5 6 7 8 9   16 17 18 19
2 5 6 7 8 9   16 17 18 19 20
1 6 7 8       17 18 19
*/
//red 35
	for(int i=11; i<=14; i++){
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0,35,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 34
	for(int i=10; i<=15; i++){
	glPushMatrix();
		if(i == 10 || i == 15)
			glColor3f(0,0,0);
		else	glColor3f(0,1,0);
		glTranslatef(0,34,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 33
	for(int i=9; i<=16; i++){
	glPushMatrix();
		if(i==9 || i==16)
			glColor3f(0,0,0);
		else	glColor3f(0,1,0);
		glTranslatef(0,33,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 32
	for(int i=8; i<=16; i++){
	glPushMatrix();
		if(i==8 || i==16)
			glColor3f(0,0,0);
		else	glColor3f(0,1,0);
		glTranslatef(0,32,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 31
	for(int i=7; i<=16; i++){
	glPushMatrix();
		if(i == 7 || i == 16)
			glColor3f(0,0,0);
		else if(i == 10 || i == 11)
			glColor3f(1,1,1);
		else	glColor3f(0,1,0);
		glTranslatef(0,31,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 30
	for(int i=7; i<=15; i++){
	glPushMatrix();
		if(i==7 || i == 15 || i==10)
			glColor3f(0,0,0);
		else if(i==9 || i ==11) glColor3f(1,1,1);
		else glColor3f(0,1,0);
		glTranslatef(0,30,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 29
	for(int i=5; i<=15; i++){
	glPushMatrix();
		if(i == 5 || i == 15 || i ==10 || i==6)
			glColor3f(0,0,0);
		else if(i == 9 || i==11) 
			glColor3f(1,1,1);
		else glColor3f(0,1,0);
		glTranslatef(0,29,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 28
	for(int i=4; i<=14; i++){
	glPushMatrix();
		if(i==4 || i==14)
			glColor3f(0,0,0);
		else if(i==10)
			glColor3f(1,1,1);
		else
			glColor3f(0,1,0);
		glTranslatef(0,28,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 27
	for(int i=3; i<=15; i++){
	glPushMatrix();
		if(i==3 || i==15 || i==7 || i==8 || i==9)
			glColor3f(0,0,0);
		else glColor3f(0,1,0);
		glTranslatef(0,27,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 26
	for(int i=2; i<=6; i++){
	glPushMatrix();
		if(i== 2 || i==6)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,26,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=10; i<=16; i++){
	glPushMatrix();
		if(i==10 || i==16)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,26,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 25
	for(int i=1; i<=5; i++){
	glPushMatrix();
		if(i==1 || i==5)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,25,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=11; i<=17; i++){
	glPushMatrix();
		if(i==11 || i==17 || i==16)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,25,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 24
	for(int i=1; i<=4; i++){
	glPushMatrix();
		if(i==1 || i == 4)
			glColor3f(0,0,0);
		else glColor3f(0,1,0);
		glTranslatef(0,24,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=12; i<=18; i++){
	glPushMatrix();
		if(i==12 || i==18 || i==17)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,24,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 23
	for(int i=2; i<=3; i++){
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0,23,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=12; i<=19; i++){
	glPushMatrix();
		if(i==12 || i==19 || i==18)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,23,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 22
	for(int i=11; i<=19; i++){
	glPushMatrix();
		if(i==11 || i==12 || i==13 || i==19)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,22,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 21
	for(int i=11; i<=20; i++){
	glPushMatrix();
		if(i==11 || i==20 || i==13 || i==16 || i==19)
			glColor3f(0,0,0);
		else 
			glColor3f(0,1,0);
		glTranslatef(0,21,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 20
	for(int i=11; i<=20; i++){
	glPushMatrix();
		if(i==11 || i==13 || i==17 || i==20)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,20,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 19
	for(int i=11; i<=20; i++){
	glPushMatrix();
		if(i==11 || i==13 || i==17 || i==20)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,19,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 18
	for(int i=11; i<=20; i++){
	glPushMatrix();
		if(i==11 || i==13 || i==20 || i==18)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,18,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 17
	for(int i=10; i<=20; i++){
	glPushMatrix();
		if(i==10 || i==11 || i==13 || i==18 || i==20)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,17,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 16
	for(int i=9; i<=21; i++){
	glPushMatrix();
		if(i==9 || i==13 || i==18 || i==21 || i==20)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,16,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 15
	for(int i=8; i<=22; i++){
	glPushMatrix();
		if(i==8 || i==12 || i==18 || i==22)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,15,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 14
	for(int i=9; i<=23; i++){
	glPushMatrix();
		if(i==9 || i==10 || i==11 || i==12 || i==18 || i==23)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,14,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 13
	for(int i=11; i<=17; i++){
	glPushMatrix();
		if(i==11 || i==17)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,13,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=19; i<=22; i++){
	glPushMatrix();
		if(i==19 || i==22)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,13,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 12
	for(int i=10; i<=16; i++){
	glPushMatrix();
		if(i==10 || i==16)
		glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,12,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=20; i<=21; i++){
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0,12,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 11
	for(int i=9; i<=16; i++){
	glPushMatrix();
		if(i==9 || i==16)
		glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,11,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 10
	for(int i=8; i<=16; i++){
	glPushMatrix();
		if(i==8 || i==16 || i==11 || i==12 || i==13)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,10,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 9 
	for(int i=7; i<=10; i++){
	glPushMatrix();
		if(i==7 || i==10)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,9,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=14; i<=17; i++){
	glPushMatrix();
		if(i==14 || i==17)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,9,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 8 
	for(int i=6; i<=9; i++){
	glPushMatrix();
		if(i==6 || i==9)
			glColor3f(0,0,0);
		else 
			glColor3f(0,1,0);
		glTranslatef(0,8,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=15; i<=17; i++){
	glPushMatrix();
		if(i==15 || i==17)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,8,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 7 
	for(int i=6; i<=8; i++){
	glPushMatrix();
		if(i==6 || i==8)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,7,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=15; i<=18; i++){
	glPushMatrix();
		if(i==15 || i==18)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,7,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 6 
	for(int i=5; i<=8; i++){
	glPushMatrix();
		if(i==5 || i==8)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,6,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=15; i<=18; i++){
	glPushMatrix();
		if(i==15 || i==18)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,6,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 5 
	for(int i=5; i<=8; i++){
	glPushMatrix();
		if(i==5 || i==8)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,5,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=16; i<=18; i++){
	glPushMatrix();
		if(i==16 || i==18)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,5,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 4 
	for(int i=5; i<=9; i++){
	glPushMatrix();
		if(i==5 || i==9)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,4,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=16; i<=19; i++){
	glPushMatrix();
		if(i==16 || i==19)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,4,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 3 
	for(int i=5; i<=9; i++){
	glPushMatrix();
		if(i==5 || i==9)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,3,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=16; i<=19; i++){
	glPushMatrix();
		if(i==16 || i==19)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,3,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 2 
	for(int i=5; i<=9; i++){
	glPushMatrix();
		if(i==5 || i==9)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,2,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=16; i<=20; i++){
	glPushMatrix();
		if(i==16 || i==20)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glTranslatef(0,2,i);
		glutSolidCube(z);
	glPopMatrix();
	}
//red 1
	for(int i=6; i<=8; i++){
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0,1,i);
		glutSolidCube(z);
	glPopMatrix();
	}
	for(int i=17; i<=19; i++){
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0,1,i);
		glutSolidCube(z);
	glPopMatrix();
	}
}