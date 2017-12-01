#ifndef MAP_C
#define MAP_C

#include "map.h"

void map_chargerMap(char *chemin,map m)
{
    FILE* fileMap = NULL;
    int i,j,c;
    fileMap = fopen(chemin,"r");
    if(fileMap == NULL)
    {
	fprintf(stderr,"Impossible d'ouvrir '%s'\n",chemin);
	exit(-1);
    }

    for(i=0;i<18;i++)
	for(j=0;j<27;j++)
	  if((c = fgetc(fileMap))!='\n')
	    m[i][j] = c;
    
    fclose(fileMap);
}

void map_afficherMap(map m)
{
    int i,j;
    for(i=0;i<18;i++)
    {
	for(j=0;j<27;j++)
	{
	    if(m[i][j]=='1')
		MLV_draw_rectangle(j*40,i*40,40,40,MLV_COLOR_BROWN);
	    if(m[i][j]=='0')
		MLV_draw_rectangle(j*40,i*40,40,40,MLV_COLOR_WHITE);
	    MLV_actualise_window();
	}
        
    }
}


#endif
