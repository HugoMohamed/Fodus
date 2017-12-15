#include "personnage.h"

void perso_creerPerso(map m,perso *p,coord *c, int vie, int dmg,persoTab joueurs,int numperso,char classe)
{
	p->pos.x = c->x;
	p->pos.y = c->y;
	p->vie = vie;
	p->dmg = dmg;
	p->classe = classe;
	p->etat = 'v';   // Vivant
	m[p->pos.y][p->pos.x] = '3';
}

char perso_choixClasse()
{
	int x,y;
	int xM = 12;
	int yM = 202;
	int xK = 283;
	int yK = 202;
	MLV_Image *choixP = MLV_load_image("../textures/choix_perso.png");

	MLV_draw_image(choixP,0,0);
	MLV_actualise_window();
	while(1)
	{
		MLV_wait_mouse(&x,&y);
		// knight
		if(x>=xK && x<xK+192 && y>=yK && y<yK+301 )
		{
			return 'k';
		}
		// Marksman
		if(x>=xM && x<xM+192 && y>=yM && y<yM+301 )
		{
			return 'm';
		}
	}
}


int perso_deplacer(map m, perso *p, int numJ, persoTab joueur, int direction, int pm,int nbJoueurs)
{
	MLV_Image *knight = MLV_load_image("../textures/knight/knight_walkdown1.png");
	MLV_Image *marksman = MLV_load_image("../textures/marksman/marksman.png");

	m[p->pos.y][p->pos.x] = '0';
	if(direction == 0 && m[p->pos.y][p->pos.x -1] == '0')//gauche
	{
		perso_nettoyer((p->pos.x)*40,(p->pos.y)*40,m,joueur,nbJoueurs);
		p->pos.x --;
		pm --;
	}

	if(direction == 1 && m[p->pos.y][p->pos.x +1] == '0') //droite
	{
		perso_nettoyer((p->pos.x)*40,(p->pos.y)*40,m,joueur,nbJoueurs);
		p->pos.x ++;
		pm --;
	}

	if(direction == 2 && m[p->pos.y - 1][p->pos.x] == '0') //haut
	{
		perso_nettoyer((p->pos.x)*40,(p->pos.y)*40,m,joueur,nbJoueurs);
		p->pos.y --;
		pm --;
	}

	if(direction == 3 && m[p->pos.y + 1][p->pos.x] == '0') //bas
	{
		perso_nettoyer((p->pos.x)*40,(p->pos.y)*40,m,joueur,nbJoueurs);
		p->pos.y ++;
		pm --;
	}

	if(p->classe == 'k')
	MLV_draw_image(knight,(p->pos.x)*40+5,(p->pos.y)*40-15);
	else if(p->classe == 'm')
	MLV_draw_image(marksman,(p->pos.x)*40+5,(p->pos.y)*40-15);
	m[p->pos.y][p->pos.x] = '3';
	joueur[numJ].pos.x = p->pos.x;
	joueur[numJ].pos.y = p->pos.y;

	MLV_actualise_window();
	return pm;
}

void perso_attaque(map m,perso *p1,persoTab joueurs,int x,int y,int nbJoueurs)
{
	int i;
	for(i=1;i<=nbJoueurs;i++)
	if(x == joueurs[i].pos.x && y == joueurs[i].pos.y)
	{
		joueurs[i].vie -= p1->dmg;
		m[joueurs[i].pos.y][joueurs[i].pos.x] = '3';
	}

}

void perso_nettoyer(int x,int y,map m,persoTab joueurs,int nbJoueurs)
{
	int i;
	MLV_Image *mur = MLV_load_image("../textures/case_mur.png");
	MLV_Image *sol = MLV_load_image("../textures/case_sol.png");
	MLV_Image *knight = MLV_load_image("../textures/knight/knight_walkdown1.png");
	MLV_Image *marksman = MLV_load_image("../textures/marksman/marksman.png");

	MLV_draw_image(sol,x,y);
	if(m[y/40-1	][(x/40)] == '1')
	MLV_draw_image(mur,x,y-40);
	else
	{
		if(m[y/40-1	][(x/40)] == '3')
		{
			MLV_draw_image(sol,x,y-40);
			for(i=1;i<=nbJoueurs;i++)
			{
				if((y/40)-1 == joueurs[i].pos.y && x/40 == joueurs[i].pos.x)
				{
					if(joueurs[i].classe == 'k')
					MLV_draw_image(knight,x+5,y-15-40);
					else if(joueurs[i].classe == 'm')
					MLV_draw_image(marksman,x+5,y-15-40);
				}
			}
		}
		else
		{
			MLV_draw_image(sol,x,y-40);
		}
	}
	// S'il y a un personnage en dessous, on le réaffiche correctement
	if(m[y/40+1	][(x/40)] == '3')
	{
		MLV_draw_image(sol,x,y-40);
		for(i=1;i<=nbJoueurs;i++)
		{
			if((y/40)+1 == joueurs[i].pos.y && x/40 == joueurs[i].pos.x)
			{
				if(joueurs[i].classe == 'k')
				MLV_draw_image(knight,x+5,y-15+40);
				else if(joueurs[i].classe == 'm')
				MLV_draw_image(marksman,x+5,y-15+40);
			}
		}
	}
	MLV_actualise_window();
}

void perso_nettoyerAttaque(map m,persoTab joueurs,int nbJ)
{
	MLV_Image *marksman = MLV_load_image("../textures/marksman/marksman.png");
	MLV_Image *knight = MLV_load_image("../textures/knight/knight_walkdown1.png");
	MLV_Image *sol = MLV_load_image("../textures/case_sol.png");
	int i,j,k;
	for(i=0;i<17;i++)
	{
		for(j=0;j<27;j++)
		{
			if(m[i][j]=='2')
			{
				m[i][j] = '0';
				perso_nettoyer(j*40,i*40,m,joueurs,nbJ);
			}
			if(m[i][j]=='4')
			{

				m[i][j] = '3';
				MLV_draw_image(sol,j*40,i*40);
				for(k=1;k<=nbJ;k++)
				{
					if(i == joueurs[k].pos.y && j == joueurs[k].pos.x)
					{
						if(joueurs[k].classe == 'k')
						MLV_draw_image(knight,(j*40)+5,(i*40)-15);
						if(joueurs[k].classe == 'm')
						MLV_draw_image(marksman,(j*40)+5,(i*40)-15);
					}
				}
			}
		}
	}
}

void personnage_afficherPer(map m,persoTab joueurs,int nbJoueurs)
{
	int i,j,k;
	MLV_Image *sol = MLV_load_image("../textures/case_sol.png");
	MLV_Image *marksman = MLV_load_image("../textures/marksman/marksman.png");
	MLV_Image *knight = MLV_load_image("../textures/knight/knight_walkdown1.png");
	for(i=0;i<17;i++)
	for(j=0;j<27;j++)
	{
		if(m[i][j] == '3')
		{
			MLV_draw_image(sol,j*40,i*40);
			for(k=1;k<=nbJoueurs;k++)
			{
				if(i == joueurs[k].pos.y && j == joueurs[k].pos.x)
				{
					if(joueurs[k].classe == 'm')
					MLV_draw_image(marksman,(j*40)+5,(i*40)-15);
					if(joueurs[k].classe == 'k')
					MLV_draw_image(knight,(j*40)+5,(i*40)-15);
				}
			}
		}
	}
	MLV_actualise_window();
}
