#ifndef JEUX_C
#define JEUX_C

#include "jeux.h"
#include "menu.h"

void jeux_tour(perso *p,int numJ,persoTab joueurs,map m,int nbJoueurs,int papm[2])
{
	int pa = papm[0];//Point d'attaque du joueur
	int pm = papm[1];//Points de dédéplacement du joueur
	MLV_Keyboard_button touche;
	jeux_hud(joueurs,numJ,pa,pm,nbJoueurs);
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
		jeux_hud(joueurs,numJ,pa,pm,nbJoueurs);
	}
	jeux_hud(joueurs,numJ,pa,pm,nbJoueurs);
}


int jeux_fin(persoTab joueurs, map m,int nbJoueurs)
{
	int i,nbVivant = 0;
	for(i=1;i<=nbJoueurs;i++)
	{
		if(joueurs[i].vie > 0)
		{
			nbVivant ++;
		}
		if(joueurs[i].vie <= 0)
		{
			joueurs[i].etat = 'm';
			perso_nettoyer((joueurs[i].pos.x)*40,(joueurs[i].pos.y)*40,m,joueurs,nbJoueurs);
			m[joueurs[i].pos.y][joueurs[i].pos.x] = '0';
			joueurs[i].pos.x = i;
			joueurs[i].pos.y = 40;

		}
	}
	if(nbVivant > 1)
	return 0;
	else return i;
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

void jeux_hud(persoTab joueurs, int numJ, int pa, int pm,int nbJoueurs)
{
	MLV_Image *hud = MLV_load_image("../textures/hud.png");
	char tpa[TMAX],tpm[TMAX],vie[TMAX];
	int i;
	sprintf(tpa,"%d",pa);
	sprintf(tpm,"%d",pm);
	MLV_draw_image(hud,0,0);
	for(i=1;i<=nbJoueurs;i++)
	{
		sprintf(vie,"%d / 100",joueurs[i].vie);
		if(i == 1)
		MLV_draw_text(369,12,vie,MLV_COLOR_WHITE);
		if(i == 2)
		MLV_draw_text(842,12,vie,MLV_COLOR_WHITE);
		if(i == 3)
		MLV_draw_text(369,615,vie,MLV_COLOR_WHITE);
		if(i == 4)
		MLV_draw_text(842,615,vie,MLV_COLOR_WHITE);
	}
	if(numJ == 1)
	{
		MLV_draw_text(306,2,tpm,MLV_COLOR_WHITE);
		MLV_draw_text(306,24,tpa,MLV_COLOR_WHITE);
	}
	if(numJ == 2)
	{
		MLV_draw_text(779,2,tpm,MLV_COLOR_WHITE);
		MLV_draw_text(779,24,tpa,MLV_COLOR_WHITE);
	}
	if(numJ == 3)
	{
		MLV_draw_text(306,603,tpm,MLV_COLOR_WHITE);
		MLV_draw_text(306,625,tpa,MLV_COLOR_WHITE);
	}
	if(numJ == 4)
	{
		MLV_draw_text(779,603,tpm,MLV_COLOR_WHITE);
		MLV_draw_text(779,625,tpa,MLV_COLOR_WHITE);
	}
	MLV_actualise_window();
}

void jeux_pause(persoTab joueurs,map m, int nbJoueurs, int numJ, int papm[2])
{
	int i;
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
			numG = sauvegarde_choseSave(0);
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
			for(i=1;i<nbJoueurs;i++)
				joueurs[i].vie = -100;
			jeux_fin(joueurs,m,nbJoueurs);
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_actualise_window();
			done = 1;
		}
		// Save & exit
		if(x>=xBouton && x<xBouton+lnBouton && y>=ySaveEx && y<ySaveEx+wdBouton)
		{
			numG = sauvegarde_choseSave(0);
			sauvegarde(m,joueurs,nbJoueurs,numJ,papm,numG);
			for(i=1;i<nbJoueurs;i++)
				joueurs[i].vie = -100;
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

int jeux_nbJoueurs()
{
	int x,y;
	int wBouton = 70;
	int lnBouton =  360;
	int xBouton = 351;
	int y2 = 234;
	int y3 = 345;
	int y4 = 456;
	MLV_Image *nbJ = MLV_load_image("../textures/nbJoueurs.png");

	MLV_draw_image(nbJ,0,0);
	MLV_actualise_window();
	while(1)
	{
		MLV_wait_mouse(&x,&y);
		// 2
		if(x>=xBouton && x<xBouton+lnBouton && y>=y2 && y<y2+wBouton )
		{
			return 2;
		}
		// 3
		if(x>=xBouton && x<xBouton+lnBouton && y>=y3 && y<y3+wBouton )
		{
			return 3;
		}
		// 4
		if(x>=xBouton && x<xBouton+lnBouton && y>=y4 && y<y4+wBouton )
		{
			return 4;
		}
	}
}

#endif
