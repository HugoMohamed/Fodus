#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "jeux.h"

// Sauvegarde la partie
void sauvegarde(map m,persoTab joueurs,int nbJoueurs,int numJ,int papm[2],int numG);

// Charge une partie
coord sauvegarde_charger(map m,persoTab joueurs,int papm[2],int numG);

// Renvoie le choix de la sauvegarde
int sauvegarde_choseSave();

#endif
