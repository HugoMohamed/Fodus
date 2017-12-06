#ifndef MENU_C
#define MENU_C

#include "menu.h"

void menu_afficher()
{
	int lnBouton = 340;
	int wdBouton = 70;

	int xSolo = 350;
	int ySolo = 234;

	int x = 0;
	int y = 0;
	MLV_Image *menu;

	menu = MLV_load_image("../textures/mm_studios.png");
	MLV_draw_image(menu,0,0);
	MLV_actualise_window();
	MLV_wait_seconds(3);

	menu = MLV_load_image("../textures/test_menu.png");
	MLV_draw_image(menu,0,0);
	MLV_actualise_window();

	while(1)
	{
		MLV_wait_mouse(&x,&y);
		if(x>=xSolo && x<xSolo+lnBouton && y>=ySolo && y<ySolo+wdBouton)
			break;
	}
}

#endif
