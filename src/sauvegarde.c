#ifndef SAUVERGARDE_C
#define SAUVERGARDE_C

#include "sauvegarde.h"

void sauvegarde(map m,persoTab joueurs,int nbJoueurs,int numJ,int papm[2])
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

int sauvegarde_charger(char *cheminMap,char *cheminPers,map m,persoTab joueurs,int papm[2])
{
	int numJ;
	int i = 1,vie,dmg,x,y,nbJoueurs;
	char attributs[15],c;
	FILE* savePers = fopen(cheminPers,"r");

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

	fclose(savePers);
	MLV_actualise_window();
	return numJ;
}

#endif
