#ifndef KNIGHT_C
#define KNIGHT_C

#include "knight.h"
#include "personnage.h"

int knight_attaqueA(perso *p,map m, int x, int y,persoTab joueurs,int nbJoueurs,int pa)
{
	int i = 1;
	int mouseX, mouseY;

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

	// On attend qu'il clique sur une case
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

int knight_atkE(perso *p,map m, int x, int y,persoTab joueurs,int nbJoueurs,int pa)
{
	int i;
	int mouseX, mouseY;
	// On affiche les cases attaquables
	for(i=1;i<=5;i++)
	{
		if(m[y-i][x] != '1')
		{
			if(m[y-i][x] == '0')
			m[y-i][x] = '2';
			if(m[y-i][x] == '3')
			m[y-i][x] = '4';

			MLV_draw_filled_rectangle(x*40,(y-i)*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y][x-i] != '1')
		{
			if(m[y][x-i] == '0')
			m[y][x-i] = '2';
			if(m[y][x-i] == '3')
			m[y][x-i] = '4';
			MLV_draw_filled_rectangle((x-i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
		}
	}
	for(i=1;i<=5;i++)
	{
		if(m[y+i][x] != '1')
		{
			if(m[y+i][x] == '0')
			m[y+i][x] = '2';
			if(m[y+i][x] == '3')
			m[y+i][x] = '4';

			MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
		}
		if(m[y][x+i] != '1')
		{
			if(m[y][x+i] == '0')
			m[y][x+i] = '2';
			if(m[y][x+i] == '3')
			m[y][x+i] = '4';
			MLV_draw_filled_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
		}
	}

	MLV_actualise_window();
	// On attend qu'il clique sur une case
	MLV_wait_mouse(&mouseX,&mouseY);
	mouseX /= 40;
	mouseY /= 40;
	// S'il clique sur une case valide
	if(m[mouseY][mouseX] == '2' || m[mouseY][mouseX] == '4')
	{
		// S'il clique sur un joueur
		if(m[mouseY][mouseX] == '4')
		{
			// On regarde sur quel joueur il a cliqué
			for(i=1;i<=nbJoueurs;i++)
			{
				if(mouseX == joueurs[i].pos.x && mouseY == joueurs[i].pos.y)
				{
					// On ramène le joueur ciblé vers le joueur qui attaque
					if(m[y][x+1] != '1' && m[y][x+1] != '3')
					{
						perso_nettoyer(joueurs[i].pos.x,joueurs[i].pos.y,m);
						m[mouseY][mouseX] = '2';
						m[y][x+1] = '4';
						joueurs[i].pos.x = x+1;
						joueurs[i].pos.y = y;
					}
					else if(m[y-1][x] != '1' && m[y-1][x] != '3')
					{
						perso_nettoyer(joueurs[i].pos.x,joueurs[i].pos.y,m);
						m[mouseY][mouseX] = '2';
						m[y-1][x] = '4';
						joueurs[i].pos.x = x;
						joueurs[i].pos.y = y-1;
					}
					else if(m[y+1][x] != '1' && m[y+1][x] != '3')
					{
						perso_nettoyer(joueurs[i].pos.x,joueurs[i].pos.y,m);
						m[mouseY][mouseX] = '2';
						m[y+1][x] = '4';
						joueurs[i].pos.x = x;
						joueurs[i].pos.y = y+1;
					}
					else if(m[y][x-1] != '1' && m[y][x-1] != '3')
					{
						perso_nettoyer(joueurs[i].pos.x,joueurs[i].pos.y,m);
						m[mouseY][mouseX] = '2';
						m[y][x-1] = '4';
						joueurs[i].pos.x = x-1;
						joueurs[i].pos.y = y;
					}
				}
			}
		}
		pa --;
	}
	perso_nettoyerAttaque(m,p->pos.x,p->pos.y,joueurs,nbJoueurs);
	return pa;

}
#endif
