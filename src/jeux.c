#ifndef JEUX_C
#define JEUX_C

#include "jeux.h"
#include "menu.h"

void jeux_tour(perso *p,int numJ,persoTab joueurs,map m,int nbJoueurs,int papm[2])
{
	int pa = papm[0];//Point d'attaque du joueur
	int pm = papm[1];//Points de dédéplacement du joueur
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
			pm = perso_deplacer(m,p,numJ,joueurs,0,pm,nbJoueurs);

			if(touche == MLV_KEYBOARD_d && pm >0)
			pm = perso_deplacer(m,p,numJ,joueurs,1,pm,nbJoueurs);

			if(touche == MLV_KEYBOARD_z && pm >0)
			pm = perso_deplacer(m,p,numJ,joueurs,2,pm,nbJoueurs);

			if(touche == MLV_KEYBOARD_s && pm >0)
			pm = perso_deplacer(m,p,numJ,joueurs,3,pm,nbJoueurs);

			// s'il choisi l'attaque A
			if(pa > 0 && touche == MLV_KEYBOARD_a)
			{
				if(p->classe == 'k')
				pa = knight_attaqueA(p,m,joueurs,nbJoueurs,pa);
				if(p->classe == 'm')
				pa = marksman_attaqueA(p,m,joueurs,nbJoueurs,pa);
				MLV_actualise_window();
			}

			// S'il choisi l'attaque E
			if(pa > 0 && touche == MLV_KEYBOARD_e)
			{
				if(p->classe == 'k')
				pa = knight_atkE(p,m,joueurs,nbJoueurs,pa);
				if(p->classe == 'm')
				pa = marksman_atkE(p,m,joueurs,nbJoueurs,pa);
				MLV_actualise_window();
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
	int done = 0;
	int numG; // Numéro de la partie à sauvegarder
	MLV_Image *pause;

	// On affiche le menu pause
	pause = MLV_load_image("../textures/pause.png");
	MLV_draw_image(pause,0,0);
	MLV_actualise_window();
	while(!done)
	{
		MLV_wait_mouse(&x,&y);

		// Save
		if(x>=xBouton && x<xBouton+lnBouton && y>=ySave && y<ySave+wdBouton)
		{
			numG = sauvegarde_choseSave();
			sauvegarde(m,joueurs,nbJoueurs,numJ,papm,numG);
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_actualise_window();
			sauvegarde_charger(m,joueurs,papm,numG);
			done = 1;
		}
		// Exit
		if(x>=xBouton && x<xBouton+lnBouton && y>=yExit && y<yExit+wdBouton)
		{
			// On crée une conditon d'arrêt de la partie
			joueurs[1].vie = -100;
			
			jeux_fin(joueurs,m,nbJoueurs);
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_actualise_window();
			done = 1;
		}
		// Save & exit
		if(x>=xBouton && x<xBouton+lnBouton && y>=ySaveEx && y<ySaveEx+wdBouton)
		{
			numG = sauvegarde_choseSave();
			sauvegarde(m,joueurs,nbJoueurs,numJ,papm,numG);
			joueurs[1].vie = 0;
			jeux_fin(joueurs,m,nbJoueurs);
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_actualise_window();
			done = 1;
		}
		// Resume
		if(x>=xBouton && x<xBouton+lnBouton && y>=yRes && y<yRes+wdBouton)
		{
			sauvegarde(m,joueurs,nbJoueurs,numJ,papm,0);
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_actualise_window();
			sauvegarde_charger(m,joueurs,papm,0);
			done = 1;
		}
	}
}

void jeux_credits()
{
	MLV_Image *credit;
	int exit = 1;
	int x,y;
	int xCredits = 860;
	int yCredits = 625;
	credit = MLV_load_image("../textures/credits.png");
	MLV_draw_image(credit,0,0);
	MLV_actualise_window();
	while(exit)
	{
		MLV_wait_mouse(&x,&y);
		if(x>=xCredits && x<xCredits+158 && y>=yCredits && y<yCredits+41)
		{
			exit = 0;
		}
	}
}
#endif
