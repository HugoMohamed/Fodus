#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#define TMAX 100

typedef enum
{
    air,
    sol
}blocs;

typedef int map[TMAX][TMAX];

// Permet de charger la map depuis un fichier
void map_chargerMap(FILE * map);

#endif
