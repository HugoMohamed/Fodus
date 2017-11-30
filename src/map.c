#include "map.h"

void map_chargerMap(char *chemin,map m)
{
    FILE* fileMap = NULL;
    int i,j;
    fileMap = fopen(chemin,"r");
    if(fileMap == NULL)
    {
	fprintf(stderr,"Impossible d'ouvrir '%s'\n",chemin);
	exit(-1);
    }

    for(i=0;i<27;i++)
	for(j=0;j<18;j++)
	    m[i][j]=fgetc(fileMap);
    
    fclose(fileMap);
}
