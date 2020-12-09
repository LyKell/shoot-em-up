#ifndef __ALLIE__
#define __ALLIE__

	/**
	 * \file Allié.h
	 * \brief Module contenant les informations propres à un joueur
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module contenant les fonctions d'initialisation, de déplacement et de 
	 * libération de l'Allié.
	 * 
	 */
	#include "Missile.h"
	#include "Vaisseau.h"

	#define HP 50

	/**
	 * \struct Allie
	 * \brief Structure du Joueur.
	 *
	 * Allie est une structure contenant le vaisseau du joueur et les missiles qu'il a envoyé. 
	 * Le score du joueur, son inertie, son temps de chargement du turbo et
	 * le temps écoulé dans la partie !
	 */
	typedef struct {
		Vaisseau* vaisseau;	/* Vaisseau du joueur */
		Liste_missile missiles;	/* Missiles envoyé par le joueur */
		int score;	/* Nombre d'ennemi tué */
		double turbo;	/* Valeur qui empeche une accélération ou ralentissement trop important */
		double ax;	/* Inertie en x */
		double ay;	/* Inertie en y */
		double temps;	/* Temps survécu */
	} Allie;


	/**
	 * \fn int init_allie(Allie* joueur, int hauteur, int largeur) 
	 * \brief Fonction qui initialise la partie du joueur que l'on contrôlera
	 * \param  joueur  L'adresse de la structure du joueur
	 *         hauteur La hauteur de la fenêtre de jeu
	 *         largeur La largeur de la fenêtre de jeu
	 * \return         0 si l'opération échoue, 1 sinon
	 */
	int init_allie(Allie* joueur, int hauteur, int largeur);


	/**
	 * \fn void free_allie(Allie* joueur)
	 * \brief Fonction qui libère l'espace mémoire utilisée pour le joueur
	 * \param joueur L'adresse de la structure du joueur
	 */
	void free_allie(Allie* joueur);


	/**
	 * \fn void action_touche(Allie* joueur, int touche[], double accum, int hauteur, int largeur)
	 * \brief Fonction qui gère l'action des touches pressées par l'utilisateur
	 * \param joueur  L'adresse de la strucutre du joueur
	 *        touche  Le tableau des touches utilisables
	 *        accum   Le temps écoulé
	 *        hauteur La hauteur de la fenêtre
	 *        largeur La largeur de la fenêtre
	 */
	void action_touche(Allie* joueur, int touche[], double accum, int hauteur, int largeur);

#endif
