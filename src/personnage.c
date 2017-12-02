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
	perso_nettoyerDeplacement((p->pos.x)*40,(p->pos.y)*40);
	p->pos.x --;
    }
    
    if(direction == 1 && m[p->pos.y][p->pos.x +1] == '0') //droite
    {
	perso_nettoyerDeplacement((p->pos.x)*40,(p->pos.y)*40);
	p->pos.x ++;

    }

    if(direction == 2 && m[p->pos.y - 1][p->pos.x] == '0') //haut
    {
	perso_nettoyerDeplacement((p->pos.x)*40,(p->pos.y)*40);
	p->pos.y --;
    }

    if(direction == 3 && m[p->pos.y + 1][p->pos.x] == '0') //bas
    {
	fprintf(stdout,"%c\n",m[p->pos.x ][p->pos.y + 1]);
        perso_nettoyerDeplacement((p->pos.x)*40,(p->pos.y)*40);
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

void perso_nettoyerDeplacement(int x,int y)
{
    MLV_draw_filled_rectangle(x,y,40,40, MLV_COLOR_BLACK);
    MLV_draw_rectangle(x,y,40,40, MLV_COLOR_WHITE);
    MLV_actualise_window();
}
