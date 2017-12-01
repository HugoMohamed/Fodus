#ifndef MAIN_C
#define MAIN_C

#include "map.h"

int main()
{
    map m;
    MLV_create_window("jeux", "jeux", 1040, 720);
    
    map_chargerMap("../map/map.txt",m);
    map_afficherMap(m);

    MLV_actualise_window();
    MLV_wait_seconds( 20 );

    exit(0);
	
}

#endif
