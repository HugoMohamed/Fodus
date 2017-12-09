#ifndef JEUX_C
#define JEUX_C

#include "jeux.h"

void jeux_tour(perso *p,int numJ,persoTab joueurs,map m,int nbJoueurs)
{
	int pm = 6; // Les points de mouvement du joueur
	int pa = 1; // Les points d'action du joueur
	int mouseX, mouseY;
	MLV_Keyboard_button touche;
	fprintf(stdout,"%d\n",numJ);
	jeux_hud(joueurs,numJ,pa,pm);
	// Tant que le joueur peut se déplacer
	while(pm > 0 || pa > 0)
	{
		if(jeux_fin(joueurs,m,nbJoueurs) == 0)
		{
			// On gere les evenement du clavier
			MLV_wait_keyboard(&touche,NULL,NULL);
			// permet de passer son tours
			if(touche == MLV_KEYBOARD_p)
			{
				pa = 0;
				pm = 0;
			}
			// on deplace le perso
			// le pm n'est dépenser que si le déplacement est "réussi"
			if(touche == MLV_KEYBOARD_q && pm >0)
			pm = perso_deplacer(m,p,numJ,joueurs,0,pm);

			if(touche == MLV_KEYBOARD_d && pm >0)
			pm = perso_deplacer(m,p,numJ,joueurs,1,pm);

			if(touche == MLV_KEYBOARD_z && pm >0)
			pm = perso_deplacer(m,p,numJ,joueurs,2,pm);

			if(touche == MLV_KEYBOARD_s && pm >0)
			pm = perso_deplacer(m,p,numJ,joueurs,3,pm);

			// s'il choisi d'attaquer
			if(pa > 0 && touche == MLV_KEYBOARD_a)
			{
				if(p->classe == 'k')
				knight_attaqueA(m,p->pos.x,p->pos.y);
				// On affiche en surbrillance les cases ou il peut attaquer
				if(p->classe == 'a')
				archer_attaqueA(m,p->pos.x,p->pos.y);
				MLV_actualise_window();

				// On attend qu'il clique sur une des cases

				MLV_wait_mouse(&mouseX,&mouseY);
				mouseX /= 40;
				mouseY /= 40;
				if(m[mouseY][mouseX] == '2' || m[mouseY][mouseX] == '4')
				{
					fprintf(stdout,"Attaque !\n");
					perso_attaque(m,p,joueurs,mouseX,mouseY,nbJoueurs);
					pa --;
					perso_nettoyerAttaque(m,p->pos.x,p->pos.y,joueurs,nbJoueurs);

				}
				else
				perso_nettoyerAttaque(m,p->pos.x,p->pos.y,joueurs,nbJoueurs);

				// Le perso attaque sur la case selectionnée
			}

			// on repete l'operation tant qu'il a le droit de bouger
		}
		else
		{
			pa = 0;
			pm = 0;
		}
		jeux_hud(joueurs,numJ,pa,pm);
	}
	jeux_hud(joueurs,numJ,pa,pm);
}


int jeux_fin(persoTab joueurs, map m,int nbJoueurs)
{
	int i;
	for(i=1;i<=nbJoueurs;i++)
	if(joueurs[i].vie <= 0)
	return i;
	return 0;
}

void jeux_afficherGagnant(int gagnant)
{
	char g[TMAX];
	sprintf(g,"Joueur %d remporte la partie",gagnant);
	MLV_draw_adapted_text_box(
		400,300,g,10,
		MLV_COLOR_RED,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER
	);
	MLV_actualise_window();
}

void jeux_hud(persoTab joueurs, int numJ, int pa, int pm)
{
	char papm[TMAX],vie[TMAX];
	sprintf(papm,"%d\n%d",pa,pm);
	sprintf(vie,"%d / %d",joueurs[numJ].vie,VIE);
	MLV_draw_text_box(
		500,640,
		50,40,
		papm,5,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_LEFT,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_draw_text_box(
		550,640,
		150,40,
		vie,5,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_LEFT,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();
}
#endif
