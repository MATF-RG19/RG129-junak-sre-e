#include <stdlib.h>
#include <math.h>

#ifdef __linux__ 
#include <GL/glut.h>
#elif _WIN32
#include <glut.h>
#endif

#include <stdio.h>
#include "junak_srece.h"
#include "vestica.h"
#include "third.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 30

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void shoot();
static void story(int tp);
static void igrac();

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

//Oba parametra sluze za rotiranje igraca u zavisnosti od toga gde se krece i za navodjenje pravca i smera pucnja igraca
int side=0, strana =0;


/*
enemy_shoot_z 
	- cuva z koordinatu od neprijatelja koji puca 
	kako bi se metak pomerao samo po z osi u datoj 
	poziciji a ne da se pomara zajedno s neprijateljem

enemy_shoot_x
	- isto sto i enemy_shoot_z samo za x koordinatu

enemy_prepare
	- kada je neprijatelju odobreno pucanje postoji krak vremenski persiod 
	koji ga zaustavlja da ne puca odmah i da bi najavio igracu da se pucati
	upravo za to sluzi ovaj niz, kako bi odugovlacila vreme pocetka pucnja

permission
	- promenljiva koja ogranicava maksimalan broj neprijatelja koji moze da puca istovremeno
*/
int enemy_shoot_x[10], enemy_shoot_z[10], permission=0, enemy_prepare[10];

//Parametri koji sluze za proveru da li je igrac pogodjen od strane neprijatelja ili ne
double e_p1, e_p3;

//Parametar koji se koristi za kretanje neprijateljevog pucnja
double p=0;

//Da li je kljuc sakupljen (imaju dva, prvi za zuti kljuc drugi za zeleni)
int key_collected[2];

//Parametri za pocetnu i krajnju animaciju
// tp se povecava a tq racuna 
int tp=0;
double tq=0;

