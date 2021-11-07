#ifdef __linux__ 
#include <GL/glut.h>
#elif _WIN32
#include <glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void spiky_wall(int key, double player_x, double player_z);
void spikes_wall_collision(double player_x, double player_z);
void spikes_design();

int damage_spikes;