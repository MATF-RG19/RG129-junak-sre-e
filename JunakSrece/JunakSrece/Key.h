#ifdef __linux__ 
#include <GL/glut.h>
#elif _WIN32
#include <glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

void key_design();

//Da li je kljuc sakupljen (imaju dva, prvi za zuti kljuc drugi za zeleni)
int key_collected[2];