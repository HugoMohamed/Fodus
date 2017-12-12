#ifndef ARCHER_C
#define KNIGHT_C

#include "marksman.h"

int marksman_attaqueA(perso *p,map m, int x, int y,persoTab joueurs,int nbJoueurs,int pa)
{
	int i = 6,j;
	int mouseX, mouseY;
	for(j=0;j<=i;j++)
	{
		if(m[y-j][x+i-j] == '0')
		{
			m[y-j][x+i-j] = '2';
			MLV_draw_filled_rectangle((x+i-j)*40,(y-j)*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y-j][x+i-j] == '3')
		{
			m[y-j][x+i-j] = '4';
		}
		if(m[y-j][x-i+j] == '0')
		{
			m[y-j][x-i+j] = '2';
			MLV_draw_filled_rectangle((x-i+j)*40,(y-j)*40,40,40,MLV_rgba(0,255,0,100));

		}
		if(m[y-j][x-i+j] == '3')
		{
			m[y-j][x-i+j] = '4';
		}

		if(m[y+j][x+i-j] == '0')
		{
			m[y+j][x+i-j] = '2';
			MLV_draw_filled_rectangle((x+i-j)*40,(y+j)*40,40,40,MLV_rgba(0,255,0,100));
		}

		if(m[y+j][x+i-j] == '3')
		{
			m[y+j][x+i-j] = '4';
		}

		if(m[y+j][x-i+j] == '0')
		{
			m[y+j][x-i+j] = '2';
			MLV_draw_filled_rectangle((x-i+j)*40,(y+j)*40,40,40,MLV_rgba(0,255,0,100));
		}

		if(m[y+j][x-i+j] == '3')
		{
			m[y+j][x-i+j] = '4';
		}
	}
	MLV_actualise_window();
	MLV_wait_mouse(&mouseX,&mouseY);
	mouseX /= 40;
	mouseY /= 40;
	if(m[mouseY][mouseX] == '2' || m[mouseY][mouseX] == '4')
	{
		perso_attaque(m,p,joueurs,mouseX,mouseY,nbJoueurs);
		perso_nettoyerAttaque(m,p->pos.x,p->pos.y,joueurs,nbJoueurs);
		pa --;
	}
	else
	perso_nettoyerAttaque(m,p->pos.x,p->pos.y,joueurs,nbJoueurs);
	return pa;
}

#endif
