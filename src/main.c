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
    MLV_create_window("Fodus Ultimate Battle", "Fodus", 1040, 680);

    map_chargerMap("../map/map.txt",m);
    map_afficherMap(m);
    perso_creerPerso(&p,&c,100,10);
    MLV_actualise_window();

    jeux_tour(&p,m);
    MLV_wait_seconds( 20 );

    exit(0);

}

#endif
