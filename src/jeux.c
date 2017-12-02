#ifndef JEUX_C
#define JEUX_C

#include "jeux.h"

void jeux_tour(perso *p, map m)
{
    int pm = 6; // Les points de mouvement du joueur
    int pa = 1; // Les points d'action du joueur
    int i;
    int mouseX, mouseY;
    MLV_Keyboard_button touche;

    // Tant que le joueur peut se déplacer
    while(pm > 0 || pa > 0)
    {
      	// On gere les evenement du clavier
	MLV_wait_keyboard(&touche,NULL,NULL);
	
	// on deplace le perso
	if(touche == MLV_KEYBOARD_q && pm >0)
	{
	    perso_deplacer(m,p,0);
	    pm --;	
	}
	if(touche == MLV_KEYBOARD_d && pm >0)
	{
	    perso_deplacer(m,p,1);
	    pm --;
	}
	if(touche == MLV_KEYBOARD_z && pm >0)
	{
	    perso_deplacer(m,p,2);
	    pm --;
	}
	if(touche == MLV_KEYBOARD_s && pm >0)
	{
	    perso_deplacer(m,p,3);
	    pm --;
	}

	// s'il choisi d'attaquer
	if(pa > 0 && touche == MLV_KEYBOARD_a)
	{
	    // On affiche en surbrillance les cases ou il peut attaquer
	    for(i=1;i<=3;i++)
	    {
		if(m[p->pos.y][p->pos.x+i] != '1')
		{
		    m[p->pos.y][p->pos.x+i] = '2';
		    MLV_draw_filled_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		}
		if(m[p->pos.y+i][p->pos.x] != '1')
		{
		    m[p->pos.y+i][p->pos.x] ='2';
	        
		    MLV_draw_filled_rectangle(p->pos.x*40,(p->pos.y+i)*40,40,40,MLV_COLOR_GREEN);
		}
	    }
	    
	    for(i=-3;i<0;i++)
	    {
		if(m[p->pos.y][p->pos.x+i] != '1')
		{
		    m[p->pos.y][p->pos.x+i] = '2';
		    MLV_draw_filled_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		}
		if(m[p->pos.y+i][p->pos.x] != '1')
		{
		    m[p->pos.y+i][p->pos.x] ='2';
	        
		    MLV_draw_filled_rectangle(p->pos.x*40,(p->pos.y+i)*40,40,40,MLV_COLOR_GREEN);
		}
	    }
	    MLV_actualise_window();

	    // On attend qu'il clique sur une des cases
	    
	    MLV_wait_mouse(&mouseX,&mouseY);
	    mouseX /= 40;
	    mouseY /= 40;
	    if(m[mouseY][mouseX] == '2')
	    {
		fprintf(stdout,"Attaque !\n");
		pa --;
		perso_nettoyerAttaque(m,p->pos.x,p->pos.y);
	    }
	    else
	        perso_nettoyerAttaque(m,p->pos.x,p->pos.y);
	    	    
	    // Le perso attaque sur la case selectionnée

    	}
	// on repete l'operation tant qu'il a le droit de bouger
    }
}

void jeux_cleanAtk(map m)
{
    int i,j;
    for(i=0;i<TMAX;i++)
	for(j=0;j<TMAX;j++)
	    if(m[i][j] == 2)
		m[i][j] = 1;
}

#endif
