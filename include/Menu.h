#ifndef __MENU__
#define __MENU__

	/**
	 * \file Menu.h
	 * \brief Module s'occupant des interractions avec le menu
	 * \author BERGERON Youssef SAVANE Kevin
	 * \date 11 Janvier 2020
	 *
	 * Module contenant une liste chainée d'option, qui auront des positions et des états.
	 *
	 */

	/**
	 * \struct Menu
	 * \brief Structure des option.
	 *
	 * Menu est une structure contenant le titre de l'option, le fait qu'elle ait été sélectionné ou non
	 * Elle contient également la taille de l'image de l'option,
	 * la position de l'image par défaut de l'option dans le tableau static
	 * et la position de l'image sélectionnée de l'option dans le tableau static
	 * Enfin, elle contient un pointeur sur une option
	 */
	typedef struct menu {
		char* titre;	// Nom de l'option
		int selection;	// Option sélectionnée ou non
		int width;	// Largeur de l'image de l'option
		int height;	// Hauteur de l'image de l'option
		int position_image;	// Position de l'image par défaut de l'option dans le tableau static
		int position_image_selection;	// Position de l'image sélectionnée de l'option dans le tableau static
		struct menu* suivant;
	} Menu, *Option;


	/**
	 * \fn  Option alloue_option(char* titre)
	 * \brief Alloue la place nécessaire pour une option ayant le nom titre
	 * \param  titre    Le nom de l'option à allouer
	 * \return          L'option allouée
	 */
	Option alloue_option(const char* titre);


	/**
	 * \fn void position_image_dans_option(Option option, int valeur)
	 * \brief Donne à chaque option la position des images correspondantes depuis le tableau static d'image 
	 * \param option La liste chaînée contenant les options
	 *        valeur  La position de l'image par défaut de l'option
	 */
	void position_image_dans_option(Option option, int valeur);


	/**
	 * \fn void ajouter_option(Option* option, char* titre)
	 * \brief Ajout l'option au nom titre dans la liste chaînée option
	 * \param  option La liste chaînée contenant les options
	 *         titre  Le nom de l'option à allouer
	 * \return        La liste chaînée mise à jour
	 */
	void ajouter_option(Option* option, const char* titre);


	/**
	 * \fn void change_selection(Option option, char* titre);
	 * \brief Change le statut de l'option titre de la liste chaînée option en "Sélectionné"
	 * \param option La liste chaînée contenant les options
	 *        titre  Le nom de l'option à modifier
	 */
	void change_selection(Option option, const char* titre);


	/**
	 * \fn void free_options(Option option)
	 * \brief Libère l'espace mémoire allouée à option
	 * \param option La liste chaînée à libérer
	 */
	void free_options(Option option);

#endif

