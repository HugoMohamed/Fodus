#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED
#include <MLV/MLV_all.h>

#define VIE 100
#define DEGAT 10

typedef struct
{
    int x;
    int y
} coordonnees;

//Crée un personnage à une position par défaut
coordonnees perso_creerPerso();


//Prend les coordonnes initiales et renvoi les nouvelles
coordonnees perso_deplacer(map m, coordonnees c, int direction);





#endif
