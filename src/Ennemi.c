/**
 * \file Ennemi.c
 * \brief Module qui gère la liste des ennemis
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module qui gère la liste des ennemis en l'initialisant, ajoutant des éléments ou les supprimant
 *
 */

#include "../include/Ennemi.h"
#include "../include/Déplacement.h"

#include <MLV/MLV_all.h>
#include <math.h>


int init_liste_ennemi(Liste_ennemi* liste_ennemi) {
	liste_ennemi -> taille = 0;
	liste_ennemi -> tete = NULL;
	liste_ennemi -> queue = NULL;
	init_liste_missile(&(liste_ennemi -> missiles));
	return 1;
}


int ajout_ennemi(Liste_ennemi* liste_ennemi, int vie, int largeur) {
	Vaisseau *vaisseau = alloue_vaisseau(
							MLV_get_random_integer(0, largeur - LARGEUR_VAISSEAU), 
							 0,
							  MLV_get_random_integer(1, 3),
							   vie);
	if (vaisseau == NULL) {	/* Erreur d'allocation d'un vaisseau */
		return 0;
	}

	if (liste_ennemi -> queue == NULL) {
		liste_ennemi -> tete = vaisseau;
		liste_ennemi -> queue = vaisseau;
	} else {
		liste_ennemi -> queue -> suivant = vaisseau;
		vaisseau -> precedent = liste_ennemi -> queue;
		liste_ennemi -> queue = vaisseau;
	}

	liste_ennemi -> taille += 1;

	return 1;
}


Vaisseau* supprime_ennemi(Liste_ennemi* liste_ennemi, Vaisseau* vaisseau, int pos, Liste_explosion* liste_explosion) {
	Vaisseau *supp_element, *renvoi;

	if (liste_ennemi->taille == 0) {
		return NULL;
	}

	if (pos == 1) { /* suppresion de 1er élément */
		supp_element = liste_ennemi->tete;
		liste_ennemi->tete = liste_ennemi->tete->suivant;

		if (liste_ennemi->tete == NULL) {
			liste_ennemi->queue = NULL;
		} else {
			liste_ennemi->tete->precedent = NULL;
		}

	} else if (pos == liste_ennemi->taille) { /* suppression du dernier élément */
		supp_element = liste_ennemi->queue;
		liste_ennemi->queue->precedent->suivant = NULL;
		liste_ennemi->queue = liste_ennemi->queue->precedent;

	} else { /* suppression ailleurs */
		supp_element = vaisseau;
		vaisseau -> precedent -> suivant = vaisseau -> suivant;
		vaisseau -> suivant -> precedent = vaisseau -> precedent;
	}

	renvoi = supp_element -> suivant;
	ajouter_explosion(liste_explosion, supp_element->x, supp_element->y);	// Quand un ennemi meurt, on enclenche une explosion
	free(supp_element);
	liste_ennemi->taille--;
	return renvoi;
}


/*
Fonction d'ajout d'un tir d'un ennemi basique
*/
int tir_ennemi(Liste_ennemi* liste_ennemi, Vaisseau* ennemi, const Vaisseau* joueur) {
	if (ennemi -> y + HAUTEUR_VAISSEAU + TAILLE_MISSILE < joueur -> y) {
		if (ajout_missile(&(liste_ennemi -> missiles), 
				ennemi -> x + (LARGEUR_VAISSEAU - TAILLE_MISSILE) / 2,
				 ennemi -> y + HAUTEUR_VAISSEAU + TAILLE_MISSILE,
				  angle_tir(ennemi -> x + (LARGEUR_VAISSEAU - TAILLE_MISSILE) / 2, ennemi ->  y + HAUTEUR_VAISSEAU + TAILLE_MISSILE, joueur -> x + LARGEUR_VAISSEAU / 2, joueur -> y + HAUTEUR_VAISSEAU / 2),
				   ennemi -> vitesse + 2,
					ennemi -> pattern_tir) == 0) {
			return 0;
		}
		ennemi -> recharge = 0.4;
	}
	return 1;
} 


