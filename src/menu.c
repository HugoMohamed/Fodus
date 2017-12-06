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
	int ySolo = 234;
	int yMulti = 345;
	int yLoad = 456;
	int yQuit = 567;

	int x = 0;
	int y = 0;
	MLV_Image *menu;

	menu = MLV_load_image("../textures/mm_studios.png");
	MLV_draw_image(menu,0,0);
	MLV_actualise_window();
	MLV_wait_seconds(2);

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
	}
}

#endif
