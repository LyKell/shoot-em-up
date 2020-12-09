/**
 * \file Menu.c
 * \brief Module s'occupant des interractions avec le menu
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module contenant une liste chainée d'option, qui auront des positions et des états.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Menu.h"


Option alloue_option(const char* titre) {
	Option tmp = (Menu*) malloc(sizeof(Menu));
	if (tmp == NULL) {
		exit(EXIT_FAILURE);
	}

	tmp->titre = (char *) malloc(sizeof(char) * (strlen(titre) + 1));
	if (tmp->titre == NULL) {
		exit(EXIT_FAILURE);
	}

	strcpy(tmp->titre, titre);
	tmp->selection = 0;
	tmp->width = 0;
	tmp->height = 0;
	tmp->suivant = NULL;

	return tmp;
}


void position_image_dans_option(Option option, int valeur) {
	option->position_image = valeur;	/* Image non sélectionnée */
	option->position_image_selection = valeur + 4;	/* Image sélectionnée */
}


void ajouter_option(Option* option, const char* titre) {
	Option tmp = alloue_option(titre);

	if (tmp != NULL) {
		tmp->suivant = *option;
		*option = tmp;
	}
}


void change_selection(Option option, const char* titre) {
	if (option == NULL) {
		printf("Pas d'options");
	} else {
		while (option != NULL) {
			if (strcmp(option->titre, titre) == 0) {
				option->selection = 1;	// Si l'option titre est sélectionnée, on change son champs à 1 (Apparaît rouge dans la fenêtre)
			} else {
				option->selection = 0;	// Si l'option titre n'est pas sélectionnée, on change son champs à 0 (Apparaît blanche dans la fenêtre)
			}
			option = option->suivant;
		}
	}
}


void free_options(Option option) {
	Option supp_elem;
	while (option != NULL) {
		free(option->titre);
		supp_elem = option;
		option = option->suivant;
		free(supp_elem);
	}
}