//Parametar za kretanje bodljikavog zida koji se aktivira kada je skupljen zuti kljuc
int key_parameter=0;

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Junak srece");

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
	glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
	

	glClearColor(0.153, 0.153, 0.255, 0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LINE_SMOOTH);

	glutMainLoop();	

	return 0;
}
//funkcija za podesavanje parametara koji se koriste u pocetnoj i krajnjoj animaciji igre
static void on_timer(int id) {

	if (id != TIMER_ID)
		return;
	if (tp < 201 || tp >= 300)
		tp++;
	//else return;

	tq = tp/50.0;

	if(tp > 50 && tp < 75)
		tq = tp%50/25.0;
	if(tp >= 75 && tp < 100)
		tq = tp%75/25.0;
	if(tp >100 && tp < 130)
		tq = tp%100/30.0;
	if(tp > 150 && tp < 175)
		tq = tp%150/25.0;
	if(tp >= 300 && tp <325)
		tq = tp%300/25.0;
	if(tp >= 325 && tp < 350)
		tq = tp%325/25.0;
	if(tp >= 350 && tp < 375)
		tq = tp%350/25.0;
	if(tp >= 400 && tp < 425)
		tq = tp%400/25.0;
	if(tp >= 425 && tp < 475)
		tq = tp%425/50.0;
	if(tp>=475)
		tq=1;

	glutPostRedisplay();

	//if(tp < 201 || tp >= 300)
		glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
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

	p/P
		-precica za drugi nivo

	n/N
		-preskace najavnu spicu

	o/O
		-precica za zavrsnu spicu i kraj
*/
static void on_keyboard(unsigned char key, int x, int y){


	switch(key){
	case 27:
		exit(0);
		break;
	case 'w':
	case 'W':
		pick_key=0;
		w = 0.45;
		move_player = 1;
		strana =0;
		// glutPostRedisplay();
		// glutSwapBuffers();
		break;
	case 'a':
	case 'A':
		pick_key = 1;
		a = -0.45;
		move_player = 1;
		strana = 1;
		//glutPostRedisplay();
		//glutSwapBuffers();
		break;
	case 'd':
	case 'D':
		pick_key = 1;
		a = 0.45;
		move_player = 1;
		strana =2;
		//glutPostRedisplay();
		break;
	case 's':
	case 'S':
		pick_key = 0;
		w = -0.45;
		move_player = 1;
		strana =3;
		//glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		door1=10;
		a1=15;
		a3=0;
		tp=201;
		//glutPostRedisplay();
		break;
	case 'o':
	case 'O':
		door1=10;
		a1=60;
		a3=0;
		tp=301;
		key_collected[1] = 1;
		glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
		break;
	case 'n':
	case 'N':
		tp=201;
		//glutPostRedisplay();
		break;
	}

	if(key == 'k' || key == 'K'){
		side = strana;
		shoot_key=1;
		//glutPostRedisplay();
	}
}
static void init_lights()
{
    GLfloat light_position[] = { -5, 15, 0, 0};
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1 };
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
//Osnova po kojoj se igrac i neprijatelji krecu
static void osnova(){

	glPushMatrix();

		glColor3f(0.888,0.736,0.54);
		glScalef(500, 0.2, 20);
		glTranslatef(0.498,0,0);
		glutSolidCube(1);
	

	glPopMatrix();	
}
//Iscrtavanje ograde za podlogu kroz koju igrac ne moze da prodje
static void ograda(){

	int boja=0;

	for(int i=0; i<500; i+= 1, boja++){
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

	for(int i=0; i<500; i+= 1, boja++){
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
		glTranslatef(-500, 0.5, i);
		glutSolidCube(1);
		glPopMatrix();
	}

//Animacija siljaka s leve strane u drugom nivou
	for(int i=0; i<5; i++){
	glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(20, 0.0, -6-i*0.8);
		glRotatef(90, -1, 0, 0);
		glutSolidCone(0.5,1,30,30);
	glPopMatrix();
	}

	for(int i=0; i<3; i++){
	glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(30, 0.0, -7.5-i*0.8);
		glRotatef(90, -1, 0, 0);
		glutSolidCone(0.5,1,30,30);
	glPopMatrix();
	}	
}
//Prva granica
static void border1(){

	glPushMatrix();
		glColor3f(0.476,0.544,0.612);
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

	for(int i=0; i<2; i++)
		key_collected[i] =0;

}
//Pravljenje health bara
static void health_bar(){

	if(health_parameter == 0)
		game_over();

	for(int i=0; i<health_parameter; i++){
		glPushMatrix();
			glTranslatef(-11+a1, 11.77, 2.2+a3 - 0.7*i);
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

		glColor3f(0.0, 0.0, 0.0);

		//U zavisnosti od parametra side se pucanj krece u razlicite strane
		if(side == 0)
			glTranslatef(p1 = a1+6*k, 0.6, p3 = a3);
		if(side == 1)
			glTranslatef(p1 = a1, 0.6, p3 = a3-6*k);
		if(side == 2)
			glTranslatef(p1 = a1, 0.6, p3 = a3+6*k);
		if(side == 3)
			glTranslatef(p1 = a1-6*k, 0.6, p3 = a3);
		
		glutSolidSphere(0.13,30,30);

	glPopMatrix();
	//glutPostRedisplay();

	hit_or_miss(p1, p3);

	if(player_parameter >= 8){
		player_parameter =0;
		shoot_key = 0;
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
			if (a1 > 500)
				a1 = 500;
			if(door1 < 10 && a1 > 18.5)
				a1 =18.5;
			if(key_collected[1] == 0 && a1 > 60)
				a1 = 60;

	//funkcija koja registruje da li je skupljen zuti kljuc
			if(a1+1 >= 34+4.5 && a1-1 <= 34+4.5 && a3+1 >= 4+0.2 && a3-1 <= 4+0.2)
				key_collected[0] = 1;
	//funkcija koja registruje da li je skupljen zeleni kljuc
			if(a1+1 >= 38+4.5 && a1-1 <= 38+4.5 && a3+1 >= -8+0.2 && a3-1 <= -8+0.2)
				key_collected[1] = 1;


	//kada je igrac skupio zeleni kljuc i presao mesto gde je bila granica krece zavrsna animacija
			if(key_collected[1] == 1 && a1 >60){
				tp = 300; 
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
			}


	//Kolizija s levim siljcima
			if(a1 > 20-0.5 && a1 < 20+0.5 && a3 > -10 && a3 < -5){
				a1=15;
				a3=0;
				health_parameter--;
			}
			if(a1 > 30-0.5 && a1 < 30+0.5 && a3 > -10 && a3 < -7){
				a1=15;
				a3=0;
				health_parameter--;
			}

			glTranslatef(a1 = a1 + 0, a2=0.0, a3 += 0);
			move_player =0;
		}
		else glTranslatef(a1, a2, a3);

	// onemogucava igracu da prolazi kroz neprijatelje
		if(door1 < 10)
			collision();
		
		//U zavisnosti od toga na koju smo se stranu kretali na tu stranu se rotira igrac
		if(strana == 1)
			glRotatef(90, 0, 1, 0);
		if(strana == 2)
			glRotatef(90, 0, -1, 0);
		if(strana == 3)
			glRotatef(180, 0, 1, 0);

	//funkcija za izgled igraca(nalazi se u vestica.h)
		player_look();

	glPopMatrix();
}
//Funkcija koja proverava da li je neprijatelj pogodio igraca
static void enemy_hit_or_miss(){

	if(a1+0.5 >= e_p1 && a1-0.5 <= e_p1 && a3+0.5 >= e_p3 && a3-0.5 <= e_p3){
		a1=0;
		a3=0;
		health_parameter--;
	}
	//glutPostRedisplay();
}
//Neprijatelj puca prvu vrsta pucnja
static void enemy_shoot(int i){

	p=enemy_parameter%8;

	//Zavrsetak iscrtavanja pucnja
	if(p == 7){
		enemy_prepare[i] = 0;
		permission--;
	}
	//ANimacija kretanja pucnja i provera da li je pogodio igraca
	else{
	glPushMatrix();

		glColor3f(0.2, 0.3, 0.8);
		glTranslatef(e_p1 = enemy_shoot_x[i]-6*p/8.0, 1,e_p3 = enemy_shoot_z[i]);
		glScalef(0.1, 0.1, 0.1);
		glutSolidCube(2);

		enemy_hit_or_miss();

	glPopMatrix();

	//glutPostRedisplay();
	}
}
//Funkcija koja iscrtava neprijatelje, pomera ih i poziva funkciju za pucanje neprijatelja
static void enemy(){


	enemy_parameter++;

	srand(enemy_parameter);	
//Dokle god u prvom delu ima prezivelih neprijatelja 
	if(door1 != 10){

		// Iscrtavanje prvih 5 neprijatelja s leve strane
		for(int i=0; i<5; i++){
		
			//Znaci da je neprijatelj ubijen i zavrseno je s njegovim iscrtavanjem
			if(killed[i] == 3)
				continue;
	
			glPushMatrix();

				//Znaci da ce neprijatelj uskoro pucati pa menja boju kako bi upozorio igraca
				if(enemy_prepare[i] > 0 && enemy_prepare[i] < 10){
					enemy_prepare[i]++;
					glColor3f(1,0,0);
				}
				else
					glColor3f(0, 0.8, 0.4);	
	
				glTranslatef(e1[i]=7+i, 0.7, e3[i]=-5 + i + 3*sin(enemy_parameter/20.0));

				//Neprijatelj je pogodjen pa animiramo njegov nestanak
				if(killed[i] > 0){
				
					glutSolidCube(sin(killed[i]/20.0));
					killed[i]++;
					if(enemy_prepare[i] != 0)
						permission--;
				}
				if(killed[i] == 0)
					glutSolidCube(1);
				
			glPopMatrix();

			//Definisemo kada ce neprijatelj moci da puca
			glPushMatrix();
				if (rand()%10 > 7 && permission < 2){
					enemy_prepare[i] = 1;
					permission++;
				}
				//Cuvamo trenutne koordinate neprijatelja kako bismo pucanj kretali pomoci njih
				if(enemy_prepare[i] == 9){
					enemy_shoot_x[i] = e1[i];
					enemy_shoot_z[i] = e3[i];
				}
				//Zavrseno je s upozorenjem za igraca i neprijatelj puca
				if(enemy_prepare[i] == 10){
					enemy_shoot(i);
				}
					
			glPopMatrix();

			//glutPostRedisplay();			
		}
		//Iscrtava 5 neprijatelja s desne strane na isti nacin kao i prosla for petlja
		for(int i=5; i<10; i++){

			if(killed[i] == 3)
				continue;
			

			glPushMatrix();

				if(enemy_prepare[i] > 0 && enemy_prepare[i] < 10){
					enemy_prepare[i]++;
					glColor3f(1,0,0);
				}
				else
					glColor3f(0, 0.8, 0.4);	

				glTranslatef(e1[i]=7+i%5, 0.7, e3[i]=5 - i%5 + 3*sin(enemy_parameter/20.0));
	
				if(killed[i] > 0){
				
					glutSolidCube(sin(killed[i]/20.0));
					killed[i]++;
					if(enemy_prepare[i] != 0)
						permission--;
				}
				if(killed[i] == 0)
					glutSolidCube(1);
			glPopMatrix();


			glPushMatrix();
				if (rand()%10 > 7 && permission < 2){
					enemy_prepare[i] = 1;
					permission++;
				}
				if(enemy_prepare[i] == 9){
					enemy_shoot_x[i] = e1[i];
					enemy_shoot_z[i] = e3[i];
				}
				if(enemy_prepare[i] == 10){
					enemy_shoot(i);
				}
					
			glPopMatrix();

			//glutPostRedisplay();
		}
		//Proverava se da li su svi od prvih 10 neprijatelja unisteni
		door1=0;
		for(int j=0;j<10;j++)
			if(killed[j] == 3)
				door1++;
	}
}
//Dizajn izgleda novih neprijatelja
static void enemy2_design(){

	glPushMatrix();
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-135, 0, 1, 0);
		glutSolidCone(1, 1.5, 30,30);
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glutSolidCone(1, 1.5, 30,30);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-45, 0, 1, 0);
		glutSolidCone(1, 1.5, 30,30);
	glPopMatrix();

	glPushMatrix();
		glRotatef(135, 0, 1, 0);
		glutSolidCone(1, 1.5, 30,30);
	glPopMatrix();

}
//Proverava da li je igrac pogodjen od strane neprijatelja broj 2
static void enemy2_hit_or_miss(){

	if( a1+0.5 >= e_p1 && a1-0.5<=e_p1 && a3+0.5 >= e_p3 && a3-0.5 <= e_p3){
		a1=15;
		a3=0;
		health_parameter--;

	}
	//glutPostRedisplay();
}
static void enemy2_shoot(int x, int z){

	p=enemy_parameter%20;

	//Jedan pucanj koji ide x koordinatom nadole
	glPushMatrix();
		glColor3f(0.2, 0.3, 0.8);
		glTranslatef(e_p1 = x-10*p/20.0, 1,e_p3 = z);
		glScalef(0.5, 0.1, 0.1);
		glutSolidCube(2);

		enemy2_hit_or_miss();
		
	glPopMatrix();

	//Pucanj gde se menja z koordina udesno 
	glPushMatrix();
		glColor3f(0.2, 0.3, 0.8);
		glTranslatef(e_p1 = x, 1,e_p3 = z+15*p/40.0);
		glScalef(0.1, 0.1, 0.5);

		//Ovaj if sluzi da se pucanj ne iscrtava kada dodirne levi ili desni zid
		if(e_p3 > -9.5 && e_p3 < 9.5){
			glutSolidCube(2);

			enemy2_hit_or_miss();
		}
	glPopMatrix();

	//Pucanj gde je x koordinata ista a menja se z koordinata (ulevo)
	glPushMatrix();
		glColor3f(0.2, 0.3, 0.8);
		glTranslatef(e_p1 = x, 1,e_p3 = z-15*p/30.0);
		glScalef(0.1, 0.1, 0.5);

		//Ovaj if sluzi da se pucanj ne iscrtava kada dodirne levi ili desni zid
		if(e_p3 > -9.5 && e_p3 < 9.5){
			glutSolidCube(2);

			enemy2_hit_or_miss();
		}
	glPopMatrix();

	//Jedan pucanj koji ide x koordinatom nagore
	glPushMatrix();
		glColor3f(0.2, 0.3, 0.8);
		glTranslatef(e_p1 = x+10*p/20.0, 1,e_p3 = z);
		glScalef(0.5, 0.1, 0.1);
		glutSolidCube(2);

		enemy2_hit_or_miss();
	glPopMatrix();

	//glutPostRedisplay();
}
static void wall_of_death_collision(){

	if(a1 >= e1[1]-11 && a1 <= e1[1]+10 && a3 >=  e3[0]-1.5 && a3 <= e3[0]+0.5){
		health_parameter--;
		a1=15;
		a3=0;
	}
}

//Drugaciji tip neprijatelja u drugoj zoni
static void enemy2(){

//Naredna tri for-a i dva objekta su zbunje(neprijatelji) iz drugog sektora koji ne mogu biti ubijeni
	for(int i=0; i<3; i++){

		glPushMatrix();
			glColor3f(1, 0.512, 456);
			glTranslatef(20+i*12 , 1, -5+i*3);
			glRotatef(45, 0, 1, 0);
			enemy2_design();
		glPopMatrix();

		glPushMatrix();
			enemy2_shoot(20+i*12, -5+i*3);
		glPopMatrix();
	}
	for(int i=0; i<4; i++){

		glPushMatrix();
			glColor3f(1, 0.512, 456);
			glTranslatef(25+i*8 , 1, 7);
			glRotatef(45, 0, 1, 0);
			enemy2_design();
		glPopMatrix();

		glPushMatrix();
			enemy2_shoot(25+i*8, 7);
		glPopMatrix();
	}
	for(int i=0; i<4; i++){

		glPushMatrix();
			glColor3f(1, 0.512, 456);
			glTranslatef(30+i*8 , 1, -7 + i%2*3);
			glRotatef(45, 0, 1, 0);
			enemy2_design();
		glPopMatrix();

		glPushMatrix();
			enemy2_shoot(30+i*8, -7 + i%2*3);
		glPopMatrix();
	}
//Zbun 
	glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(26 , 1, 2);
		glRotatef(45, 0, 1, 0);
		enemy2_design();
	glPopMatrix();

	glPushMatrix();
		enemy2_shoot(26, 2);
	glPopMatrix();

//Drugi zbun
	glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(52 , 1, 3);
		glRotatef(45, 0, 1, 0);
		enemy2_design();
	glPopMatrix();

	glPushMatrix();
		enemy2_shoot(52, 3);
	glPopMatrix();
	
//Desni zid koji se pomera ako je skupljen zuti kljuc
	for(int i=0; i<2; i++){
		glPushMatrix();
			glColor3f(1, 0.512, 456);
			if(key_collected[0] == 1){

				key_parameter++;

				if(sin(key_parameter/40.0) > 0)
					glTranslatef(e1[i] = 22+i*10, 0.6,e3[i] = 9.5 -sin(key_parameter/40.0)*7);
				else glTranslatef(e1[i] = 22+i*10, 0.6,e3[i] = 9.5 +sin(key_parameter/40.0)*7);
			}
			else glTranslatef(e1[i] = 22+i*10, 0.6, e3[i] = 9.5);
			wall_of_death();
			wall_of_death_collision();
		glPopMatrix();
	}

	//glutPostRedisplay();
}
//oblik kljuca
static void key_shape(){

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
static void on_display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	init_lights();

//Ako je vremenski parametar manji od 200 treba pokrenuti pocetnu animaciju igrice
//inace krecemo s igrom 

	if(tp < 200){

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(-30, 14, 0, 0, 1, 0, 0, 1, 0);

		story(tp);
		
		//crta sliku dok ne bude ukradena
		if(tp < 75){
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
			if(tp > 150)
				glTranslatef(-1 -4*tq, 4.15-2*tq, 0.5 + 6*tq);
			else
				glTranslatef(-1, 4.15, 0.5);
			if(tp > 140){
				glRotatef(180, 0,1,0);
				player_look();
			}
			else glutSolidSphere(0.65,30,30);
		glPopMatrix();

		//vestica
		if(tp < 130){
		glPushMatrix();
			if(tp < 50)
				glTranslatef(-25 + 15*tq, 1, -2.5);
			else if(tp > 100 && tp<130)
				glTranslatef(-10, 1, -2.5+10*tq);
			     else
				glTranslatef(-10, 1, -2.5);
			final_boss();
		glPopMatrix();
		}

		//zvezda koja krade sliku
		glPushMatrix();
			if(tp < 75 && tp > 50)
				glTranslatef(-5, 2+6*tq, -2.5);
			star();
		glPopMatrix();

		//zvezda koja pravi portal
		glPushMatrix();
			if(tp >=75 && tp <100)
				glTranslatef(-5, 2.5, -2.5 + 7*tq);
			glRotatef(90, 0, 1, 0);
			star();
		glPopMatrix();

	}
	else{

	// Podesavanje kamere i tacke gledista tako da prati kretanje igraca (dok ne traje neka od animacija)

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if(tp>=300 && tp < 425)
			gluLookAt(40, 14, 0, 60, 4, 0, 0, 1, 0);
		else if(tp > 425)
			gluLookAt(40+15*tq, 14-7*tq, 0-4*tq, 60, 4, 0-4*tq, 0, 1, 0);
		     else
			gluLookAt(-19+a1, 14, 0+a3, 0+a1, 4, 0+a3, 0, 1, 0);

		//Osnova
		glPushMatrix();
			osnova();
		glPopMatrix();

		//Ograda
		glPushMatrix();
			ograda();
		glPopMatrix();
	
		//Ovo se aktivira samo kada igrac predje igricu ili kada koristimo precicu(taster o)
		if(tp>=300){

			//iscrtava vesticu i kasnije povlaci sa scene
			glPushMatrix();
				if(tp >= 400 && tp <425)
					glTranslatef(60, 0-tq*7, 0);
				else if(tp<400)glTranslatef(60,0,0);
				final_boss();
			glPopMatrix();

			//iscrtava magicnu vesticiju zzvezdu dva puta
			glPushMatrix();
				if((tp > 301  && tp < 325) || (tp >= 350  && tp < 375))
					glTranslatef(65, 1, 0-tq*5);
				star();
			glPopMatrix();	

			//animira stvaranje kante
			if(tp >= 325){

				//kreira kantu za smece
				glPushMatrix();
					glColor3f(0.5,0.5,0.5);
					glTranslatef(65,0.7,-5);

					if(tp < 350)
						glScalef(1, 10*tq, 1);
					else glScalef(1, 10, 1);

					glRotatef(90, -1, 0, 0);
					glutSolidTorus(0.1,0.75,30,30);
				glPopMatrix();
	
				//Poklopac od kante
				glPushMatrix();
					glColor3f(0.5,0.5,0.5);
					glTranslatef(64.5,0.7,-3.5);
					glRotatef(100,-1,0,0);
					glRotatef(-38, 1, 0, 0);
					if(tp < 350)
						glScalef(1, 0.1*tq, 1);
					else glScalef(1, 0.1, 1);
					glutSolidSphere(1,30,30);
				glPopMatrix();
			}

			//Postavlja Junaka srece u kantu
			if(tp >= 375){
				glPushMatrix();
					glTranslatef(64.8,0.2,-6);
					glScalef(0.01,0.08,0.07);
					bold_and_brash();
				glPopMatrix();
			}	

			//Pravi portal
			if(tp > 390){
				glPushMatrix();
					glColor3f(0.2, 0.75, 1);
					glTranslatef(65, 0.4, 0);
					glScalef(1.5, 0.3, 1.5);
					glutSolidSphere(1, 30, 30);
				glPopMatrix();
			}	
		}
		else {
			//Neprijatelji prvog nivoa
			glPushMatrix();
				enemy();
			glPopMatrix();
	
			//Igrac
			glPushMatrix();
				igrac();
			glPopMatrix();

			//Neprijatelji drugog nivoa
			glPushMatrix();
				if(door1 >= 10)
					enemy2();
			glPopMatrix();

			//Funkcija koja iscrtava i pozicitonira zuti kljuc
			if(key_collected[0] == 0){
			glPushMatrix();
				glColor3f(1, 1, 0);
				glTranslatef(34, 0, 5);
				key_shape();
			glPopMatrix();
			}

			//Funkcija koja iscrtava i pozicitonira zeleni kljuc
			if(key_collected[1] == 0){
			glPushMatrix();
				glColor3f(0.564, 0.933, 0.564);
				glTranslatef(38, 0, -8);
				key_shape();
			glPopMatrix();
			}
	
			//Health bar
			glPushMatrix();
				health_bar();
			glPopMatrix();
	
			//Granica1 - nestaje kad se uniste svi neprijatelji prvog sektora
			if(door1 < 10){
				glPushMatrix();
					border1();
				glPopMatrix();
			}
	
			//Granica2 - nestaje kad se skupi zeleni kljuc
			if(key_collected[1] == 0){
				glPushMatrix();
					glTranslatef(40, 0, 0);
					border1();
				glPopMatrix();
			}
		
			//AKtivira funkciju za pucanj igraca kada se pritisne taster za pucanje
			if(shoot_key == 1)
				shoot();

			
			
		}
	}	
	//glutPostRedisplay();
	glutSwapBuffers();
}
