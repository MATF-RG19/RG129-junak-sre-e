#ifdef __linux__ 
#include <GL/glut.h>
#elif _WIN32
#include <glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void player_look();
void bullet_look();