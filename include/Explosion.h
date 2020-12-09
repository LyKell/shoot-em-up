#ifndef __Explosion__
#define __Explosion__
	/**
	 * \file Explosion.h
	 * \brief Module qui gère la liste des explosions
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module qui gère la liste des explosions en l'initialisant, ajoutant des éléments ou les supprimant
	 *
	 */
	 
	#include "Sound.h"

	/**
	 * \struct Explosion
	 * \brief Structure d'une explosion.
	 *
	 * Explosion est une structure contenant les coordonnées d'une explosion, le numéro de frame à afficher
	 * et deux pointeurs (explosions suivantes et précédentes) 
	 * 
	 */
	typedef struct explosion {
		int x;	// Coordonnée X du vaisseau détruit
		int y;	// Coordonnée Y du vaisseau détruit
		int frame_actuelle;	// Numéro de la frame à afficher de l'explosion
		struct explosion *suivant;	// Explosion suivante dans la liste
		struct explosion *precedent;	// Explosion précédente dans la liste
	} Explosion;


	/**
	 * \struct Liste_explosion
	 * \brief Structure des explosions.
	 *
	 * Liste_explosion est une structure contenant l'explosion de tete et celle de queue 
	 * Elle contient également le nombre d'explosions existantes
	 * 
	 */
	typedef struct {
		struct explosion *tete;	// Première explosion de la liste
		struct explosion *queue;	// Dernière explosion de la liste
		int taille;	// Nombre d'explosion dans la liste
	} Liste_explosion;
	


	/**
	 * \fn Explosion* allouer_explosion(int x, int y)
	 * \brief Alloue la place nécessaire pour une explosion de coordonnée (x, y)
	 * \param  x La coordonnée X de l'explosion
	 *         y La coordonnée Y de l'explosion
	 * \return   L'explosion allouée
	 */
	Explosion* allouer_explosion(int x, int y);


	/**
	 * \fn int init_liste_explosion(Liste_explosion* liste_explosion)
	 * \brief Initialise la liste des explosions
	 * \param  liste_explosion La liste chaînée contenant les explosions à initialiser
	 * \return                 1
	 */
	int init_liste_explosion(Liste_explosion* liste_explosion);


	/**
	 * \fn int ajouter_explosion(Liste_explosion* liste_explosion, int x, int y)
	 * \brief Ajoute une explosion à la liste des explosions
	 * \param  liste_explosion La liste chaînée contenant les explosions
	 *         x               La coordonnée X de l'explosion
	 *         y               La coordonnée Y de l'explosion
	 * \return                 0 si l'explosion n'a pas pu être ajoutée, 1 sinon
	 */
	int ajouter_explosion(Liste_explosion* liste_explosion, int x, int y);


	/**
	 * \fn void actualise_explosion(Liste_explosion* liste_explosion)
	 * \brief Met à jour la frame à afficher de chaque explosion et enclenche sa suppression si nécessaire
	 * \param liste_explosion La liste chaînée contenant les explosions
	 */
	void actualise_explosion(Liste_explosion* liste_explosion);


	/**
	 * \fn Explosion* supprime_explosion(Liste_explosion* liste_explosion, Explosion* explosion, int pos);
	 * \brief Supprime une explosion de la liste d'explosions
	 * \param  liste_explosion La liste chaînée contenant les explosions
	 *         explosion       L'explosion à supprimer
	 *         pos             La position de l'explosion dans la liste
	 * \return                 L'adresse de l'explosion suivante
	 */
	Explosion* supprime_explosion(Liste_explosion* liste_explosion, Explosion* explosion, int pos);


	/**
	 * \fn void free_liste_explosion(Liste_explosion* liste_explosion)
	 * \brief Libère la place allouée aux explosions
	 * \param liste_explosion La liste chaînée contenant les explosions à libérer
	 */
	void free_liste_explosion(Liste_explosion* liste_explosion);


#endif
