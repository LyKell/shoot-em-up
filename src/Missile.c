/**
 * \file Missile.c
 * \brief Module qui gère la liste des missiles
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module qui gère la liste des missiles en l'initialisant, ajoutant des éléments ou les supprimant
 *
 */
 
#include <stdlib.h>
#include <math.h>

#include "../include/Missile.h"
#include "../include/Tir.h"

#define DUREE_VIE_TETE_CHERCHEUSE 150

/*
Fonction qui alloue un nouveau missile avec pour coordonées (x, y) et dont la direction,
la vitesse et le pattern
*/
Missile* allouer_noeud(int x, int y, double direction, int vitesse, int pattern_tir) {
	Missile *missile;

	missile = (Missile*) malloc(sizeof (Missile));
	if (missile == NULL) {
		return NULL;
	}
	
	(*missile).x = x;
	(*missile).y = y;
	(*missile).direction = direction;
	(*missile).vitesse = vitesse;
	(*missile).suivant = NULL;
	(*missile).precedent = NULL;
	(*missile).pattern_tir = pattern_tir;
	(*missile).duree_vie = DUREE_VIE_TETE_CHERCHEUSE;
	
	return missile;
}


int init_liste_missile(Liste_missile* liste_missile) {
	liste_missile -> tete = NULL;
	liste_missile -> queue = NULL;
	liste_missile -> taille = 0;
	return 1;
}


int ajout_missile(Liste_missile* liste_missile, int x, int y, double direction, int vitesse, int pattern_tir) {
	Missile *missile = allouer_noeud(x, y, direction, vitesse, pattern_tir);
	if (missile == NULL) {
		return 0;
	}
	
	if (liste_missile -> queue == NULL) {
		liste_missile -> tete = missile;
		liste_missile -> queue = missile;
	} else {
		liste_missile -> queue -> suivant = missile;
		missile -> precedent = liste_missile -> queue;
		liste_missile -> queue = missile;
	}
	liste_missile -> taille += 1;
	return 1;
}


Missile* supprime_missile(Liste_missile* liste_missile, Missile* missile, int pos) {
	Missile *supp_element, *renvoi;

	if (liste_missile->taille == 0) {
		return NULL;
	}

	if (pos == 1) { /* suppresion du premier élément */
		supp_element = liste_missile->tete;
		liste_missile->tete = liste_missile->tete->suivant;

		if (liste_missile->tete == NULL) {
			liste_missile->queue = NULL;
		} else {
			liste_missile->tete->precedent = NULL;
		}

	} else if (pos == liste_missile->taille) { /* suppression du dernier élément */
		supp_element = liste_missile->queue;
		liste_missile->queue->precedent->suivant = NULL;
		liste_missile->queue = liste_missile->queue->precedent;

	} else { /* suppression ailleurs */
		supp_element = missile;
		missile -> precedent -> suivant = missile -> suivant;
		missile -> suivant -> precedent = missile -> precedent;
	}

	renvoi = supp_element -> suivant;
	free(supp_element);
	liste_missile->taille--;
	return renvoi;
}


double angle_tir(int x1, int y1, int x2, int y2) {	
	if (x1 == x2) {
		if (y1 > y2) {
			return 3 * M_PI_2;
		}
		return M_PI_2;
	}
	if (x1 > x2) {
		return M_PI + atan((double)(y1- y2) / (x1 - x2));
	}

	return atan((double)(y2- y1) / (x2 - x1));
}


int actualise_missile(Liste_missile* liste_missile, int hauteur, int largeur, int x, int y) {
	Missile* tmp;
	int pos;
	
	if (liste_missile -> taille != 0) {
		tmp = liste_missile -> tete;
		pos = 1;
		while (tmp != NULL) {
			gestion_tir(tmp, x, y);
			if (tmp -> x < 0 || tmp -> y < 0 || tmp -> x > largeur || tmp -> y > hauteur || tmp -> duree_vie == 0) {
				tmp = supprime_missile(liste_missile, tmp, pos);
			} else {
				tmp = tmp -> suivant;
				pos += 1;
			}
		}
	}
	return 1;
}

void free_liste_missile(Liste_missile* liste_missile) {
	while (supprime_missile(liste_missile, NULL, 1) != NULL); /* Libération de chaque missile */
}
