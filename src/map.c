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

    for(i=0;i<17;i++)
	for(j=0;j<27;j++)
	    if((c = fgetc(fileMap))!='\n')
		m[i][j] = c;

    fclose(fileMap);
}

void map_afficherMap(map m)
{
	MLV_Image *sol;
	MLV_Image *mur;
    int i,j;

	sol = MLV_load_image("../textures/case_sol.png");
	mur = MLV_load_image("../textures/case_mur.png");

    for(i=0;i<17;i++)
		for(j=0;j<27;j++)
		{
		    if(m[i][j]=='1')
				MLV_draw_image(mur,j*40,i*40);
		    if(m[i][j]=='0')
				MLV_draw_image(sol,j*40,i*40);
		    MLV_actualise_window();
		}
}

#endif
