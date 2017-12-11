#ifndef JEUX_C
#define JEUX_C

#include "jeux.h"

void jeux_tour(perso *p,int numJ,persoTab joueurs,map m,int nbJoueurs,int papm[2])
{
	int pa = papm[0];//Point d'attaque du joueur
	int pm = papm[1];//Points de dédéplacement du joueur
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
			if(touche == MLV_KEYBOARD_ESCAPE)
			{
				papm[0] = pa;
				papm[1] = pm;
				jeux_pause(joueurs,m,nbJoueurs,numJ,papm);
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
				if(p->classe == 'm')
				marksman_attaqueA(m,p->pos.x,p->pos.y);
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
	MLV_wait_seconds(3);
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

void jeux_pause(persoTab joueurs,map m, int nbJoueurs, int numJ, int papm[2])
{
	// Longueur et Hauteur des boutons
	int lnBouton = 340;
	int wdBouton = 70;

	// les positions nord-ouest des boutons
	int xBouton = 350;
	int yRes = 200;
	int yExit = 405;
	int ySave = 310;
	int ySaveEx = 520;
	int x = 0;
	int y = 0;
	MLV_Image *pause;

	pause = MLV_load_image("../textures/pause.png");
	MLV_draw_image(pause,0,0);
	MLV_actualise_window();
	MLV_wait_mouse(&x,&y);
	//Save
	if(x>=xBouton && x<xBouton+lnBouton && y>=ySave && y<ySave+wdBouton)
	{
		sauvegarde(m,joueurs,nbJoueurs,numJ,papm);
	}
	//Exit
	if(x>=xBouton && x<xBouton+lnBouton && y>=yExit && y<yExit+wdBouton)
	{
		joueurs[1].vie = 0;
		jeux_fin(joueurs,m,nbJoueurs);
		MLV_clear_window(MLV_COLOR_BLACK);
		MLV_actualise_window();
	}
	//Save & exit
	if(x>=xBouton && x<xBouton+lnBouton && y>=ySaveEx && y<ySaveEx+wdBouton)
	{
		sauvegarde(m,joueurs,nbJoueurs,numJ,papm);
		joueurs[1].vie = 0;
		jeux_fin(joueurs,m,nbJoueurs);
		MLV_clear_window(MLV_COLOR_BLACK);
		MLV_actualise_window();
	}
	//Resume
	if(x>=xBouton && x<xBouton+lnBouton && y>=yRes && y<yRes+wdBouton)
	{

	}
}
#endif
