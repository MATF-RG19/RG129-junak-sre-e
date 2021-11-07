#include "SpikyWall.h"

int movement_counter_wall = 0;
double spikes_x[10];
double spikes_z[10];

void spiky_wall(int key, double player_x, double player_z) {
	//Desni zid koji se pomera ako je skupljen zuti kljuc
	for (int i = 0; i < 2; i++) {
		glPushMatrix();
		glColor3f(1, 0.512, 456);
		if (key == 1) {

			movement_counter_wall++;

			if (sin(movement_counter_wall / 40.0) > 0)
				glTranslatef(spikes_x[i] = 22 + i * 10, 0.6, spikes_z[i] = 9.5 - sin(movement_counter_wall / 40.0) * 7);//40.0
			else glTranslatef(spikes_x[i] = 22 + i * 10, 0.6, spikes_z[i] = 9.5 + sin(movement_counter_wall / 40.0) * 7);
		}
		else glTranslatef(spikes_x[i] = 22 + i * 10, 0.6, spikes_z[i] = 9.5);
		spikes_design();
		spikes_wall_collision(player_x, player_z);
		glPopMatrix();
	}
}
void spikes_wall_collision(double player_x, double player_z) {

	if (player_x >= spikes_x[1] - 11 && player_x <= spikes_x[1] + 10 && player_z >= spikes_z[0] - 1.5 && player_z <= spikes_z[0] + 0.5) {
		damage_spikes++;
		//a1 = 15;
		//a3 = 0;
	}
}
void spikes_design() {

	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glTranslatef(1 * i, 0, 0);
		glRotatef(180, 0, 1, 0);
		glutSolidCone(0.5, 1, 30, 30);
		glPopMatrix();
	}
}
void static_spikes() {
	//Iscrtavanje siljaka s leve strane u drugom nivou
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(20, 0.0, -6 - i * 0.8);
		glRotatef(90, -1, 0, 0);
		glutSolidCone(0.5, 1, 30, 30);
		glPopMatrix();
	}

	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glColor3f(1, 0.512, 456);
		glTranslatef(30, 0.0, -7.5 - i * 0.8);
		glRotatef(90, -1, 0, 0);
		glutSolidCone(0.5, 1, 30, 30);
		glPopMatrix();
	}
}