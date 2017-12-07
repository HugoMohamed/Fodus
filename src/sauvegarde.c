#ifndef SAUVERGARDE_C
#define SAUVERGARDE_C

#include "sauvegarde.h"

void sauvegarde(map m,persoTab joueurs,int nbJoueurs,int numJ)
{
	int i,j;
	FILE* saveMap = NULL;
	FILE* savePers = NULL;
	saveMap = fopen("../save/saveMap.txt","w");
	savePers = fopen("../save/savePers.txt","w");

	if(saveMap == NULL || savePers == NULL)
	{
		fprintf(stderr,"Impossible de créer une sauvegarde.");
		exit(-1);
	}

	// Ecris l'état de la map actuelle dans un fichier.
	for(i=0;i<17;i++)
	{
		for(j=0;j<27;j++)
			fputc(m[i][j],saveMap);
		fputc('\n',saveMap);
	}

	// Ecris les attributs des personnages dans un fichier
	// La première ligne correspond au nombre de joueurs et quel joueur doit jouer.
	fprintf(savePers,"%d %d\n",nbJoueurs,numJ);
	// Chaque ligne correspond a un personnage
	for(i=1;i<=nbJoueurs;i++)
		fprintf(savePers,"%d %d %d %d \n",joueurs[i].vie,joueurs[i].dmg,joueurs[i].pos.x,joueurs[i].pos.y);

	fclose(saveMap);
	fclose(savePers);
}

int sauvegarde_charger(char *cheminMap,char *cheminPers,map m,persoTab joueurs)
{
	int numJ;
	int i = 1,vie,dmg,x,y,nbJoueurs;
	char *attributs = "";
	FILE* savePers = fopen(cheminPers,"r");

	if(savePers == NULL)
	{
		fprintf(stderr,"Impossible de charger la partie :\nFichier %s manquant.\n",cheminPers);
		exit(-1);
	}

	// On charge la map
	map_chargerMap(cheminMap,m);

	// On charge les personnages
	nbJoueurs = fgetc(savePers);
	numJ = fgetc(savePers);
	while(i<=nbJoueurs)
	{
		fgets(attributs,8,savePers);
		sscanf(attributs,"%d %d %d %d\n",&vie,&dmg,&x,&y);
		joueurs[i].vie = vie;
		joueurs[i].dmg = dmg;
		joueurs[i].pos.x = x;
		joueurs[i].pos.y = y;
	}

	fclose(savePers);
	return numJ;
}

#endif
