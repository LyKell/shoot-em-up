#ifndef __HIGHSCORE__
#define __HIGHSCORE__

	/**
	 * \file Highscore.h
	 * \brief Module qui gère les meilleurs scores
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module s'occupant d'insérer un meilleur score dans un fichier Highscore .
	 *
	 */

	#include <stdio.h>

	/**
	 * \struct Score
	 * \brief Structure d'un score.
	 *
	 * Score est une structure contenant le score et le nom d'un joueur 
	 * 
	 */
	typedef struct {
		char name[100] ;
		int score;
	} Score;


	/**
	 * \fn int nouveau_score(FILE* fichier, char* nom_joueur, int score);
	 * \brief Fonction qui inscrit un nouveau score dans le fichier highscore
	 * \param  fichier     Le fichier highscore.txt
	 *         nom_joueur Le nom du joueur
	 *         score       Le score du joueur
	 * \return             1
	 */
	int nouveau_score(FILE* fichier, const char* nom_joueur, int score);


	/**
	 * \fn void gestion_highscore(char* nom_joueur, int score)
	 * \brief Fonction qui inscrit le score indiqué et le nom du joueur s'il le mérite ou non
	 * \param nom_joueur Le nom du joueur
	 *        score       Le score du joueur
	 */
	void gestion_highscore(const char* nom_joueur, int score);


#endif
