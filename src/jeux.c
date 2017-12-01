#ifndef JEUX_C
#define JEUX_C

#include "jeux.h"

void jeux_tour(perso *p, map *m)
{
    int pm = 6; // Le nombre de point de mouvement du joueur

    while(pm != 0)
    {
        // On gere les evenement du clavier
	MLV_Keyboard_button touche = 0;
    
	while(touche != MLV_KEYBOARD_z || touche != MLV_KEYBOARD_s || touche != MLV_KEYBOARD_q || touche != MLV_KEYBOARD_d)
	    MLV_wait_keyboard(&touche,NULL,NULL);
    
	// on deplace le perso
	if(touche != MLV_KEYBOARD_q)
	    perso_deplacer(m,p,0);
	else if(touche != MLV_KEYBOARD_d)
	    perso_deplacer(m,p,1);
	else if(touche != MLV_KEYBOARD_z)
	    perso_deplacer(m,p,2);
	else
	    perso_deplacer(m,p,3);

	pm --;
    }
}


#endif
