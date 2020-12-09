/**
 * \file Vaisseau.c
 * \brief Module gérant l'allocation d'un vaisseau
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 */

#include "../include/Vaisseau.h"
#include <MLV/MLV_all.h>

#include <assert.h>
#include <stdlib.h>


Vaisseau* alloue_vaisseau(double x, double y, int vitesse, int vie){
	Vaisseau *vaisseau;
	
	vaisseau = (Vaisseau*) malloc(sizeof(Vaisseau));
	
	if (vaisseau == NULL){
		exit(EXIT_FAILURE);
	}
	 
	vaisseau -> vie = vie;
	vaisseau -> x = x;
	vaisseau -> y = y;
	vaisseau -> vitesse = vitesse;
	vaisseau -> suivant = NULL;	
	vaisseau -> precedent = NULL;	
	vaisseau -> recharge = 0;	
	vaisseau -> pattern_depl = MLV_get_random_integer(1, 4);
	vaisseau -> pattern_tir = MLV_get_random_integer(1, 4);
	
	return vaisseau;
}
		


