#ifndef __SOUND__
#define __SOUND__
	/**
	 * \file Sound.h
	 * \brief Module qui gère le son du jeu
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module s'occupant d'initialiser les sons et musiques du jeu
	 *
	 */

	#include <MLV/MLV_all.h>

	/**
	 * \fn MLV_Music* background_music()
	 * \brief Charge une musique
	 * \return La musique qui a été chargée
	 */
	MLV_Music* background_music();


	/**
	 * \fn void joue_musique(MLV_Music* music)
	 * \brief Joue une musique
	 * \param music La musique qui sera jouée
	 */
	void joue_musique(const MLV_Music* music);


	/**
	 * \fn MLV_Sound* charge_son()
	 * \brief Fonction qui charge un son pour la suite
	 * \return Le son qui a été chargé
	 */
	MLV_Sound* charge_son();


	/**
	 * \fn void joue_son(MLV_Sound* son)
	 * \brief Fonction qui met en route un son
	 * \param son Le son qui sera joué
	 */
	void joue_son(const MLV_Sound* son);

#endif
