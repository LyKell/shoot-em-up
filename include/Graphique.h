#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__
	
	/**
	 * \file Graphique.h
	 * \brief Module qui gère l'affichage graphique
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module s'occupant d'afficher les menus, la fenêtre du jeu, les éléments du jeu
	 *
	 */
	
	#include "Ennemi.h"
	#include "Allié.h"
	#include "Menu.h"
	#include "Explosion.h"
	
	#define LARGEUR_FENETRE (LARGEUR + 213)
	#define LARGEUR_HIGHSCORE (LARGEUR_FENETRE / 2)
	#define LARGEUR 640
	#define HAUTEUR 480
	#define MENU_W_ORIG 450
	#define MENU_H_ORIG 120
	#define MAIN_MENU 0
	#define HIGHSCORE_MENU 1


	/**
	 * \fn void init_tab_image(Option option)
	 * \brief Fonction qui initialise un tableau d'image
	 * \param option La liste chaînée contenant les options
	 */
	void init_tab_image(Option option);


	/**
	 * \fn void free_tab_image()
	 * \brief Fonction qui libère l'espace mémoire utilisée par le tableau d'images
	 */
	void free_tab_image();


	/**
	 * \fn void init_tab_explosion()
	 * \brief Initialise le tableau contenant les frames des explosions
	 */
	void init_tab_explosion();


	/**
	 * \fn void free_tab_explosion()
	 * \brief Libère l'espace mémoire utilisée par le tableau des frames d'explosion
	 */
	void free_tab_explosion();


	/**
	 * \fn void cree_fenetre()
	 * \brief Fonction qui crée une fenetre de jeu
	 */
	void cree_fenetre();


	/**
	 * \fn void dessine_fenetre(const Allie* joueur, const Liste_ennemi* liste_ennemi, const Liste_ennemi* boss, const Liste_explosion* liste_explosion, int* y, int* nb_alea, int hp_vaisseau, int temps_ecoule)
	 * \brief Fonction qui dessine l'ensemble de la fenêtre de jeu
	 * \param joueur          L'adresse de la structure de l'allié
	 *        liste_ennemi    L'adresse de la strucutre des ennemis
	 *        boss            L'adresse de la structure des boss
	 *        liste_explosion L'adresse de la structure des explosions
	 *        y               L'entier de défilement de l'écran
	 *        nb_alea		  Un entier permettant de choisir un boss aléatoirement
	 *        hp_vaisseau	  La vie totale du vaisseau
	 *        temps_ecoule    Le temps écoulé depuis le début de la partie
	 */
	void dessine_fenetre(const Allie* joueur, const Liste_ennemi* liste_ennemi, const Liste_ennemi* boss, const Liste_explosion* liste_explosion, int* y, int* nb_alea, int hp_vaisseau, int temps_ecoule);


	/**
	 * \fn void dessine_menu(Option option, int valeur)
	 * \brief Dessine l'intégralité du menu
	 * \param option La liste chaînée contenant les options à afficher
	 *        valeur Une valeur indiquant quel menu afficher (0 - Principal / 1 - Highscore)
	 */
	void dessine_menu(Option option, int valeur);


	/**
	 * \fn void recupere_taille_options(Option option)
	 * \brief Récupère la taille des images du menu (Start, Highscore, Quit et Back)
	 * \param option La liste chaînée contenant les options
	 */
	void recupere_taille_options(Option option);


	/**
	 * \fn void dessine_options(Option option, int valeur)
	 * \brief Dessine les options selon leur état (survolé ou non) et du menu actuel (Principal ou Highscore)
	 * \param option La liste chaînée contenant les options
	 *        valeur Une valeur indiquant dans quel menu on se trouve (0 - Principal / 1 - Highscore)
	 */
	void dessine_options(Option option, int valeur);


	/**
	 * \fn void dessine_highscore_dans_menu()
	 * \brief Affiche sur le menu Highscore les scores
	 */
	void dessine_highscore_dans_menu();


	/**
	 * \fn int survole_et_selectionne_option(Option option, int valeur)
	 * \brief Indique à une option qu'on la survole à la souris
	 * \param  option La liste chaînée contenant les options
	 *         valeur Une valeur indiquant dans quel menu on se trouve (0 - Principale / 1 - Highscore)
	 * \return        La valeur de l'option survolée (définie par selectionne_option), -1 si on ne survole aucune option
	 */
	int survole_et_selectionne_option(Option option, int valeur);


	/**
	 * \fn int survole_option(Option tmp, Option option)
	 * \brief Change l'état de l'option et la sélectionne pour y accéder
	 * \param  tmp    La liste chaînée contenant les options
	 *         option L'option sélectionnée
	 * \return        La valeur de l'option survolée (définie par selectionne_option), -1 si on ne survole aucune option
	 */
	int survole_option(Option tmp, const Option option);


	/**
	 * \fn int selectionne_option(char* titre)
	 * \brief Sélectionne une option
	 * \param  titre Le nom de l'option sélectionnée
	 * \return       La valeur de l'option survolée
	 *                  - 0 : Quit
	 *                  - 1 : Start
	 *                  - 2 : Highscore
	 *                  - 3 : Back
	 */
	int selectionne_option(char* titre);


	/**
	 * \fn void sauvegarde_nom_joueur_pour_highscore(char** nom_joueur)
	 * \brief Fonction qui demande au joueur d'entrer un nom pour son score
	 * \param nom_joueur L'adresse du nom du joueur
	 */
	void sauvegarde_nom_joueur_pour_highscore(char** nom_joueur);

#endif
