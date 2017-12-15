#ifndef MENU_C
#define MENU_C

#include "menu.h"

int menu_afficher()
{
	// Longueur et Hauteur des boutons
	int lnBouton = 340;
	int wdBouton = 70;

	// les positions nord-ouest des boutons
	int xBouton = 350;
	int xCredits = 860;
	int yCredits = 625;
	int ySolo = 234;
	int yMulti = 345;
	int yLoad = 456;
	int yQuit = 567;

	int x = 0;
	int y = 0;
	MLV_Image *menu;

	menu = MLV_load_image("../textures/test_menu.png");
	MLV_draw_image(menu,0,0);
	MLV_actualise_window();

	while(1)
	{
		MLV_wait_mouse(&x,&y);

		// Solo
		if(x>=xBouton && x<xBouton+lnBouton && y>=ySolo && y<ySolo+wdBouton)
		return 1;

		// Multi
		if(x>=xBouton && x<xBouton+lnBouton && y>=yMulti && y<yMulti+wdBouton)
		return 2;

		// Charger Partie
		if(x>=xBouton && x<xBouton+lnBouton && y>=yLoad && y<yLoad+wdBouton)
		return 3;

		// Quitter
		if(x>=xBouton && x<xBouton+lnBouton && y>=yQuit && y<yQuit+wdBouton)
		return 4;

		//Credits
		if(x>=xCredits && x<xCredits+158 && y>=yCredits && y<yCredits+41)
		{
			return 5;
		}
	}
}

void menu_credits()
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
