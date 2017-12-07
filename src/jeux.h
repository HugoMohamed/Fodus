#ifndef JEUX_H
#define JEUX_H

#include "knight.h"
#include "ia.h"

// Gère le tour d'un joueur
void jeux_tour(perso *p, int numJ, persoTab joueurs,map m,int nbJoueurs);

// Renvoie le joueur gagnant si la partie est terminée et 0 sinon
int jeux_fin(persoTab joueurs, map m,int nbJoueurs);

// Affiche le vainqueur
void jeux_afficherGagnant(int gagnant);

void jeux_hud(persoTab joueurs, int numJ, int pa, int pm);
#endif
