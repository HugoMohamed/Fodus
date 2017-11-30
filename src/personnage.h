#ifndef PERSO_H
#define PERSO_H

#include <MLV/MLV_all.h>

#define VIE 100
#define DEGAT 10

typedef struct
{
    int x;
    int y
} coord;

typedef struct
{
    int vie;
    int dmg;
    coord pos
}perso;

//Initialise un perso
void perso_creerPerso(perso *p,coord *c, int vie, int dmg);

//Deplace le perso p a d'une case a gauche ou a droite
void perso_deplacer(map m, perso *p, int direction)


#endif
