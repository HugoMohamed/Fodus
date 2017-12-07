#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "MLV/MLV_all.h"

#define TMAX 100

/* map est un tableau d'entier en 2 dimension avec :
	0 le sol
	1 les murs
	2 les cases ou le joueur peut attaquer
	(faudra ptet penser a utiliser des enum pour que ce soit plus propre)
*/
typedef int map[TMAX][TMAX];

// Permet de charger la map depuis un fichier map.txt
void map_chargerMap(char *chemin,map m);

// Permet d'afficher la map
void map_afficherMap(map m);
#endif
