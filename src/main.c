#ifndef MAIN_C
#define MAIN_C

#include "sauvegarde.h"
#include "menu.h"

int main()
{
	map m;
	persoTab joueurs;
	char classe;
	int i;
	int nbJoueurs = 2;
	int gagnant = 0;
	int numJ,conti = 1;
	int choixMenu;
	int numG; // Choix de la sauvegarde
	int papm[3] = {1,6};
	MLV_Music *mainTheme = MLV_load_music("../sounds/main.ogg");
	MLV_Image *menu;

	coord c1;
	coord c2;
	c1.x = 15;
	c1.y = 15;
	c2.x = 2;
	c2.y = 14;

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
			jeux_credits();
		}
		if(choixMenu == 4)
		{
			exit(0);
		}
		if(choixMenu == 3)
		{
			numG = sauvegarde_choseSave();
			if(numG != 0)
			{
				numJ = sauvegarde_charger(m,joueurs,papm,numG);
				while((gagnant = jeux_fin(joueurs,m,nbJoueurs)) == 0)
				{
					if(numJ == 1)
					{
						jeux_tour(&joueurs[1],numJ,joueurs,m,nbJoueurs,papm);
						if((gagnant = jeux_fin(joueurs,m,nbJoueurs)) != 0)
						break;
						numJ = 2;
					}
					else
					{
						jeux_tour(&joueurs[2],numJ,joueurs,m,nbJoueurs,papm);
						numJ = 1;
					}
					papm[0] = 1;
					papm[1] = 6;
				}
				jeux_afficherGagnant(numJ);
				MLV_clear_window(MLV_COLOR_BLACK);
				MLV_actualise_window();
				MLV_stop_music(mainTheme);
			}
		}
		if(choixMenu == 1 || choixMenu == 2)
		{

			map_chargerMap("../map/map.txt",m);
			// On crée les différents personnages
			if(choixMenu == 1)
			{
				perso_creerPerso(m,&joueurs[1],&c2,100,20,joueurs,2,'k');
				classe = perso_choixClasse();
				if(classe == 'k')
				perso_creerPerso(m,&joueurs[2],&c1,100,20,joueurs,2,'k');
				if(classe == 'm')
				perso_creerPerso(m,&joueurs[2],&c2,50,10,joueurs,2,'m');
			}
			if(choixMenu == 2)
			{
				for(i=1;i<=nbJoueurs;i++)
				{
					classe = perso_choixClasse();
					if(classe == 'k')
					perso_creerPerso(m,&joueurs[i],&c1,100,20,joueurs,1,'k');
					if(classe == 'm')
					perso_creerPerso(m,&joueurs[i],&c2,50,10,joueurs,2,'m');
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
						papm[0] = 1;
						papm[1] = 6;
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
					papm[0] = 1;
					papm[1] = 6;
					numJ = 1;
					jeux_tour(&joueurs[1],numJ,joueurs,m,nbJoueurs,papm);
					numJ = 2;
					ia_approche(m,&joueurs[2],joueurs,6,nbJoueurs);
					papm[0] = 1;
					papm[1] = 6;

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
