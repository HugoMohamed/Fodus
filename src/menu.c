#ifndef MENU_C
#define MENU_C

#include "menu.h"

void menu_afficher()
{
	MLV_Image *menu;
	menu = MLV_load_image("../textures/mm_studios.png");
	MLV_draw_image(menu,0,0);
	MLV_actualise_window();
	MLV_wait_seconds(3);
	
}

#endif
