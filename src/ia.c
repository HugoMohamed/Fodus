#ifndef IA_C
#define IA_C

#include "ia.h"
#include <math.h>

void ia_approche(map m,perso *p,persoTab joueur,int pm,int nbJoueurs)
{
	int i =1, dir;
	double minD,d;
	while(pm > 0)
	{
		dir = -1;
		if(m[joueur[2].pos.y+i][joueur[2].pos.x] == '3' || m[joueur[2].pos.y-i][joueur[2].pos.x] == '3' || m[joueur[2].pos.y][joueur[2].pos.x+i] == '3' || m[joueur[2].pos.y][joueur[2].pos.x-i] == '3')
		{
			perso_attaque(m,p,joueur,joueur[1].pos.x,joueur[1].pos.y,2);
			pm = 0;
		}
		minD = sqrt(((joueur[2].pos.x-joueur[1].pos.x)*(joueur[2].pos.x-joueur[1].pos.x))+((joueur[2].pos.y-joueur[1].pos.y)*(joueur[2].pos.y-joueur[1].pos.y)));

		d = sqrt((joueur[2].pos.x+i-joueur[1].pos.x)*(joueur[2].pos.x+i-joueur[1].pos.x)+((joueur[2].pos.y-joueur[1].pos.y)*(joueur[2].pos.y-joueur[1].pos.y)));
		if(d < minD && m[joueur[2].pos.y][joueur[2].pos.x+i] == '0')
		{
			dir = 1;
			minD = d;
		}
		d = sqrt(((joueur[2].pos.x-i-joueur[1].pos.x)*(joueur[2].pos.x-i-joueur[1].pos.x))+((joueur[2].pos.y-joueur[1].pos.y)*(joueur[2].pos.y-joueur[1].pos.y)));
		if(d < minD && m[joueur[2].pos.y][joueur[2].pos.x-i] == '0')
		{
			minD = d;
			dir = 0;
		}
		d = sqrt(((joueur[2].pos.x-joueur[1].pos.x)*(joueur[2].pos.x-joueur[1].pos.x))+((joueur[2].pos.y-i-joueur[1].pos.y)*(joueur[2].pos.y-i-joueur[1].pos.y)));
		if(d < minD && m[joueur[2].pos.y-i][joueur[2].pos.x] == '0')
		{
			minD = d;
			dir = 2;
		}
		d = sqrt(((joueur[2].pos.x-joueur[1].pos.x)*(joueur[2].pos.x-joueur[1].pos.x))+((joueur[2].pos.y+i-joueur[1].pos.y)*((joueur[2].pos.y+i)-joueur[1].pos.y)));
		if(d < minD && m[joueur[2].pos.y+i][joueur[2].pos.x] == '0')
		{
			minD = d;
			dir = 3;
		}
		if(dir == -1)
		{
			if(m[joueur[2].pos.y+1][joueur[2].pos.x] == '1' || m[joueur[2].pos.y-1][joueur[2].pos.x] == '1')
			dir = 1;
			if(m[joueur[2].pos.y][joueur[2].pos.x-1] == '1' || m[joueur[2].pos.y][joueur[2].pos.x+1] == '1')
			dir = 3;
		}
		pm = perso_deplacer(m,p,2,joueur,dir,pm,nbJoueurs);
	}

}



#endif
