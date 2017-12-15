#ifndef JEUX_H
#define JEUX_H

#include "knight.h"
#include "marksman.h"
#include "ia.h"
#include "sauvegarde.h"

// Gère le tour d'un joueur
void jeux_tour(perso *p, int numJ, persoTab joueurs,map m,int nbJoueurs,int papm[2]);

// Renvoie le joueur gagnant si la partie est terminée et 0 sinon
int jeux_fin(persoTab joueurs, map m,int nbJoueurs);

// Affiche le vainqueur
void jeux_afficherGagnant(int gagnant);

// Affiche les différentes information sur les joueurs
void jeux_hud(persoTab joueurs, int numJ, int pa, int pm,int nbJoueurs);

// Met le jeu en pause
void jeux_pause(persoTab joueurs,map m, int nbJoueurs, int numJ,int papm[2]);

#endif
