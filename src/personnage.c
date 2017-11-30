#include "personnage.h"

void perso_creerPerso(perso *p,coord *c, int vie, int dmg)
{
    p->pos.x = c->x;
    p->pos.y = c->y;
    p->vie = vie;
    p->dmg = dmg;
    
    MLV_draw_rectangle( c.x, c.y, 2, 2, MLV_COLOR_BLUE );
}


void perso_deplacer(map m, perso *p, int direction)
{
    if(direction == 0 && m[p->pos.x + 1][p->pos.y] == 0)//gauche
	p->pos.x --;

    else
	if(direction == 1 && m[p->pos.x + 2][p->pos.y] == 0) //droite
	    p->pos.x ++;
}



    
	

    
