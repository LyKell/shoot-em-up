/**
 * \file Explosion.c
 * \brief Module qui gère la liste des explosions
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module qui gère la liste des explosions en l'initialisant, ajoutant des éléments ou les supprimant
 *
 */

#include "../include/Explosion.h"

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>



Explosion* allouer_explosion(int x, int y) {
	Explosion* explosion;
	explosion = (Explosion*) malloc(sizeof(Explosion));

	if (explosion == NULL) {
		fprintf(stderr, "Echec de l'allocation d'une explosion.\n");
		return NULL;
	}

	(*explosion).x = x;
	(*explosion).y = y;
	(*explosion).frame_actuelle = 0;
	(*explosion).suivant = NULL;
	(*explosion).precedent = NULL;

	return explosion;
}


int init_liste_explosion(Liste_explosion* liste_explosion) {
	liste_explosion->tete = NULL;
	liste_explosion->queue = NULL;
	liste_explosion->taille = 0;
	return 1;
}


int ajouter_explosion(Liste_explosion* liste_explosion, int x, int y) {
	Explosion* explosion = allouer_explosion(x, y);

	if (explosion == NULL) {
		return 0;
	}

	if (liste_explosion->queue == NULL) {
		liste_explosion->tete = explosion;
		liste_explosion->queue = explosion;

	} else {
		liste_explosion->queue->suivant = explosion;
		explosion->precedent = liste_explosion->queue;
		liste_explosion->queue = explosion;
	}
	liste_explosion->taille += 1;

	return 1;
}


void actualise_explosion(Liste_explosion* liste_explosion) {
	Explosion* tmp;
	int pos;

	if (liste_explosion->taille != 0) {
		tmp = liste_explosion->tete;
		pos = 1;
		while (tmp != NULL) {
			tmp->frame_actuelle++;

			if (tmp->frame_actuelle >= 8) {
				tmp = supprime_explosion(liste_explosion, tmp, pos);

			} else {
				tmp = tmp->suivant;
				pos++;
			}
		}
	}
}


Explosion* supprime_explosion(Liste_explosion* liste_explosion, Explosion* explosion, int pos) {
	Explosion *supp_element, *renvoi;

	if (liste_explosion->taille == 0) {
		return NULL;
	}

	if (pos == 1) {	// Suppression du premier élément
		supp_element = liste_explosion->tete;
		liste_explosion->tete = liste_explosion->tete->suivant;

		if (liste_explosion->tete == NULL) {
			liste_explosion->queue = NULL;
		} else {
			liste_explosion->tete->precedent = NULL;
		}

	} else if (pos == liste_explosion->taille) {	// Suppression du dernier élément
		supp_element = liste_explosion->queue;
		liste_explosion->queue->precedent->suivant = NULL;	// On casse le lien suivant de l'explosion précédente
		liste_explosion->queue = liste_explosion->queue->precedent;

	} else {	// Suppression ailleurs
		supp_element = explosion;
		explosion->precedent->suivant = explosion->suivant;
		explosion->suivant->precedent = explosion->precedent;
	}

	renvoi = supp_element->suivant;
	free(supp_element);
	liste_explosion->taille--;
	return renvoi;
}


void free_liste_explosion(Liste_explosion* liste_explosion) {
	while (supprime_explosion(liste_explosion, NULL, 1) != NULL);	// Libération de chaque explosion
}

