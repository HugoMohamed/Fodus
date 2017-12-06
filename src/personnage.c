#include "personnage.h"

void perso_creerPerso(map m,perso *p,coord *c, int vie, int dmg,persoTab joueurs,int numperso)
{
  p->pos.x = c->x;
  p->pos.y = c->y;
  p->vie = vie;
  p->dmg = dmg;

  joueurs[numperso] = *p;

  MLV_draw_filled_rectangle( (p->pos.x)*40, (p->pos.y)*40,40,40, MLV_COLOR_BLUE );
  m[p->pos.y][p->pos.x] = '3';

}


int perso_deplacer(map m, perso *p, int numJ, persoTab joueur, int direction, int pm)
{

  m[p->pos.y][p->pos.x] = '0';
  if(direction == 0 && m[p->pos.y][p->pos.x -1] == '0')//gauche
  {
    perso_nettoyer((p->pos.x)*40,(p->pos.y)*40);
    p->pos.x --;
    pm --;
  }

  if(direction == 1 && m[p->pos.y][p->pos.x +1] == '0') //droite
  {
    perso_nettoyer((p->pos.x)*40,(p->pos.y)*40);
    p->pos.x ++;
    pm --;
  }

  if(direction == 2 && m[p->pos.y - 1][p->pos.x] == '0') //haut
  {
    perso_nettoyer((p->pos.x)*40,(p->pos.y)*40);
    p->pos.y --;
    pm --;
  }

  if(direction == 3 && m[p->pos.y + 1][p->pos.x] == '0') //bas
  {
    perso_nettoyer((p->pos.x)*40,(p->pos.y)*40);
    p->pos.y ++;
    pm --;
  }

  MLV_draw_filled_rectangle( (p->pos.x)*40, (p->pos.y)*40,40,40, MLV_COLOR_BLUE );
  m[p->pos.y][p->pos.x] = '3';
  joueur[numJ].pos.x = p->pos.x;
  joueur[numJ].pos.y = p->pos.y;

  MLV_actualise_window();
  return pm;
}

void perso_attaque(map m,perso *p1,persoTab joueurs,int x,int y,int nbJoueurs)
{
  int i;
  // animation d'attaque au coordonnées c a ajouter
  for(i=1;i<=nbJoueurs;i++)
  if(x == joueurs[i].pos.x && y == joueurs[i].pos.y)
  {
    joueurs[i].vie -= p1->dmg;
    m[joueurs[i].pos.y][joueurs[i].pos.x] = '3';
  }

}

void perso_nettoyer(int x,int y)
{
	MLV_Image *sol;
	sol = MLV_load_image("../textures/case_sol.png");
	MLV_draw_image(sol,x,y);
	MLV_actualise_window();
}

void perso_nettoyerAttaque(map m,int x,int y,persoTab joueurs,int nbJ)
{
  int i;
  for(i=1;i<=3;i++)
  {
    if(m[y][x+i] == '4')
    {
      MLV_draw_filled_rectangle((x+i)*40,y*40,40,40, MLV_COLOR_BLUE);
      m[y][x+i] = '3';
      MLV_actualise_window();
    }

    if(m[y][x+i] == '2')
    {
      m[y][x+i] = '0';
      perso_nettoyer((x+i)*40,y*40);
    }


    if(m[y+i][x] == '4')
    {
      MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40, MLV_COLOR_BLUE);
      m[y+i][x] = '3';
      MLV_actualise_window();
    }

    if(m[y+i][x] == '2')
    {
      m[y+i][x] = '0';
      perso_nettoyer(x*40,(y+i)*40);
    }
  }

  for(i=-3;i<0;i++)
  {
    if(m[y][x+i] == '4')
    {
      MLV_draw_filled_rectangle((x+i)*40,y*40,40,40, MLV_COLOR_BLUE);
      m[y][x+i] = '3';
      MLV_actualise_window();
    }

    if(m[y][x+i] == '2')
    {
      m[y][x+i] = '0';
      perso_nettoyer((x+i)*40,y*40);
    }


    if(m[y+i][x] == '4')
    {
      MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40, MLV_COLOR_BLUE);
      m[y+i][x] = '3';
      MLV_actualise_window();
    }

    if(m[y+i][x] == '2')
    {
      m[y+i][x] = '0';
      perso_nettoyer(x*40,(y+i)*40);
    }
  }
  m[y][x] = '3';
}

void perso_attaqueA(map m, int x, int y)
{
  int i;
  i = 1;
  while(i <= 3 && m[y][x+i] != '1')
  {
    if(m[y][x+i] == '0')
    {
      m[y][x+i] = '2';
      MLV_draw_filled_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
    }
    if(m[y][x+i] == '3')
    {
      MLV_draw_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
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
      MLV_draw_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
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
      MLV_draw_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
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
      MLV_draw_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
      m[y+i][x] = '4';
    }
    i--;
  }
}
