#ifdef __linux__ 
#include <GL/glut.h>
#elif _WIN32
#include <glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <stdio.h>


void bush_shoot(int x, int z, double player_x, double player_z);
void bushDesign();
void enemyBush(double player_x, double player_z);
void bush_hit_or_miss(double player_x, double player_z);

//ne prepoznaje bool tip?
double damage;

