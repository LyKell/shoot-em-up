#ifndef __Collision__
#define __Collision__

	/**
	 * \file Collision.h
	 * \brief Module tous ce qui concerne les collisions
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module gérant les collisions entre vaisseau et les collisions missiles/vaisseau.
	 *
	 */
	#include "Ennemi.h"
	#include "Allié.h"
	#include "Sound.h"
	#include "Explosion.h"


	/**
	 * \fn void gestion_collision(Allie* joueur, Liste_ennemi* liste_ennemi, int largeur, int hauteur, Liste_explosion* liste_explosion, MLV_Sound* son)
	 * \brief Fonction qui gère tout type de collision (joueur / ennemis, ennemis / ennemis)
	 * \param joueur          L'adresse de la structure du joueur
	 *        liste_ennemi    L'adresse de la structure des ennemis
	 *        largeur         La largeur de la hitbox de l'ennemi
	 *        hauteur         La hauteur de la hitbox de l'ennemi
	 *        liste_explosion L'adresse de la structure des explosions
	 *        son             Le son produit par une collision
	 */
	void gestion_collision(Allie* joueur, Liste_ennemi* liste_ennemi, int largeur, int hauteur, Liste_explosion* liste_explosion, const MLV_Sound* son);
	
#endif
