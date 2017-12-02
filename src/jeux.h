#ifndef JEUX_H
#define JEUX_H

#include "personnage.h"

// Gère le tour d'un joueur
void jeux_tour(perso *p, map m);

// Efface toute les cases ou le joueur peut attaquer
void jeux_cleanAtk(map m);

#endif
