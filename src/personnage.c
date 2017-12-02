#include "personnage.h"

void perso_creerPerso(perso *p,coord *c, int vie, int dmg)
{
    p->pos.x = c->x;
    p->pos.y = c->y;
    p->vie = vie;
    p->dmg = dmg;

    MLV_draw_filled_rectangle( (p->pos.x)*40, (p->pos.y)*40,40,40, MLV_COLOR_BLUE );

}


void perso_deplacer(map m, perso *p, int direction)
{

    if(direction == 0 && m[p->pos.y][p->pos.x -1] == '0')//gauche
    {
	perso_nettoyer((p->pos.x)*40,(p->pos.y)*40);
	p->pos.x --;
    }
    
    if(direction == 1 && m[p->pos.y][p->pos.x +1] == '0') //droite
    {
	perso_nettoyer((p->pos.x)*40,(p->pos.y)*40);
	p->pos.x ++;

    }

    if(direction == 2 && m[p->pos.y - 1][p->pos.x] == '0') //haut
    {
	perso_nettoyer((p->pos.x)*40,(p->pos.y)*40);
	p->pos.y --;
    }

    if(direction == 3 && m[p->pos.y + 1][p->pos.x] == '0') //bas
    {
        perso_nettoyer((p->pos.x)*40,(p->pos.y)*40);
	p->pos.y ++;
    }

    MLV_draw_filled_rectangle( (p->pos.x)*40, (p->pos.y)*40,40,40, MLV_COLOR_BLUE );

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

void perso_nettoyer(int x,int y)
{
    MLV_draw_filled_rectangle(x,y,40,40, MLV_COLOR_BLACK);
    MLV_draw_rectangle(x,y,40,40, MLV_COLOR_WHITE);
    MLV_actualise_window();
}

void perso_nettoyerAttaque(map m,int x,int y)
{
    int i;
    for(i=1;i<=3;i++)
    {
	if(m[y][x+i] != '1')
	{
	    m[y][x+i] = '0';
	    perso_nettoyer((x+i)*40,y*40);
	}
	if(m[y+i][x] != '1')
	{
	    m[y+i][x] = '0';
	    perso_nettoyer(x*40,(y+i)*40);
	}

    }
    for(i=-3;i<0;i++)
    {
	if(m[y][x+i] != '1')
	{
	    m[y][x+i] = '0';
	    perso_nettoyer((x+i)*40,y*40);
	}
	if(m[y+i][x] != '1')
	{
	    m[y+i][x] = '0';
	    perso_nettoyer(x*40,(y+i)*40);
	}
    }
}
