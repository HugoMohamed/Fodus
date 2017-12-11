#ifndef KNIGHT_H
#define KNIGHT_H

#include "personnage.h"

// Attaque de base
int knight_attaqueA(perso *p,map m, int x, int y,persoTab joueurs,int nbJoueurs,int pa);

// Grab
int knight_atkE(perso *p,map m, int x, int y,persoTab joueurs,int nbJoueurs,int pa);

#endif
