#ifndef MAIN_C
#define MAIN_C

#include "sauvegarde.h"

int main()
{
  map m;
  persoTab joueurs;
  perso p1;
  perso p2;
  int nbJoueurs = 2;
  int gagnant = 0;
  int numJ;
  coord c1;
  coord c2;
  c1.x = 15;
  c1.y = 4;
  c2.x = 2;
  c2.y = 14;

  // On crée et on affiche le terrain
  MLV_create_window("Fodus Ultimate Battle", "Fodus", 1040, 680);

  map_chargerMap("../map/map.txt",m);
  map_afficherMap(m);

  // On crée les différents personnages
  perso_creerPerso(m,&p1,&c1,50,10,joueurs,1);
  perso_creerPerso(m,&p2,&c2,50,10,joueurs,2);
  MLV_actualise_window();

  while((gagnant = jeux_fin(joueurs,m,nbJoueurs)) == 0)
  {
    numJ = 1;
    jeux_tour(&p1,numJ,joueurs,m,nbJoueurs);
    if((gagnant = jeux_fin(joueurs,m,nbJoueurs)) != 0)
    break;
    numJ = 2;
    ia_approche(m,&p2,joueurs);
    //jeux_tour(&p2,numJ,joueurs,m,nbJoueurs);
  }

  jeux_afficherGagnant(numJ);

  MLV_wait_seconds( 20 );

  exit(0);

}

#endif
