#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define TMAX 100

typedef enum
{
    air,
    sol
}blocs;

typedef int map[TMAX][TMAX];

// Permet de charger la map depuis un fichier
void map_chargerMap(char *chemin,map *m);

// Permet d'afficher la map
void map_afficherMap(map m);
#endif
