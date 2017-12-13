#ifndef MARKSMAN_C
#define MARKSMAN_C

#include "marksman.h"

int marksman_attaqueA(perso *p,map m,persoTab joueurs,int nbJoueurs,int pa)
{
	int x = p->pos.x;
	int y= p->pos.y;
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
		perso_nettoyerAttaque(m,joueurs,nbJoueurs);
		pa --;
	}
	else
	perso_nettoyerAttaque(m,joueurs,nbJoueurs);
	return pa;
}

int marksman_atkE(perso *p,map m,persoTab joueurs,int nbJoueurs,int pa)
{
	int x = p->pos.x;
	int y = p->pos.y;
	int i = 1;
	int j;
	int a;
	int mouseX, mouseY;

	// On affiche les cases attaquables
	while(i <= 3 && m[y][x+i] != '1')
	{
		if(m[y][x+i] == '0')
		{
			m[y][x+i] = '2';
			MLV_draw_filled_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y][x+i] == '3')
		{
			m[y][x+i] = '4';
		}
		i++;
	}
	i = 1;
	while( i <= 3 && m[y+i][x] != '1')
	{
		if(m[y+i][x] == '0')
		{
			m[y+i][x] ='2';
			MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y+i][x] == '3')
		{
			m[y+i][x] = '4';
		}
		i++;
	}
	i = -1;
	while(i >= -3 && m[y][x+i] != '1')
	{
		if(m[y][x+i] == '0')
		{
			m[y][x+i] = '2';
			MLV_draw_filled_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y][x+i] == '3')
		{
			m[y][x+i] = '4';
		}
		i--;
	}
	i = -1;
	while(i >= -3 && m[y+i][x] != '1')
	{
		if(m[y+i][x] == '0')
		{
			m[y+i][x] = '2';
			MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y+i][x] == '3')
		{
			m[y+i][x] = '4';
		}
		i--;
	}
	MLV_actualise_window();

	// On attend qu'il clique
	MLV_wait_mouse(&mouseX,&mouseY);
	mouseX /= 40;
	mouseY /= 40;

	if(m[mouseY][mouseX] == '2' || m[mouseY][mouseX] == '4')
	{
		// Si il clique sur un joueur
		if(m[mouseY][mouseX] == '4')
		{
			// On regarde sur quel joueur on a cliqué
			for(a=1;a<=nbJoueurs;a++)
			{
				if(mouseX == joueurs[a].pos.x && mouseY == joueurs[a].pos.y)
				{
					// Si le joueur ciblé est au dessus
					if(p->pos.x == joueurs[a].pos.x && joueurs[a].pos.y < p->pos.y)
					{
						// On le déplace de 3 cases vers le haut tant qu'il n'y a pas d'obstacles
						for(j=1;j<=3;j++)
						{
							if(m[joueurs[a].pos.y-1][joueurs[a].pos.x] == '0' ||  m[joueurs[a].pos.y-1][joueurs[a].pos.x] == '2')
							{
								m[joueurs[a].pos.y][joueurs[a].pos.x] = '2';
								m[joueurs[a].pos.y-1][joueurs[a].pos.x] = '4';
								joueurs[a].pos.y --;
							}
						}
					}
					// Si le joueur ciblé est au dessous
					if(p->pos.x == joueurs[a].pos.x && joueurs[a].pos.y > p->pos.y)
					{
						// On le déplace de 3 cases vers le haut tant qu'il n'y a pas d'obstacles
						for(j=1;j<=3;j++)
						{
							if(m[joueurs[a].pos.y+1][joueurs[a].pos.x] == '0' ||  m[joueurs[a].pos.y+1][joueurs[a].pos.x] == '2')
							{
								m[joueurs[a].pos.y][joueurs[a].pos.x] = '2';
								m[joueurs[a].pos.y+1][joueurs[a].pos.x] = '4';
								joueurs[a].pos.y ++;
							}
						}
					}
					// Si le joueur est à gauche
					if(p->pos.x > joueurs[a].pos.x && joueurs[a].pos.y == p->pos.y)
					{
						// On le déplace de 3 cases vers le haut tant qu'il n'y a pas d'obstacles
						for(j=1;j<=3;j++)
						{
							if(m[joueurs[a].pos.y][joueurs[a].pos.x-1] == '0' ||  m[joueurs[a].pos.y][joueurs[a].pos.x-1] == '2')
							{
								m[joueurs[a].pos.y][joueurs[a].pos.x] = '2';
								m[joueurs[a].pos.y][joueurs[a].pos.x-1] = '4';
								joueurs[a].pos.x --;
							}
						}
					}
					// Si le joueur ciblé est à droite
					if(p->pos.x < joueurs[a].pos.x && joueurs[a].pos.y == p->pos.y)
					{
						// On le déplace de 3 cases vers le haut tant qu'il n'y a pas d'obstacles
						for(j=1;j<=3;j++)
						{
							if(m[joueurs[a].pos.y][joueurs[a].pos.x+1] == '0' ||  m[joueurs[a].pos.y][joueurs[a].pos.x+1] == '2')
							{
								m[joueurs[a].pos.y][joueurs[a].pos.x] = '2';
								m[joueurs[a].pos.y][joueurs[a].pos.x+1] = '4';
								joueurs[a].pos.x ++;
							}
						}
					}
				}

			}
		}
		pa--;
	}
	perso_nettoyerAttaque(m,joueurs,nbJoueurs);
	return pa;
}
#endif
