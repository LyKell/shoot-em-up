#ifndef __EVENEMENT__
#define __EVENEMENT__

	#include <MLV/MLV_all.h>

	/**
	 * \file Evenement.h
	 * \brief Module gérant les interractions joueur/clavier
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module contenant une fonction de gestion des touches selon leurs états.
	 *
	 */

	/**
	 * \enum Touche
	 * \brief Constantes de touche.
	 *
	 * Touche est une série de constantes prédéfinie pour diverses touches 
	 */
	typedef enum {
		UP,
		LEFT,
		RIGHT,
		DOWN,
		SPACE,
		E,
		A
	} Touche;


	/**
	 * \fn void gestion_touche(int touche[], MLV_Keyboard_button keysym, MLV_Button_state state)
	 * \brief Fonction qui gère la touche pressée et qui l'integre dans un tableau de touche
	 * \param touche Le tableau de touches
	 *        keysym La touche fournie
	 *        state  L'état de la touche
	 */
	void gestion_touche(int touche[], MLV_Keyboard_button keysym, MLV_Button_state state);


	/**
	 * \fn void remise_zero_touche(int touche[])
	 * \brief Fonction qui remet à 0 toutes les touches du tableau
	 * \param touche Le tableau de touches
	 */
	void remise_zero_touche(int touche[]);

#endif
