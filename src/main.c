#ifndef MAIN_C
#define MAIN_C

#include "sauvegarde.h"
#include "menu.h"

int main()
{
	map m;
	persoTab joueurs;
	char classe;
	int i,g;
	int nbJoueurs;
	int gagnant = 0;
	int numJ,conti = 1;
	int choixMenu;
	int numG; // Choix de la sauvegarde
	int papm[3] = {2,6};
	MLV_Music *mainTheme = MLV_load_music("../sounds/main.ogg");
	MLV_Image *menu;

	coord c1;
	coord nb;

	// On crée et on affiche le terrain
	MLV_create_window("Fodus Ultimate Battle", "Fodus", 1040, 680);
	MLV_load_image("../textures/test_menu.png");
	menu = MLV_load_image("../textures/mm_studios.png");
	MLV_draw_image(menu,0,0);
	MLV_actualise_window();
	MLV_wait_seconds(2);
	while(conti)
	{
		MLV_init_audio();
		MLV_play_music(mainTheme,1.0,-1);
		choixMenu = menu_afficher();
		if(choixMenu == 5)
		{
			menu_credits();
		}
		if(choixMenu == 4)
		{
			exit(0);
		}
		if(choixMenu == 3)
		{
			numG = sauvegarde_choseSave(1);
			if(numG != 0)
			{
				nb = sauvegarde_charger(m,joueurs,papm,numG);
				numJ = nb.x;
				nbJoueurs = nb.y;
				while((gagnant = jeux_fin(joueurs,m,nbJoueurs)) == 0)
				{
					while(numJ <= nbJoueurs && (gagnant = jeux_fin(joueurs,m,nbJoueurs)) == 0)
					{
						if(joueurs[numJ].etat == 'v')
						jeux_tour(&joueurs[numJ],numJ,joueurs,m,nbJoueurs,papm);
						papm[0] = 2;
						papm[1] = 6;
						numJ++;
					}
					g = numJ - 1;
					numJ = 1;
				}
				if(joueurs[1].vie != -100) //En cas de fin normale
				{
					jeux_afficherGagnant(g);
				}
				MLV_clear_window(MLV_COLOR_BLACK);
				MLV_actualise_window();
				MLV_stop_music(mainTheme);
			}
		}

		if(choixMenu == 1 || choixMenu == 2)
		{

			map_chargerMap("../map/map.txt",m);
			// On crée les différents personnages
			// Singleplayer
			if(choixMenu == 1)
			{
				nbJoueurs = 2;
				c1.x = 3;
				c1.y = 3;
				perso_creerPerso(m,&joueurs[2],&c1,100,20,joueurs,2,'k');
				classe = perso_choixClasse(1);
				c1.x = 10;
				c1.y = 10;
				if(classe == 'k')
				perso_creerPerso(m,&joueurs[1],&c1,100,20,joueurs,2,'k');
				if(classe == 'm')
				perso_creerPerso(m,&joueurs[1],&c1,100,10,joueurs,2,'m');
			}
			// Multiplayer
			if(choixMenu == 2)
			{
				nbJoueurs = jeux_nbJoueurs();
				for(i=1;i<=nbJoueurs;i++)
				{
					c1.x = 3*i;
					c1.y = 3*i;
					classe = perso_choixClasse(i);
					if(classe == 'k')
					perso_creerPerso(m,&joueurs[i],&c1,100,20,joueurs,1,'k');
					if(classe == 'm')
					perso_creerPerso(m,&joueurs[i],&c1,100,10,joueurs,2,'m');
				}
			}
			map_afficherMap(m);
			personnage_afficherPer(m,joueurs,nbJoueurs);
			MLV_actualise_window();
			if(choixMenu == 2)
			{
				while((gagnant = jeux_fin(joueurs,m,nbJoueurs)) == 0)
				{
					numJ = 1;
					while(numJ <= nbJoueurs && (gagnant = jeux_fin(joueurs,m,nbJoueurs)) == 0)
					{
						papm[0] = 2;
						papm[1] = 6;
						if(joueurs[numJ].etat == 'v')
						jeux_tour(&joueurs[numJ],numJ,joueurs,m,nbJoueurs,papm);
						numJ++;
					}
				}
				numJ--;
			}
			if(choixMenu == 1)
			{
				while((gagnant = jeux_fin(joueurs,m,nbJoueurs)) == 0)
				{
					papm[0] = 2;
					papm[1] = 6;
					numJ = 1;
					jeux_tour(&joueurs[1],numJ,joueurs,m,nbJoueurs,papm);
					if((gagnant = jeux_fin(joueurs,m,nbJoueurs)) != 0)
					break;
					numJ = 2;
					ia_approche(m,&joueurs[2],joueurs,6,nbJoueurs);
				}
			}
			if(joueurs[1].vie != -100) //En cas de fin normale
			{
				jeux_afficherGagnant(numJ);
			}
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_actualise_window();
			MLV_stop_music(mainTheme);
		}
	}
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_free_music(mainTheme);
	MLV_actualise_window();
	MLV_wait_seconds( 20 );

	exit(0);

}

#endif
