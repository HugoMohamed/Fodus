#ifndef PERSO_H
#define PERSO_H
#include "map.h"
#include <MLV/MLV_all.h>

#define VIE 100
#define DEGAT 10

typedef struct
{
    int x;
    int y;
} coord;

typedef struct
{
    int vie;
    int dmg;
    coord pos;
} perso;

// Pour avoir une liste des joueurs
// Avec p[0] le nombre de joueurs
typedef perso persoTab[TMAX];

// Initialise un perso
void perso_creerPerso(map m,perso *p,coord *c, int vie, int dmg,persoTab joueurs,int numperso);

// Deplace le perso p d'une case a gauche/droite/haut/bas
void perso_deplacer(map m, perso *p, int direction);

// Le perso p attaque en c
void perso_attaque(perso *p1,persoTab joueurs,int x, int y,int nbJoueurs);

// Rend la couleur initiale à la case de coordonnées (x,y)
void perso_nettoyer(int x,int y);

// Remet les cases ou le joueur pouvait attaquer a 0
void perso_nettoyerAttaque(map m,int x,int y);

#endif
