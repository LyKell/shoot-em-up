#ifndef __DEPLACEMENT__
#define __DEPLACEMENT__

	/**
	 * \file Déplacement.h
	 * \brief Module qui gère les déplacement des ennemis
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module s'occupant d'insérer des pattern de déplacements.
	 *
	 */
	#include "Vaisseau.h"


	/**
	 * \fn void gestion_deplacement(Vaisseau* vaisseau, int hauteur, int largeur)
	 * \brief Fonction qui gère le déplacement d'un vaisseau au vu de son pattern
	 * \param vaisseau L'adresse de la structure du vaisseau concerné
	 *        hauteur  La hauteur de la fenêtre
	 *        largeur  La largeur de la fenêtre
	 */
	void gestion_deplacement(Vaisseau* vaisseau, int hauteur, int largeur);
 		
#endif
