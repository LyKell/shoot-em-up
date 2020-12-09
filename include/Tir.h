#ifndef __TIR__
#define __TIR__

	/**
	 * \file Tir.h
	 * \brief Module qui gère les tirs des ennemis
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module s'occupant d'insérer des pattern de tirs.
	 *
	 */

	#include "Missile.h"


	/**
	 * \fn void gestion_tir(Missile* missile, int x, int y)
	 * \brief Fonction qui gère le déplacement d'un missile selon son pattern
	 * \param missile L'adresse de la structure du missile concerné
	 *        x       La coordonnée X du vaisseau du joueur
	 *        y       La coordonnée Y du vaisseau du joueur
	 */
	void gestion_tir(Missile* missile, int x, int y);
 		
#endif
