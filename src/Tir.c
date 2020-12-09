/**
 * \file Tir.c
 * \brief Module qui gère les tirs des ennemis
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module s'occupant d'insérer des pattern de tirs.
 *
 */
#include "../include/Tir.h"
#include "../include/Vaisseau.h"

#include <math.h>

/*
Fonction qui tire selon un angle
*/
void pattern_tir_1(Missile* missile) {
	missile -> x += cos(missile -> direction) * missile -> vitesse;
	missile -> y += sin(missile -> direction) * missile -> vitesse;
}


/*
Fonction qui tire tout droit
*/
void pattern_tir_2(Missile* missile) {
	missile -> y += missile -> vitesse;
}


/*
Fonction qui tire un missile avec tête cherche
*/
void pattern_tir_3(Missile* missile, int x, int y) {
	missile -> x += cos(missile -> direction) * missile -> vitesse;
	missile -> y += sin(missile -> direction) * missile -> vitesse;
	missile -> duree_vie -= 1;
	missile -> direction = angle_tir(missile -> x + TAILLE_MISSILE / 2, 
									  missile -> y + TAILLE_MISSILE / 2, 
									   x + LARGEUR_VAISSEAU / 2, 
										y + HAUTEUR_VAISSEAU / 2);
}


void gestion_tir(Missile* missile, int x, int y) {
	switch(missile -> pattern_tir) {
		case 1:
			pattern_tir_1(missile);
			break;
		case 2:
			pattern_tir_2(missile);
			break;
		case 3:
			pattern_tir_3(missile, x, y);
			break;
	}
}
