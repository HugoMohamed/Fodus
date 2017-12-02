#include "personnage.h"

void perso_creerPerso(perso *p,coord *c, int vie, int dmg)
{
    p->pos.x = c->x;
    p->pos.y = c->y;
    p->vie = vie;
    p->dmg = dmg;

    MLV_draw_filled_rectangle( p->pos.x, p->pos.y,40,40, MLV_COLOR_BLUE );

}


void perso_deplacer(map m, perso *p, int direction)
{
    if(direction == 0 && m[p->pos.x - 1][p->pos.y] == 0)//gauche
    {
	MLV_draw_rectangle( p->pos.x, p->pos.y,40,40, MLV_COLOR_WHITE );
	p->pos.x --;
    }

    else if(direction == 1 && m[p->pos.x + 1][p->pos.y] == 0) //droite
    {
	MLV_draw_rectangle( p->pos.x, p->pos.y,40,40, MLV_COLOR_WHITE );
	p->pos.x ++;
    }

    else if(direction == 2 && m[p->pos.x][p->pos.y - 1] == 0) //haut
    {
	MLV_draw_rectangle( p->pos.x, p->pos.y,40,40, MLV_COLOR_WHITE );
	p->pos.y ++;
    }

    else if(direction == 3 && m[p->pos.x][p->pos.y + 1] == 0) //bas
    {
	MLV_draw_rectangle( p->pos.x, p->pos.y,40,40, MLV_COLOR_WHITE );
	p->pos.y --;
    }

    MLV_draw_filled_rectangle( p->pos.x, p->pos.y,40,40, MLV_COLOR_BLUE );

    MLV_actualise_window();
}

void perso_attaque(perso *p1,persoTab pT,coord *c,int nbJoueur)
{
    int i;
    // animation d'attaque au coordonnées c a ajouter
    for(i=0;i<nbJoueur;i++)
	if(c->x == pT[i].pos.x && c->y == pT[i].pos.y)
	    pT[i].vie -= p1->dmg;
}
