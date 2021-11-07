#ifdef __linux__ 
#include <GL/glut.h>
#elif _WIN32
#include <glut.h>
#endif

#include "Player.h"
#include "BeginingAnimation.h"
#include "EnemyBush.h"
#include "EndingAnimation.h"
#include "SpikyWall.h"
#include "Key.h"
#include "Borders.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define TIMER_ID 0
#define TIMER_INTERVAL 30

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void shoot();
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

//Pomocni parametar za animaciju igracevog pucnja 
double player_parameter=0; 

//Pomocni parametar za animaciju kretanja neprijatelja
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

//Parametri za pocetnu i krajnju animaciju
// tp se povecava a tq racuna 
int tp=0;
double tq=0;

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

	tq = tp/50.0;

	if(tp > 50 && tp < 75)
		tq = tp%50/25.0;
	if(tp >= 75 && tp < 100)
		tq = tp%75/25.0;
	if(tp >100 && tp < 130)
		tq = tp%100/30.0;
	if(tp > 150 && tp < 175)
		tq = tp%150/25.0;
	if (tp >= 300 && tp <325)
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

	esc		-izlazi iz programa

	w/W		-pomera igraca napred

	a/A		-pomera igraca ulevo

	d/D		-pomera igraca udesno

	s/S		-pomera igraca unazad

	k/K		-igrac puca

	p/P		-precica za drugi nivo

	n/N		-preskace najavnu spicu

	o/O		-precica za zavrsnu spicu i kraj
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
		break;
	case 'a':
	case 'A':
		pick_key = 1;
		a = -0.45;
		move_player = 1;
		strana = 1;
		break;
	case 'd':
	case 'D':
		pick_key = 1;
		a = 0.45;
		move_player = 1;
		strana =2;
		break;
	case 's':
	case 'S':
		pick_key = 0;
		w = -0.45;
		move_player = 1;
		strana =3;
		break;
	case 'p':
	case 'P':
		door1=10;
		a1=15;
		a3=0;
		tp=201;
		break;
	case 'o':
	case 'O':
		door1=10;
		a1=60;
		a3=0;
		tp=301;
		key_collected[1] = 1;
		break;
	case 'n':
	case 'N':
		tp=201;
		break;
	}

	if(key == 'k' || key == 'K'){
		side = strana;
		shoot_key=1;
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
//Funkcija koja proverava da li je protivnik pogodjen
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
}
//Neprijatelj puca prvu vrsta pucnja
static void enemy_shoot(int i){

	p=enemy_parameter%8;

	//Zavrsetak iscrtavanja pucnja
	if(p == 7){
		enemy_prepare[i] = 0;
		permission--;
	}
	//Animacija kretanja pucnja i provera da li je pogodio igraca
	else{
	glPushMatrix();

		glColor3f(0.2, 0.3, 0.8);
		glTranslatef(e_p1 = enemy_shoot_x[i]-6*p/8.0, 1,e_p3 = enemy_shoot_z[i]);
		glScalef(0.1, 0.1, 0.1);
		glutSolidCube(2);

		enemy_hit_or_miss();

	glPopMatrix();
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

static void on_display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	init_lights();

//Ako je vremenski parametar manji od 200 treba pokrenuti pocetnu animaciju igrice
//inace krecemo s igrom 

	if(tp < 200){
		story(tp,tq);
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
			ending_animation(tp, tq);
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
			if (door1 >= 10) {
				damage = 0;
				enemyBush(a1, a3);
				if (damage > 0) {
					health_parameter -= 1;
					a1 = 15;
					a3 = 0;
				}

				damage_spikes = 0;
				spiky_wall(key_collected[0], a1, a3);
				if (damage_spikes > 0) {
					health_parameter -= 1;
					a1 = 15;
					a3 = 0;
				}

				static_spikes();
			}
			glPopMatrix();

			//Funkcija koja iscrtava i pozicitonira zuti kljuc
			if(key_collected[0] == 0){
			glPushMatrix();
				glColor3f(1, 1, 0);
				glTranslatef(34, 0, 5);
				key_design();
			glPopMatrix();
			}

			//Funkcija koja iscrtava i pozicitonira zeleni kljuc
			if(key_collected[1] == 0){
			glPushMatrix();
				glColor3f(0.564, 0.933, 0.564);
				glTranslatef(38, 0, -8);
				key_design();
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
	
	glutSwapBuffers();
}
