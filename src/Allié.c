/**
 * \file Allié.c
 * \brief Module contenant les informations propres à un joueur
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module contenant les fonctions d'initialisation, de déplacement et de 
 * libération de l'Allié.
 * 
 */
 
#include "../include/Allié.h"
#include "../include/Evenement.h"

#include <math.h>


int init_allie(Allie* joueur, int hauteur, int largeur) {
	joueur -> vaisseau = alloue_vaisseau(largeur / 2 - LARGEUR_VAISSEAU / 2, hauteur - HAUTEUR_VAISSEAU, 1, HP);
	if (joueur -> vaisseau == NULL) { /* Allocation échoué */
		return 0;
	}

	init_liste_missile(&(joueur -> missiles)); /* Aucune allocation dynamique ici */
	joueur -> score = 0;
	joueur -> temps = 0;
	joueur -> turbo = 0;
	joueur -> ax = 0;
	joueur -> ay = 0;	

	return 1;
}


void action_touche(Allie* joueur, int touche[], double accum,  int hauteur, int largeur) {
	joueur -> turbo -= accum; /* Valeur du turbo dépend du temps accumulé */
	joueur -> vaisseau -> recharge -= accum; /* Valeur de rechargement dépend du temps accumulé */

	/* Gestion de l'accélération */
	joueur -> vaisseau -> y += joueur -> ay; 
	joueur -> vaisseau -> x += joueur -> ax;

	if (touche[UP]) {
		joueur -> ay -= 0.2;
		joueur -> vaisseau -> y -= joueur -> vaisseau -> vitesse;
	}
	if (touche[DOWN]) {
		joueur -> ay += 0.2;
		joueur -> vaisseau -> y += joueur -> vaisseau -> vitesse;
	}
	if (touche[LEFT]) {
		joueur -> ax -= 0.2;
		joueur -> vaisseau -> x -= joueur -> vaisseau -> vitesse;
	}
	if (touche[RIGHT]) {
		joueur -> ax += 0.2;
		joueur -> vaisseau -> x += joueur -> vaisseau -> vitesse;
	}
	if (touche[SPACE] && joueur -> vaisseau -> recharge <= 0) { /* Si le temps de recharge est écoulé, on peut tirer (evite le spam) */
		ajout_missile(&(joueur -> missiles), 
					  joueur -> vaisseau -> x + TAILLE_MISSILE / 2, 
					   joueur -> vaisseau -> y - TAILLE_MISSILE, 
						3 * M_PI_2, joueur -> vaisseau -> vitesse, 1);
		joueur -> vaisseau -> recharge = 0.3;
	}
	if (touche[E] && joueur -> turbo <= 0) {
		joueur -> vaisseau -> vitesse += 1;
		joueur -> turbo = 0.25;
	}
	if (touche[A] && joueur -> turbo <= 0) {
		joueur -> vaisseau -> vitesse -= 1;
		if (joueur -> vaisseau -> vitesse < 1) {
			joueur -> vaisseau -> vitesse = 1;
		} else {
			joueur -> turbo = 0.25;
		}
	}

	/* Traitement de l'inertie */
	joueur -> ax = joueur -> ax > 0 ? joueur -> ax - 0.09 : joueur -> ax < 0 ? joueur -> ax + 0.09 : 0;
	joueur -> ay = joueur -> ay > 0 ? joueur -> ay - 0.09 : joueur -> ay < 0 ? joueur -> ay + 0.09 : 0;
	joueur -> ax >= -0.1 && joueur -> ax <= 0.1 ? joueur -> ax = 0 : 1;
	joueur -> ay >= -0.1 && joueur -> ay <= 0.1 ? joueur -> ay = 0 : 1;

	/* Gérer les sorties d'écran */
	if (joueur -> vaisseau -> y < 0) {
		joueur -> vaisseau -> y = 0;
		joueur -> ay = 0;

	} else {
		if (joueur -> vaisseau -> y > hauteur - HAUTEUR_VAISSEAU) {
			joueur -> vaisseau -> y = hauteur - HAUTEUR_VAISSEAU;
			joueur -> ay = 0;
		}
	}

	if (joueur -> vaisseau -> x < 0) {
		joueur -> vaisseau -> x = 0;
		joueur -> ax = 0;

	} else {
		if (joueur -> vaisseau -> x > largeur - LARGEUR_VAISSEAU) {
			joueur -> vaisseau -> x = largeur - LARGEUR_VAISSEAU;
			joueur -> ax = 0;
		}
	}
}


void free_allie(Allie* joueur) {
	free(joueur -> vaisseau); /* Libération du vaisseau */
	free_liste_missile(&(joueur -> missiles)); /* Suppression de l'espace de chaque missile */
}
