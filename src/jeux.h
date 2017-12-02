#ifndef JEUX_H
#define JEUX_H

#include "personnage.h"

// Gère le tour d'un joueur
void jeux_tour(perso *p,persoTab joueurs,map m,int nbJoueurs);

// Renvoie le joueur gagnant si la partie est terminée et 0 sinon
int jeux_fin(persoTab joueurs, map m,int nbJoueurs);

// Affiche le vainqueur
void jeux_afficherGagnant(int gagnant);

#endif
