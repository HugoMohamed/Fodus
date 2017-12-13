#ifndef SAUVERGARDE_C
#define SAUVERGARDE_C

#include "sauvegarde.h"

void sauvegarde(map m,persoTab joueurs,int nbJoueurs,int numJ,int papm[2],int numG)
{
	int i,j;
	FILE* saveMap = NULL;
	FILE* savePers = NULL;
	char saMap[100],saPers[100];

	sprintf(saMap,"../save/saveMap%d.txt",numG);
	sprintf(saPers,"../save/savePers%d.txt",numG);
	saveMap = fopen(saMap,"w");
	savePers = fopen(saPers,"w");
	if(saveMap == NULL || savePers == NULL)
	{
		fprintf(stderr,"Impossible de créer une sauvegarde.");
		exit(-1);
	}

	// Ecris l'état de la map actuelle dans un fichier.
	for(i=0;i<17;i++)
	{
		for(j=0;j<26;j++)
		fputc(m[i][j],saveMap);
		fputc('\n',saveMap);
	}

	// Ecris les attributs des personnages dans un fichier
	// La première ligne correspond au nombre de joueurs et quel joueur doit jouer.
	fprintf(savePers,"%d %d\n",nbJoueurs,numJ);
	// Le deuxième ligne correspond aux pa et pm du joueur dont c'est le tour
	fprintf(savePers,"%d %d\n",papm[0],papm[1]);
	// Chaque ligne correspond a un personnage
	for(i=1;i<=nbJoueurs;i++)
	fprintf(savePers,"%d %d %d %d %c\n",joueurs[i].vie,joueurs[i].dmg,joueurs[i].pos.x,joueurs[i].pos.y,joueurs[i].classe);

	fclose(saveMap);
	fclose(savePers);
}

int sauvegarde_charger(map m,persoTab joueurs,int papm[2],int numG)
{
	int numJ;
	int i = 1,vie,dmg,x,y,nbJoueurs;
	char attributs[15],c;
	FILE* savePers;
	char cheminMap[100], cheminPers[100];
	// On choisit les saveMap et savePers de numéro numG
	sprintf(cheminMap,"../save/saveMap%d.txt",numG);
	sprintf(cheminPers,"../save/savePers%d.txt",numG);
	savePers = fopen(cheminPers,"r");
	if(savePers == NULL)
	{
		fprintf(stderr,"Impossible de charger la partie :\nFichier %s manquant.\n",cheminPers);
		exit(-1);
	}

	// On charge la map
	map_chargerMap(cheminMap,m);
	map_afficherMap(m);

	// On charge les personnages
	fgets(attributs,8,savePers);
	sscanf(attributs,"%d %d",&nbJoueurs,&numJ);
	fgets(attributs,8,savePers);
	sscanf(attributs,"%d %d",&papm[0],&papm[1]);
	while(i<=nbJoueurs)
	{
		fgets(attributs,20,savePers);
		sscanf(attributs,"%d %d %d %d %c",&vie,&dmg,&x,&y,&c);
		joueurs[i].vie = vie;
		joueurs[i].dmg = dmg;
		joueurs[i].pos.x = x;
		joueurs[i].pos.y = y;
		joueurs[i].classe = c;
		i++;
	}
	personnage_afficherPer(m,joueurs,nbJoueurs);
	fclose(savePers);
	MLV_actualise_window();
	return numJ;
}

int sauvegarde_choseSave()
{

	MLV_Image *choix = MLV_load_image("../textures/loadmenu.png");
	// Longueur et Hauteur des boutons
	int lnBouton = 340;
	int wdBouton = 70;

	// les positions nord-ouest des boutons
	int xBouton = 350;
	int x,y;
	int y1 = 123;
	int y2 = 234;
	int y3 = 345;
	int y4 = 456;
	int y5 = 567;
	int xBack = 860;
	int yBack = 625;

	// On affiche le choix des sauvegardes
	choix = MLV_load_image("../textures/loadmenu.png");
	MLV_draw_image(choix,0,0);
	MLV_actualise_window();
	while(1)
	{
		MLV_wait_mouse(&x,&y);

		// Sauvegarde 1
		if(x>=xBouton && x<xBouton+lnBouton && y>=y1 && y<y1+wdBouton)
		{
			return 1;
		}
		// Sauvegarde 2
		if(x>=xBouton && x<xBouton+lnBouton && y>=y2 && y<y2+wdBouton)
		{
			return 2;
		}
		// Sauvegarde 3
		if(x>=xBouton && x<xBouton+lnBouton && y>=y3 && y<y3+wdBouton)
		{
			return 3;
		}
		// Sauvegarde 4
		if(x>=xBouton && x<xBouton+lnBouton && y>=y4 && y<y4+wdBouton)
		{
			return 4;
		}
		// Sauvegarde 5
		if(x>=xBouton && x<xBouton+lnBouton && y>=y5 && y<y5+wdBouton)
		{
			return 5;
		}
		// Back
		if(x>=xBack && x<xBack+158 && y>=yBack && y<yBack+41)
		{
			return 0;
		}
	}
}
#endif
