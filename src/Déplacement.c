/**
 * \file Déplacement.c
 * \brief Module qui gère les déplacement des ennemis
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module s'occupant d'insérer des pattern de déplacements.
 *
 */
#include "../include/Déplacement.h"

#include <math.h>


/*
Déplacement tout droit
*/
void pattern_1(Vaisseau* vaisseau, int largeur) {
	vaisseau -> y += vaisseau -> vitesse;
}


/*
Déplacement en diagonale droite
*/
void pattern_2(Vaisseau* vaisseau, int largeur) {
	vaisseau -> x += vaisseau -> vitesse;
	vaisseau -> y += vaisseau -> vitesse;
	if (vaisseau -> x > largeur - LARGEUR_VAISSEAU) {
		vaisseau -> x = largeur - LARGEUR_VAISSEAU;
		vaisseau -> pattern_depl = 3;
	}
}


/*
Déplacement en diagonale gauche
*/
void pattern_3(Vaisseau* vaisseau, int largeur) {
	vaisseau -> x -= vaisseau -> vitesse;
	vaisseau -> y += vaisseau -> vitesse;
	if (vaisseau -> x < 0) {
		vaisseau -> x = 0;
		vaisseau -> pattern_depl = 2;
	}
}


/*
Déplacement en diagonale bas gauche jusqu'à une certaine hauteur 
*/
void pattern_4(Vaisseau* vaisseau, int hauteur, int largeur) {
	vaisseau -> y += vaisseau -> vitesse;
	if (vaisseau -> y >= hauteur / 4) {
		vaisseau -> pattern_depl = 7;
	}

	vaisseau -> x -= vaisseau -> vitesse;
	if (vaisseau -> x < 0) {
		vaisseau -> x = 0;
		vaisseau -> pattern_depl = 5;
	}
}


/*
Déplacement en diagonale bas droite jusqu'à une certaine hauteur 
*/
void pattern_5(Vaisseau* vaisseau, int hauteur, int largeur) {
	vaisseau -> y += vaisseau -> vitesse;
	if (vaisseau -> y >= hauteur / 4) {
		vaisseau -> pattern_depl = 6;
	}

	vaisseau -> x += vaisseau -> vitesse;
	if (vaisseau -> x > largeur - LARGEUR_BOSS) {
		vaisseau -> x = largeur - LARGEUR_BOSS;
		vaisseau -> pattern_depl = 4;
	}
}


/*
Déplacement en diagonale haut droite jusqu'à une certaine hauteur 
*/
void pattern_6(Vaisseau* vaisseau, int largeur) {
	vaisseau -> y -= vaisseau -> vitesse;
	if (vaisseau -> y <= 0) {
		vaisseau -> y = 0;
		vaisseau -> pattern_depl = 5;
	}

	vaisseau -> x += vaisseau -> vitesse;
	if (vaisseau -> x > largeur - LARGEUR_BOSS) {
		vaisseau -> x = largeur - LARGEUR_BOSS;
		vaisseau -> pattern_depl = 7;
	}
}


/*
Déplacement en diagonale haut gauche jusqu'à une certaine hauteur 
*/
void pattern_7(Vaisseau* vaisseau, int largeur) {
	vaisseau -> y -= vaisseau -> vitesse;
	if (vaisseau -> y <= 0) {
		vaisseau -> y = 0;
		vaisseau -> pattern_depl = 4;
	}

	vaisseau -> x -= vaisseau -> vitesse;
	if (vaisseau -> x < 0) {
		vaisseau -> x = 0;
		vaisseau -> pattern_depl = 6;
	}
}

/*
Déplacement en sinus à gauche 
*/
void pattern_8(Vaisseau* vaisseau, int hauteur, int largeur) {
	vaisseau -> y += sin(vaisseau -> x / 20) * (vaisseau -> vitesse + 2);
	if (vaisseau -> y <= 0) {
		vaisseau -> y = 0;
	}
	else{
		if (vaisseau -> y >= hauteur / 4) {
			vaisseau -> y = hauteur / 4;
		}
	}

	if (vaisseau -> x  - vaisseau -> vitesse <=  0) {
		vaisseau -> pattern_depl = 9;
	}
	else {
		vaisseau -> x -= vaisseau -> vitesse;
	}
}

/*
Déplacement en sinus à droite 
*/
void pattern_9(Vaisseau* vaisseau, int hauteur, int largeur) {
	vaisseau -> y -= sin(vaisseau -> x / 20) * (vaisseau -> vitesse + 2);
	if (vaisseau -> y <= 0) {
		vaisseau -> y = 0;
	}
	else{
		if (vaisseau -> y >= hauteur / 4) {
			vaisseau -> y = hauteur / 4;
		}
	}

	if (vaisseau -> x + vaisseau -> vitesse > largeur - LARGEUR_BOSS) {
		vaisseau -> pattern_depl = 8;
	}
	else {
		vaisseau -> x += vaisseau -> vitesse;
	}
}


void gestion_deplacement(Vaisseau* vaisseau, int hauteur, int largeur) {
	switch (vaisseau -> pattern_depl) {
		case 1:
			pattern_1(vaisseau, largeur);
			break;
		case 2:
			pattern_2(vaisseau, largeur);
			break;
		case 3:
			pattern_3(vaisseau, largeur);
			break;
		case 4:
			pattern_4(vaisseau, hauteur, largeur);
			break;
		case 5:
			pattern_5(vaisseau, hauteur, largeur);
			break;
		case 6:
			pattern_6(vaisseau, largeur);
			break;
		case 7:
			pattern_7(vaisseau, largeur);
			break;
		case 8:
			pattern_8(vaisseau, hauteur, largeur);
			break;
		case 9:
			pattern_9(vaisseau, hauteur, largeur);
			break;
	}
}
