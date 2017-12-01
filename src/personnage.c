#include "personnage.h"

void perso_creerPerso(perso *p,coord *c, int vie, int dmg)
{
    p->pos.x = c->x;
    p->pos.y = c->y;
    p->vie = vie;
    p->dmg = dmg;
    
    MLV_draw_filled_rectangle( c->x, c->y,40,40, MLV_COLOR_BLUE );
    
}


void perso_deplacer(map m, perso *p, int direction)
{
    if(direction == 0 && m[p->pos.x - 1][p->pos.y] == 0)//gauche
	p->pos.x --;

    else if(direction == 1 && m[p->pos.x + 1][p->pos.y] == 0) //droite
	p->pos.x ++;
    
    else if(direction == 2 && m[p->pos.x][p->pos.y - 1] == 0) //droite
	p->pos.y --;

    else if(direction == 3 && m[p->pos.x][p->pos.y + 1] == 0) //droite
	p->pos.y ++;
}

void perso_attaque(perso *p1,perso *p2,coord *c)
{
    // animation d'attaque au coordonnées c a ajouter
    if(c->x == p2->pos.x && c->y == p2->pos.y)
	p2->vie -= p1->dmg;
}
