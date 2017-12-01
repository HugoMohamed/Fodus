#ifndef JEUX_C
#define JEUX_C

#include "jeux.h"

void jeux_tour(perso *p, map *m)
{
    int pm = 6; // Le nombre de point de mouvement du joueur
    int i,j;
    MLV_Keyboard_button touche;

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
  		    MLV_draw_filled_rectangle((p->pos.x+1)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
          MLV_draw_filled_rectangle(p->pos.x*40,(p->pos.y+1)*40,40,MLV_COLOR_GREEN);
        }
        for(i=-3;i<=1;i++)
        {
  		    MLV_draw_filled_rectangle((p->pos.x+1)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
          MLV_draw_filled_rectangle(p->pos.x*40,(p->pos.y+1)*40,40,MLV_COLOR_GREEN);
  	    }

				// On attend qu'il clique sur une des cases

    }
    pm --;
}


#endif
