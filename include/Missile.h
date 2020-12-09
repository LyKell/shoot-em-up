#ifndef __MISSILE__
#define __MISSILE__

	/**
	 * \file Missile.h
	 * \brief Module qui gère la liste des missiles
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module qui gère la liste des missiles en l'initialisant, ajoutant des éléments ou les supprimant
	 *
	 */

	#define TAILLE_MISSILE 16

	/**
	 * \struct Missile
	 * \brief Structure d'un missile.
	 *
	 * Missile est une structure contenant la vie restante du missile, la vitesse de celui-ci.
	 * Elle contient également les pattern de tir et la direction du missile,
	 * les coordonées du missile                                         
	 * et deux pointeurs (sur le missile précédent et le suivant)               
	 */
	typedef struct missile {
		double x;
		double y;
		double direction;
		int vitesse;
		int pattern_tir;
		int duree_vie;
		struct missile *suivant;
		struct missile *precedent;
	} Missile;

	/**
	 * \struct Liste_missile
	 * \brief Structure des missiles.
	 *
	 * Liste_missile est une structure contenant le missile de tete et celui de queue 
	 * Elle contient également le nombre de missiles existants
	 * 
	 */
	typedef struct {
		struct missile *tete;
		struct missile *queue;
		int taille;
	} Liste_missile;


	/** 
	 * \fn int init_liste_missile(Liste_missile* liste_missile)
	 * \brief Fonction qui initialise la liste des missiles (sans allocation)
	 * \param  liste_missile L'adresse de la structure des missiles à initialiser
	 * \return               1
	 */
	int init_liste_missile(Liste_missile* liste_missile);


	/**
	 * \fn 	int ajout_missile(Liste_missile* liste_missile, int x, int y, double direction, int vitesse, int pattern_tir)
	 * \brief Fonction qui ajoute une missile à la liste des missiles
	 * \param  liste_missile L'adresse de la structure des missiles
	 *         x             La coordonnée X du nouveau missile
	 *         y             La coordonnée Y du nouveau missile
	 *         direction     La direction du nouveau missile
	 *         vitesse       La vitesse du nouveau missile
	 *         pattern_tir   Le pattern de tir du nouveau missile
	 * \return               0 si le missile n'a pas pu être initialisé, 1 sinon
	 */
	int ajout_missile(Liste_missile* liste_missile, int x, int y, double direction, int vitesse, int pattern_tir);


	/**
	 * \fn int actualise_missile(Liste_missile* liste_missile, int hauteur, int largeur, int x, int y)
	 * \brief Fonction qui actualise la liste des missiles (leur position)
	 * \param  liste_missile L'adresse de la structure des missiles
	 *         hauteur       La hauteur de la fenêtre
	 *         largeur       La largeur de la fenêtre
	 *         x             La coordonnée X du joueur allié
	 *         y             La coordonnée Y du joueur allié
	 * \return               1
	 */
	int actualise_missile(Liste_missile* liste_missile, int hauteur, int largeur, int x, int y);


	/**
	 * \fn Missile* supprime_missile(Liste_missile* liste_missile, Missile* missile, int pos)
	 * \brief Fonction qui supprime un missile en position pos de la liste des missiles
	 * \param  liste_missile L'adresse de la structure des missiles
	 *         missile       L'adresse du missile à supprimer
	 *         pos           La position du missile dans la liste
	 * \return               L'adresse du missile suivant
	 */
	Missile* supprime_missile(Liste_missile* liste_missile, Missile* missile, int pos);


	/**
	 * \fn void free_liste_missile(Liste_missile* liste_missile)
	 * \brief Fonction qui libère l'espace mémoire occupée par les missiles
	 * \param liste_missile L'adresse de la structure des missiles
	 */
	void free_liste_missile(Liste_missile* liste_missile);
	

	/**
	 * \fn double angle_tir(int x1, int x2, int y1, int y2)
	 * \brief Fonction qui calcule l'angle de tir d'un missile pour viser l'allié
	 * \param  x1 La coordonnée X du tireur
	 *         x2 La coordonnée Y du tireur
	 *         y1 La coordonnée X de la cible
	 *         y2 La coordonnée Y de la cible
	 * \return    L'angle une fois calculé
	 */
	double angle_tir(int x1, int x2, int y1, int y2);
	
#endif
