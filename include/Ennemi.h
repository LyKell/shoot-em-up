#ifndef __ENNEMI__
#define __ENNEMI__

	/**
	 * \file Ennemi.h
	 * \brief Module qui gère la liste des ennemis
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module qui gère la liste des ennemis en l'initialisant, ajoutant des éléments ou les supprimant
	 *
	 */
	#include "Vaisseau.h"
	#include "Missile.h"
	#include "Explosion.h"

	#define BOSS 30

	/**
	 * \struct Liste_ennemi
	 * \brief Structure des ennemis.
	 *
	 * Liste_ennemi est une structure contenant le vaisseau de tete des ennemis et celui de queue 
	 * Elle contient également les missiles qu'ils ont envoyé et le nombre d'ennemis vivant
	 * 
	 */
	typedef struct {
		struct vaisseau *tete; /* Vaisseau en tête des ennemis */
		struct vaisseau *queue; /* Vaisseau en queue des ennemis */
		int taille; /* Nombre d'ennemis */
		Liste_missile missiles; /* Missiles tirés par les ennemis */
	} Liste_ennemi;


	/**
	 * \fn Vaisseau* supprime_ennemi(Liste_ennemi* liste_ennemi, Vaisseau* vaisseau, int pos, Liste_explosion* liste_explosion)
	 * \brief Fonction qui supprime un vaisseau en postion pos de la liste ennemis
	 * \param  liste_ennemi   L'adresse de la structure des ennemis
	 *         vaisseau       L'adresse de la structure du vaisseau à supprimer
	 *         pos            La position du vaisseau à supprimer dans la liste
	 *        liste_explosion L'adresse de la structure des explosion
	 * \return                L'adresse du vaisseau suivant
	 */
	Vaisseau* supprime_ennemi(Liste_ennemi* liste_ennemi, Vaisseau* vaisseau, int pos, Liste_explosion* liste_explosion);


	/**
	 * \fn int init_liste_ennemi(Liste_ennemi* liste_ennemi)
	 * \brief Fonction qui initialise la liste des ennemis (sans allocation)
	 * \param  liste_ennemi L'adresse de la structure des ennemis à initialiser
	 * \return              1
	 */
	int init_liste_ennemi(Liste_ennemi* liste_ennemi);


	/**
	 * \fn 	int ajout_ennemi(Liste_ennemi* liste_ennemi, int vie, int largeur)
	 * \brief Fonction qui ajoute une ennemi à la liste des ennemis 
	 * \param  liste_ennemi L'adresse de la structure des ennemis
	 *         vie          La vie du nouvel ennemi
	 *         largeur      La largeur de la fenêtre
	 * \return              0 en cas d'ajout échoué, 1 sinon
	 */
	int ajout_ennemi(Liste_ennemi* liste_ennemi, int vie, int largeur);


	/**
	 * \fn int actualise_ennemi(Liste_ennemi* liste_ennemi, Vaisseau* joueur, double accum, int hauteur, int largeur, int type, Liste_explosion* liste_explosion)
	 * \brief Fonction qui actualise la liste des ennemis (leur position et leur missile)
	 * \param  liste_ennemi   L'adresse de la structure des ennemis
	 *         joueur         L'adresse de la structure du joueur
	 *         accum          Le temps écoulé
	 *         hauteur        La hauteur de la fenêtre
	 *         largeur        La largeur de la fenêtre
	 *         type           Le type de l'ennemi (boss ou ennemi simple)
	 *        liste_explosion L'adresse de la structure des explosions
	 * \return                -1 en cas d'échec, ou les points de vie perdus
	 */
	int actualise_ennemi(Liste_ennemi* liste_ennemi, const Vaisseau* joueur, double accum, int hauteur, int largeur, int type, Liste_explosion* liste_explosion);


	/**
	 * Fonction qui libère l'espace mémoire occupée par les ennemis et leur missile
	 * @param liste_ennemi    L'adresse de la structure des ennemis
	 * @param liste_explosion L'adresse de la structure des explosions
	 */
	void free_liste_ennemi(Liste_ennemi* liste_ennemi, Liste_explosion* liste_explosion);

#endif
