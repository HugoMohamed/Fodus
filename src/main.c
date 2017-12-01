#ifndef MAIN_C
#define MAIN_C

#include "jeux.h"

int main()
{
    map m;
    coord c;
    perso p;
    c.x = 40;
    c.y = 40;
    MLV_create_window("fodus", "fodus", 1040, 720);
    
    map_chargerMap("../map/map.txt",m);
    map_afficherMap(m);
    perso_creerPerso(&p,&c,100,10);

    MLV_actualise_window();
    MLV_wait_seconds( 20 );

    exit(0);

}

#endif
