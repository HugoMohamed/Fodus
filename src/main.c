#ifndef MAIN_C
#define MAIN_C

#include "map.h"

int main()
{
    int i,j;
    map m;
    map_chargerMap("../map/map.txt",&m);
    for(i=0;i<27;i++)
    {
	for(j=0;j<18;j++)
	    fprintf(stdout,"%d",m[i][j]);
	fprintf(stdout,"\n");
    }

    exit(0);
	
}

#endif MAIN_C
