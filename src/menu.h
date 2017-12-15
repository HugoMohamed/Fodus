#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "MLV/MLV_all.h"

// Affiche le menu et retourne une des valeurs suivantes :
/*
	1 pour singleplayer
	2 pour multiplayer
	3 pour charger une partie
	4 pour quitter
	5 pour les credits
*/
int menu_afficher();

// Affiche les crédits
void menu_credits();

#endif