/*
Fonction d'ajout d'un tir d'un boss
*/
int tir_boss(Liste_ennemi* liste_ennemi, Vaisseau* ennemi, const Vaisseau* joueur) {
	int i;
	if (ennemi -> y + HAUTEUR_BOSS + TAILLE_MISSILE < joueur -> y) {
		if (ajout_missile(&(liste_ennemi -> missiles), 
				ennemi -> x + (LARGEUR_BOSS - TAILLE_MISSILE) / 2,
				 ennemi -> y + HAUTEUR_BOSS + 3 * TAILLE_MISSILE / 2,
				  angle_tir(ennemi -> x + (LARGEUR_BOSS - TAILLE_MISSILE) / 2, ennemi ->  y + HAUTEUR_BOSS + TAILLE_MISSILE, joueur -> x + LARGEUR_VAISSEAU / 2, joueur -> y + HAUTEUR_VAISSEAU / 2),
				   ennemi -> vitesse + 3,
					ennemi -> pattern_tir) == 0) {
			return 0;
		}
		ennemi -> recharge = 0.4;
	} else {
		/* Missiles vers le haut */
		for (i = 1; i < 4; i ++) {
			if (ajout_missile(&(liste_ennemi -> missiles), 
				 ennemi -> x + (i - 1) * (LARGEUR_BOSS / 2) - TAILLE_MISSILE / 2,
				  ennemi -> y - 3 * TAILLE_MISSILE / 2,
				   (4 + i) * M_PI_4,
					ennemi -> vitesse + 5,
					 1) == 0) {
				return 0;
			}
		}
		/* Missile sur le coté */
		if (ajout_missile(&(liste_ennemi -> missiles), 
				 ennemi -> x + LARGEUR_BOSS + 3 * TAILLE_MISSILE / 2,
				  ennemi -> y + HAUTEUR_BOSS / 2 - TAILLE_MISSILE / 2,
				   0,
					ennemi -> vitesse + 5,
					 1) == 0) {
				return 0;
			}
		if (ajout_missile(&(liste_ennemi -> missiles), 
				 ennemi -> x - 3 * TAILLE_MISSILE / 2,
				  ennemi -> y + HAUTEUR_BOSS / 2 - TAILLE_MISSILE / 2,
				   M_PI,
					ennemi -> vitesse + 5,
					 1) == 0) {
				return 0;
			}
		ennemi -> recharge = 0.4;
	}
	return 1;
} 


int actualise_ennemi(Liste_ennemi* liste_ennemi, const Vaisseau* joueur, double accum, int hauteur, int largeur, int type, Liste_explosion* liste_explosion) {
	Vaisseau* tmp;
	int pos;
	int point_de_vie_perdu = 0;

	if (liste_ennemi -> taille != 0) {
		tmp = liste_ennemi -> tete;
		pos = 1;
		while (tmp != NULL) {
			tmp -> recharge -= accum;
			gestion_deplacement(tmp, hauteur, largeur);
			if (MLV_get_random_integer(0, 300) == 0 && type == 1) { /* 1 chance sur 300 de changer du tout au tout pour un boss */
				tmp -> pattern_depl = MLV_get_random_integer(4, 10);
				tmp -> pattern_tir = MLV_get_random_integer(1, 4);
			}

			if (tmp -> y < 0 || tmp -> y > hauteur) {
				tmp = supprime_ennemi(liste_ennemi, tmp, pos, liste_explosion);
				point_de_vie_perdu += 2;

			} else {
				if (MLV_get_random_integer(0, 40) == 0 && tmp -> recharge <= 0) { /* 1 chance sur 40 de tirer */
					if (type == 0) {
						if (tir_ennemi(liste_ennemi, tmp, joueur) == 0) {
							return -1;
						}
					} else { 
						if (tir_boss(liste_ennemi, tmp, joueur) == 0) {
							return -1;
						}
					}
				}
				tmp = tmp -> suivant;
				pos += 1;
			}
		}
	}
	return point_de_vie_perdu;
}


void free_liste_ennemi(Liste_ennemi* liste_ennemi, Liste_explosion* liste_explosion) {
	while (supprime_ennemi(liste_ennemi, NULL, 1, liste_explosion) != NULL); /* Libération de chaque ennemi */
	free_liste_missile(&(liste_ennemi -> missiles)); /* Libération de chaque missile */
}
