#ifndef __VAISSEAU__
#define __VAISSEAU__

	/**
	 * \file Vaisseau.h
	 * \brief Module gérant l'allocation d'un vaisseau
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 */

	#define LARGEUR_VAISSEAU 30
	#define HAUTEUR_VAISSEAU 40
	#define LARGEUR_BOSS 50
	#define HAUTEUR_BOSS 80

	/**
	 * \struct Vaisseau
	 * \brief Structure d'un vaisseau.
	 *
	 * Vaisseau est une structure contenant la vie restante du vaisseau, la vitesse de celui-ci.
	 * Elle contient également les pattern de tir et déplacement des vaisseaux,
	 * les coordonées du vaisseaux, son temps de rechargement de tir       
	 * et deux pointeurs (sur le vaisseau précédent et le suivant)               
	 */
	typedef struct vaisseau{
		int vie;
		int vitesse;
		int pattern_depl;
		int pattern_tir;
		double x;
		double y;
		double recharge;
		struct vaisseau *suivant;
		struct vaisseau *precedent;
	} Vaisseau;


	/**
	 * \fn Vaisseau* alloue_vaisseau(double x, double y, int vitesse, int vie)
	 * \brief Fonction qui alloue un vaisseau en position (x, y) avec une vitesse et une vie donnée
	 * \param  x     La coordonnée X du vaisseau
	 *         y     La coordonnée Y du vaisseau
	 *         vitesse La vitesse du vaisseau
	 *         vie   La vie du vaisseau
	 * \return       Le vaisseau alloué
	 */
	Vaisseau* alloue_vaisseau(double x, double y, int vitesse, int vie);
		
#endif
