#ifndef MAIN_C
#define MAIN_C

#include "jeux.h"

int main()
{
    map m;
    persoTab joueurs;
    perso p1;
    perso p2;
    int nbJoueurs = 2;
    int gagnant = 0;
    coord c1;
    coord c2;
    c1.x = 2;
    c1.y = 2;
    c2.x = 12;
    c2.y = 12;

	// On crée et on affiche le terrain
    MLV_create_window("Fodus Ultimate Battle", "Fodus", 1040, 680);

    map_chargerMap("../map/map.txt",m);
    map_afficherMap(m);

    // On crée les différents personnages
    perso_creerPerso(m,&p1,&c1,10,10,joueurs,1);
    perso_creerPerso(m,&p2,&c2,10,10,joueurs,2);
    MLV_actualise_window();

    while((gagnant = jeux_fin(joueurs,m,nbJoueurs)) == 0)
    {
	jeux_tour(&p1,joueurs,m,nbJoueurs);
	if((gagnant = jeux_fin(joueurs,m,nbJoueurs)) != 0)
	    break;
	jeux_tour(&p2,joueurs,m,nbJoueurs);
    }

    jeux_afficherGagnant(gagnant);

    MLV_wait_seconds( 20 );

    exit(0);

}

#endif
