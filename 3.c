#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 20

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);

//a1,a2,a3 su koordinate igraca
double a1=0,a2=0.5,a3=0;

//w, a su parametri za pomeraj igraca
double w=0,a=0;

//Parametar za pucanj igraca koriscenj u funkciji shoot
double k=0;

//pomocna promenljiva kako bi se znalo da li se vrsi kretanje levo/desno ili napred/nazad
//shoot_key - promenljiva koja poziva funkciju shoot kad ima vrednost 1
int pick_key=0, move_player=0, shoot_key=0;

//Nizovi za koordinate neprijatelja
double e1[10];
double e3[10];

//Niz koji oznacava da li je neprijatelj ubijen ili ne i istovremeno sluzi kao parametar za nestanak neprijatelja
int killed[10];

//Parametar koji oznacava koliko zivota igrac ima
int health_parameter = 3;

//Ograde koje onemgucavaju igracu da prodje dok ne unisti odredjen deo neprijatelja
int door1 = 0;

//Pomocni parameter za animaciju igracevog pucnja 
double player_parameter=0; 

//Pomocni parameter za animaciju kretanja neprijatelja
int enemy_parameter=0;

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Junak srece");

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
	

	glClearColor(0.153, 0.153, 0.255, 0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LINE_SMOOTH);

	glutMainLoop();	

	return 0;
}

/* Program reaguje na tastere:

	esc
		-izlazi iz programa

	w/W
		-pomera igraca napred

	a/A
		-pomera igraca ulevo

	d/D
		-pomera igraca udesno

	s/S
		-pomera igraca unazad

	k/K
		-igrac puca
*/
static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
	case 27:
		exit(0);
		break;
	case 'w':
	case 'W':
		pick_key=0;
		w = 0.3;
		move_player = 1;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		pick_key = 1;
		a = -0.3;
		move_player = 1;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		pick_key = 1;
		a = 0.3;
		move_player = 1;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		pick_key = 0;
		w = -0.3;
		move_player = 1;
		glutPostRedisplay();
		break;
	case 'k':
	case 'K':
		shoot_key=1;
		glutPostRedisplay();
		
		break;
	}
}
static void init_lights()
{
    GLfloat light_position[] = { -5, 15, 0, 0};
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
static void on_reshape(int width, int height){

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,(float) width/height, 1, 1000);

}

//Za sada timer funkcija nema posebnu ulogu
static void on_timer(int id){

	if(id != TIMER_ID){
		return;
	}

	glutPostRedisplay();

}
static void osnova(){

	glPushMatrix();

		glColor3f(0.7, 0.7, 0.7);
		glScalef(700, 0.2, 20);
		glTranslatef(0.498,0,0);
		glutSolidCube(1);
	

	glPopMatrix();	
}
//Iscrtavanje ograde za podlogu kroz koju igrac ne moze da prodje
static void ograda(){

	int boja=0;

	for(int i=0; i<700; i+= 1, boja++){
		glPushMatrix();
		if (boja < 5)
			glColor3f(0.7, 0.2, 0);
		else{
			glColor3f(0, 0.6, 0.2);
			boja = 0;
		}
		glTranslatef(i, 0.5, -10);
		glutSolidCube(1);
		glPopMatrix();
	}

	boja=0;

	for(int i=0; i<700; i+= 1, boja++){
		glPushMatrix();
		if (boja < 5)
			glColor3f(0.7, 0.2, 0);
		else{
			glColor3f(0, 0.6, 0.2);
			boja = 0;
		}
		glTranslatef(i, 0.5, 10);
		glutSolidCube(1);
		glPopMatrix();
	}

	for(int i=-10; i<11; i+= 1){
		glPushMatrix();
		glColor3f(0.7, 0.2, 0);
		glTranslatef(-1, 0.5, i);
		glutSolidCube(1);
		glPopMatrix();
	}

	for(int i=-10; i<11; i+= 1){
		glPushMatrix();
		glColor3f(0.7, 0.2, 0);
		glTranslatef(-700, 0.5, i);
		glutSolidCube(1);
		glPopMatrix();
	}

	
}
//Prva granica
static void border1(){

	glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(20, 0.7, 0);
		glScalef(2,4,22);
		glutSolidCube(1);
	glPopMatrix();
}
//Funkcija koja crta srca koja oznacavaju zivote ostale igracu
static void heart(){

	glPushMatrix();
		glColor3f(1,0,0);
		glScalef(0.01, 0.2, 0.2);
		glutSolidSphere(1, 30, 30);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(0,0,0.2);
		glScalef(0.01, 0.2, 0.2);
		glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(-0.01, -0.08, 0.1);
		glRotatef(90, 1, 0, 0);
		glScalef(0.003, 0.3, 0.2);
		glutSolidCone(1, 2, 30, 30);
	glPopMatrix();
	
}
//Restartovanje igrice nagon gubitka svih zivota
static void game_over(){

	a1=0;
	a3=0;
	for(int i=0; i<10; i++)
		killed[i] = 0;
	health_parameter = 3;
	door1 =0;

}
//Pravljenje health bara
static void health_bar(){

	if(health_parameter == 0)
		game_over();

	for(int i=0; i<health_parameter; i++){
		glPushMatrix();
			glTranslatef(-10+a1, 9, 2.5+a3 - 0.7*i);
			heart();
		glPopMatrix();
	}	
}
//Funkcija koja proverava da li je protivnih pogodjen
static void hit_or_miss(double p1, double p3){

	for(int i=0; i<10; i++){

		if(killed[i] == 3)
			continue;

		if (e1[i]+0.5 >= p1 && e1[i]-0.5 <= p1 && e3[i]+0.5 >= p3 && e3[i]-0.5 <= p3){
			killed[i] = 1;
			shoot_key = 0;
		}
	}
}
static void shoot(){

	player_parameter++;

	k=player_parameter/8.0;

	double p1, p3;

	glPushMatrix();

		glColor3f(0.2, 0.3, 0.8);
		glTranslatef(p1 = a1+6*k, 1, p3 = a3);
		glScalef(0.1, 0.1, 0.1);
		glutSolidCube(1);

	glPopMatrix();
	glutPostRedisplay();

	hit_or_miss(p1, p3);

	if(player_parameter >= 8){
		player_parameter =0;
		shoot_key = 0;
		//animation_ongoing =0;
	}


}
//Obrada sudara s neprijateljem, rezultat je da se igrac resetuje na pocetnu poziciju s jednim zivotom manje
static void collision(){

	for(int i=0; i<10; i++){
		
		if(killed[i] != 0)
			continue;

		if(e1[i]+0.5 >= a1-0.5 && e1[i]-0.5 <= a1-0.5 && e3[i]+1 >= a3 && e3[i]-1 <= a3){
			a1=0;
			a3=0;
			health_parameter--;
		}
		if(e1[i]+0.5 >= a1+0.5 && e1[i]-0.5 <= a1+0.5 && e3[i]+1 >= a3 && e3[i]-1 <= a3){
			a1=0;
			a3=0;
			health_parameter--;
		}
	}

}

