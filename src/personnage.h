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

// Un tir a une position (qui évolue) et un tireur (pour les dmg)

// Initialise un perso
void perso_creerPerso(perso *p,coord *c, int vie, int dmg);

// Deplace le perso p d'une case a gauche/droite/haut/bas
void perso_deplacer(map m, perso *p, int direction);

// Le perso p attaque en c
void perso_attaque(perso *p1,perso *p2,coord *c);

#endif
