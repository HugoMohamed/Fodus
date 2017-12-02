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
    while(pm != 0)
    {
      	// On gere les evenement du clavier
      	touche = 0;

	while(touche != MLV_KEYBOARD_z || touche != MLV_KEYBOARD_s || touche != MLV_KEYBOARD_q || touche != MLV_KEYBOARD_d || touche != MLV_KEYBOARD_a)
	    MLV_wait_keyboard(&touche,NULL,NULL);

	// on deplace le perso
	if(touche == MLV_KEYBOARD_q)
	    perso_deplacer(m,p,0);
	else if(touche == MLV_KEYBOARD_d)
	    perso_deplacer(m,p,1);
	else if(touche == MLV_KEYBOARD_z)
	    perso_deplacer(m,p,2);
	else if(touche == MLV_KEYBOARD_s)
	    perso_deplacer(m,p,3);

	// s'il choisi d'attaquer
	else if(touche == MLV_KEYBOARD_a)
	{
	    // On affiche en surbrillance les cases ou il peut attaquer
	    for(i=1;i<=3;i++)
	    {
		m[p->pos.x+i][p->pos.y] = 2;
		m[p->pos.x][p->pos.y+i] = 2;
		MLV_draw_filled_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		MLV_draw_filled_rectangle(p->pos.x*40,(p->pos.y+i)*40,40,40,MLV_COLOR_GREEN);
	    }
	    for(i=-3;i<=1;i++)
	    {
		m[p->pos.x+i][p->pos.y] = 2;
		m[p->pos.x][p->pos.y+i] = 2;
		MLV_draw_filled_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		MLV_draw_filled_rectangle(p->pos.x*40,(p->pos.y+i)*40,40,40,MLV_COLOR_GREEN);
	    }
	    MLV_actualise_window();

	    // On attend qu'il clique sur une des cases
	    do
	    {
		MLV_wait_mouse(&mouseX,&mouseY);
		mouseX /= 40;
		mouseY /= 40;
	    }while(m[mouseX][mouseY] != 2);

	    // Le perso attaque sur la case selectionnée


	    pa --;
    	}
	// on repete l'operation tant qu'il a le droit de bouger
    	pm --;
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
