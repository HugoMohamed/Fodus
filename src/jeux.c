#ifndef JEUX_C
#define JEUX_C

#include "jeux.h"

void jeux_tour(perso *p,int numJ,persoTab joueurs,map m,int nbJoueurs)
{
    int pm = 6; // Les points de mouvement du joueur
    int pa = 1; // Les points d'action du joueur
    int i;
    int mouseX, mouseY;
    MLV_Keyboard_button touche;
    fprintf(stdout,"%d\n",numJ);
    // Tant que le joueur peut se déplacer
    while(pm > 0 || pa > 0)
	if(jeux_fin(joueurs,m,nbJoueurs) == 0)
	{
	    // On gere les evenement du clavier
	    MLV_wait_keyboard(&touche,NULL,NULL);
	    // permet de passer son tours
	    if(touche == MLV_KEYBOARD_p)
	    {
		pa = 0;
		pm = 0;
	    }
	    // on deplace le perso
	    // le pm n'est dépenser que si le déplacement est "réussi"
	    if(touche == MLV_KEYBOARD_q && pm >0)
		pm = perso_deplacer(m,p,numJ,joueurs,0,pm);

	    if(touche == MLV_KEYBOARD_d && pm >0)
		pm = perso_deplacer(m,p,numJ,joueurs,1,pm);

	    if(touche == MLV_KEYBOARD_z && pm >0)
		pm = perso_deplacer(m,p,numJ,joueurs,2,pm);

	    if(touche == MLV_KEYBOARD_s && pm >0)
		pm = perso_deplacer(m,p,numJ,joueurs,3,pm);

	    // s'il choisi d'attaquer
	    if(pa > 0 && touche == MLV_KEYBOARD_a)
	    {
		// On affiche en surbrillance les cases ou il peut attaquer
		for(i=1;i<=3;i++)
		{
		    if(m[p->pos.y][p->pos.x+i] == '0')
		    {
			m[p->pos.y][p->pos.x+i] = '2';
			MLV_draw_filled_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		    }
		    if(m[p->pos.y][p->pos.x+i] == '3')
			MLV_draw_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		    if(m[p->pos.y+i][p->pos.x] == '0')
		    {
			m[p->pos.y+i][p->pos.x] ='2';
			MLV_draw_filled_rectangle(p->pos.x*40,(p->pos.y+i)*40,40,40,MLV_COLOR_GREEN);
		    }
		    if(m[p->pos.y+i][p->pos.x] == '3')
			MLV_draw_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);		
		}

		for(i=-3;i<0;i++)
		{
		    if(m[p->pos.y][p->pos.x+i] == '0')
		    {
			m[p->pos.y][p->pos.x+i] = '2';
			MLV_draw_filled_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		    }
		    if(m[p->pos.y][p->pos.x+i] == '3')
			MLV_draw_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		    if(m[p->pos.y+i][p->pos.x] == '0')
		    {
			m[p->pos.y+i][p->pos.x] = '2';
			MLV_draw_filled_rectangle(p->pos.x*40,(p->pos.y+i)*40,40,40,MLV_COLOR_GREEN);
		    }
		    if(m[p->pos.y+i][p->pos.x] == '3')
			MLV_draw_rectangle((p->pos.x+i)*40,p->pos.y*40,40,40,MLV_COLOR_GREEN);
		
		}
		MLV_actualise_window();

		// On attend qu'il clique sur une des cases

		MLV_wait_mouse(&mouseX,&mouseY);
		mouseX /= 40;
		mouseY /= 40;
		if(m[mouseY][mouseX] == '2' || (m[mouseY][mouseX] == '3' && (mouseY != p->pos.y || mouseX != p->pos.x)))
		{
		    fprintf(stdout,"Attaque !\n");
		    perso_attaque(p,joueurs,mouseX,mouseY,nbJoueurs);
		    pa --;
		    perso_nettoyerAttaque(m,p->pos.x,p->pos.y);
		
		}
		else
		    perso_nettoyerAttaque(m,p->pos.x,p->pos.y);

		// Le perso attaque sur la case selectionnée

	    }
	    // on repete l'operation tant qu'il a le droit de bouger
	}
	else
	{
	    pa = 0;
	    pm = 0;
	}
}


int jeux_fin(persoTab joueurs, map m,int nbJoueurs)
{
    int i;
    for(i=1;i<=nbJoueurs;i++)
	if(joueurs[i].vie <= 0)
	    return i;
    return 0;
}

void jeux_afficherGagnant(int gagnant)
{
    char g[TMAX];
    sprintf(g,"Joueur %d remporte la partie",gagnant);
    MLV_draw_adapted_text_box(
	400,300,g,10,
	MLV_COLOR_RED,MLV_COLOR_WHITE,MLV_COLOR_BLACK,MLV_TEXT_CENTER
	);
    MLV_actualise_window();
}
#endif