static void igrac(){

	glPushMatrix();

		glColor3f(0.804, 0.522, 0.247);

//Prvi if sluzi da pomeri igraca samo kad je pritisnut neki od tastera za pomeranje igraca

		if (move_player == 1){

			if(pick_key == 0)
				a1 += w;
			else 	
				a3 += a;

	// onemogucava igracu da se krece van granica ograde i privremenih granica
			if (a3 < -9)
				a3 = -9;
			if (a3 > 9)
				a3 = 9;	
			if (a1 < 0)
				a1 =0;
			if (a1 > 699)
				a1 = 699;
			if(door1 < 10 && a1 > 18.5)
				a1 =18.5;

			glTranslatef(a1 = a1 + 0, a2=0.7, a3 += 0);
			move_player =0;
		}
		else glTranslatef(a1, a2, a3);

	// onemogucava igracu da prolazi kroz neprijatelje
		collision();
		
		glutSolidCube(1);


	glPopMatrix();

}
static void enemy(){

	enemy_parameter++;	

	if(door1 != 10){
		//Iscrtavanje pocetnih neprijatelja s leve strane
		for(int i=0; i<5; i++){
		
			if(killed[i] == 3)
				continue;
	
			glPushMatrix();
	
				glColor3f(0, 0.8, 0.4);
				glTranslatef(e1[i]=7+i, 0.7, e3[i]=-5 + i + 3*sin(enemy_parameter/20.0));

				if(killed[i] > 0){
					glutSolidCube(sin(killed[i]/20.0));
					killed[i]++;
				}
				if(killed[i] == 0)
					glutSolidCube(1);
				
			glPopMatrix();

			glutPostRedisplay();			
		}
		//Iscrtavanje pocetnih neprijatelja s desne strane
		for(int i=5; i<10; i++){

			if(killed[i] == 3)
				continue;
			

			glPushMatrix();

				glColor3f(0, 0.8, 0.4);
				glTranslatef(e1[i]=7+i%5, 0.7, e3[i]=5 - i%5 + 3*sin(enemy_parameter/20.0));
	
				if(killed[i] > 0){
				
					glutSolidCube(sin(killed[i]/20.0));
					killed[i]++;
				}
				if(killed[i] == 0)
					glutSolidCube(1);
		
			glutPostRedisplay();
	
			glPopMatrix();
		}
		//Racunanje da li su svi neprijatelji u prvom delu pogodjeni kako bismo otkljucali vrata
		door1=0;
		for(int j=0;j<10;j++)
			if(killed[j] == 3)
				door1++;
	}
}
static void on_display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	init_lights();

	// Podesavanje kamere i tacke gledista tako da prati kretanje igraca
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-20+a1, 10, 0+a3, 0+a1, 3, 0+a3, 0, 1, 0);

	//Osnova
	glPushMatrix();
		osnova();
	glPopMatrix();

	//Ograda
	glPushMatrix();
		ograda();
	glPopMatrix();

	//Neprijatelji
	glPushMatrix();
		enemy();
	glPopMatrix();

	//Igrac
	glPushMatrix();
		igrac();
	glPopMatrix();

	//Health bar
	glPushMatrix();
		health_bar();
	glPopMatrix();

	//Granica1
	if(door1 < 10){
		glPushMatrix();
			border1();
		glPopMatrix();
	}

	if(shoot_key == 1){
		shoot();
	}

	glutSwapBuffers();
}
