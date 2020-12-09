/**
 * \file Graphique.c
 * \brief Module qui gère l'affichage graphique
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module s'occupant d'afficher les menus, la fenêtre du jeu, les éléments du jeu
 *
 */

#include "../include/Graphique.h"
#include "../include/Missile.h"
#include "../include/Vaisseau.h"
#include "../include/Ressource.h"

#include <assert.h>
#include <MLV/MLV_all.h>

static MLV_Image* tab_image[25];
static MLV_Image* explosion_sprites[8];



void init_tab_image(Option option) {
	char boss_index[2];
	int i;
	char chemin_image[8192];
	char chemin_image1[8192];

	for (i = 0; i < 25; i++) {
		tab_image[i] = NULL;
	}
	
	strcpy(chemin_image, CHEMIN);
	tab_image[0] = MLV_load_image(strcat(chemin_image, "sprites/character/player/idle/player_idle_1.png"));
	strcpy(chemin_image, CHEMIN);
	tab_image[1] = MLV_load_image(strcat(chemin_image,"sprites/character/enemies/enemy_idle_1.png"));
	strcpy(chemin_image, CHEMIN);
	tab_image[2] = MLV_load_image(strcat(chemin_image,"sprites/projectiles/player_projectile.png"));
	strcpy(chemin_image, CHEMIN);
	tab_image[3] = MLV_load_image(strcat(chemin_image,"sprites/projectiles/enemy_projectile.png"));
	strcpy(chemin_image, CHEMIN);
	tab_image[4] = MLV_load_image(strcat(chemin_image,"sprites/projectiles/tracking_projectile.png"));
	strcpy(chemin_image, CHEMIN);
	tab_image[5] = MLV_load_image(strcat(chemin_image,"sprites/background/background2.png"));
	strcpy(chemin_image, CHEMIN);
	tab_image[6] = MLV_load_image(strcat(chemin_image,"sprites/background/sidebar.jpg"));

	for (i = 0; i <= 6; i++) {
		if (tab_image[i] == NULL) {
			fprintf(stderr, "Ouverture d'image échouée.\n");
			exit(EXIT_FAILURE);
		}
	}

	MLV_resize_image(tab_image[0], LARGEUR_VAISSEAU, HAUTEUR_VAISSEAU);
	MLV_resize_image(tab_image[1], LARGEUR_VAISSEAU, HAUTEUR_VAISSEAU);
	MLV_resize_image(tab_image[2], TAILLE_MISSILE, TAILLE_MISSILE);
	MLV_resize_image(tab_image[3], TAILLE_MISSILE, TAILLE_MISSILE);
	MLV_resize_image(tab_image[4], TAILLE_MISSILE, TAILLE_MISSILE);
	MLV_resize_image(tab_image[5], LARGEUR, HAUTEUR);

	/* Sprites de boss */
	for (i = 1; i <= 8; i++) {
		sprintf(boss_index, "%d", i);
		strcpy(chemin_image, CHEMIN);
		strcat(chemin_image,"sprites/character/boss/boss_");
		strcat(chemin_image, boss_index);
		strcat(chemin_image, ".png");
		tab_image[6 + i] = MLV_load_image(chemin_image);
		if (tab_image[6 + i] == NULL) {
			fprintf(stderr, "L'image %s n'a pas pu être chargée.\n", chemin_image);
			exit(EXIT_FAILURE);
		}
		MLV_resize_image(tab_image[6 + i], LARGEUR_BOSS, HAUTEUR_BOSS);
	}

	/* Sprites de fond des menus */
	strcpy(chemin_image, CHEMIN);
	tab_image[15] = MLV_load_image(strcat(chemin_image,"sprites/menu/menu_2.jpg"));
	strcpy(chemin_image, CHEMIN);
	tab_image[16] = MLV_load_image(strcat(chemin_image,"sprites/menu/highscore_menu.jpg"));

	for (i = 15; i < 17; i++) {
		if (tab_image[i] == NULL) {
			fprintf(stderr, "Ouverture d'image échouée.\n");
			exit(EXIT_FAILURE);
		}
	}

	MLV_resize_image(tab_image[15], LARGEUR_FENETRE, HAUTEUR);
	MLV_resize_image(tab_image[16], LARGEUR_FENETRE, HAUTEUR);

	/* Sprites des boutons d'option */
	for (i = 1; i <= 4; i++) {
		strcpy(chemin_image, CHEMIN);
		strcat(chemin_image,"sprites/menu/");
		strcat(chemin_image, option->titre);

		strcpy(chemin_image1, chemin_image);
		strcat(chemin_image1, "_selected.png");

		strcat(chemin_image, ".png");

		tab_image[16 + i] = MLV_load_image(chemin_image);	// Sprites des options non sélectionnées
		tab_image[20 + i] = MLV_load_image(chemin_image1);	// Sprites des options sélectionnées

		if (tab_image[16 + i] == NULL) {
			fprintf(stderr, "L'image %s n'a pas pu être chargée.\n", chemin_image);
			exit(EXIT_FAILURE);
		}
		if (tab_image[20 + i] == NULL) {
			fprintf(stderr, "L'image %s n'a pas pu être chargée.\n", chemin_image1);
			exit(EXIT_FAILURE);
		}

		position_image_dans_option(option, 16 + i);	// On donne à option la position des images dans le tableau pour pouvoir les afficher plus facilement plus tard
		option = option->suivant;
	}
}


void free_tab_image() {
	int i;
	for (i = 0; i < 25; i ++) {
		MLV_free_image(tab_image[i]);
	}
}


void init_tab_explosion() {
	MLV_Image *image_explosion;
	int i, j, ligne = 0;
	int hauteur = 40, largeur = 40;
	char chemin_image[8192];
	strcpy(chemin_image, CHEMIN);
	strcat(chemin_image, "sprites/character/death/death.png");

	for (i = 0; i < 8; i++) {
		explosion_sprites[i] = NULL;
	}

	image_explosion = MLV_load_image(chemin_image);
	if (image_explosion == NULL) {
		fprintf(stderr, "L'image des explosions n'a pas pu être chargée.\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0, j = 0; i < 8; i++, j++) {
		explosion_sprites[i] = MLV_copy_partial_image(image_explosion, j*largeur, ligne*hauteur, largeur, hauteur);

		if (i == 3) {
			j = -1;
			ligne = 1;
		}
	}
	MLV_free_image(image_explosion);
}


void free_tab_explosion() {
	int i;

	for (i = 0; i < 8; i++) {
		MLV_free_image(explosion_sprites[i]);
	}
}


void cree_fenetre() {
	MLV_create_window("Shoot’em up", "Shoot’em up", 
						LARGEUR_FENETRE, HAUTEUR);
}


/*
Fonction qui dessine les points de vie sur le coté de l'écran
*/
void dessine_hp(int hp, float longueur_barre_de_hp, int hp_vaisseau, int pos_x, int pos_y, int hauteur_barre_de_hp) {
	float hp_actuel = longueur_barre_de_hp - (hp_vaisseau - hp) * (longueur_barre_de_hp / hp_vaisseau);
	MLV_draw_filled_rectangle(pos_x, pos_y, hp_actuel, hauteur_barre_de_hp, MLV_COLOR_GREEN);
	MLV_draw_rectangle(pos_x, pos_y, longueur_barre_de_hp, hauteur_barre_de_hp, MLV_COLOR_WHITE);
}


/*
Fonction qui dessine un vaisseau dans la fenetre de jeu
*/
void dessine_vaisseau(const Vaisseau* vaisseau, int camp) {
	if (camp == 0) {
		MLV_draw_image(tab_image[0], vaisseau->x, vaisseau->y);
	} else {
		MLV_draw_image(tab_image[1], vaisseau->x, vaisseau->y);
	}
}


/*
Fonction qui dessine un missile dans la fenetre de jeu
*/ 
void dessine_missile(const Liste_missile* missiles, int camp) {
	Missile* tmp;

	if (missiles -> taille != 0) {
		tmp = missiles -> tete;
		while (tmp != NULL) {
			if (camp == 0) {
				MLV_draw_image(tab_image[2], tmp->x, tmp->y);

			} else if (camp == 1 && tmp->pattern_tir != 3) {
				MLV_draw_image(tab_image[3], tmp->x, tmp->y);

			} else if (camp == 1 && tmp->pattern_tir == 3) {
				MLV_draw_image(tab_image[4], tmp->x, tmp->y);
			}
			tmp = tmp -> suivant;
		}
	}
}


/*
Fonction qui dessine un ennemi dans la fenetre de jeu
*/ 
void dessine_ennemi(const Liste_ennemi* liste_ennemi) {
	Vaisseau* tmp;
	if (liste_ennemi -> taille != 0) {
		tmp = liste_ennemi -> tete;
		while (tmp != NULL) {
			dessine_vaisseau(tmp, 1);
			tmp = tmp -> suivant;
		}
	}
}


/*
Fonction qui dessine un boss dans la fenetre de jeu
*/ 
void dessine_boss(const Liste_ennemi* boss, int* nb_alea, int hp_vaisseau) {
	Vaisseau* tmp;

	if (boss -> taille != 0) {
		tmp = boss -> tete;
		MLV_draw_image(tab_image[*nb_alea + 6], tmp->x, tmp->y);

		dessine_hp(tmp->vie, MLV_get_image_width(tab_image[*nb_alea + 6]), hp_vaisseau, tmp->x, tmp->y + MLV_get_image_height(tab_image[*nb_alea + 6]), 5);

	} else {
		*nb_alea = rand() % (8) + 1;	// We want to have a different boss each time it appears
	}
}


/*
Fonction qui dessine les explosions des ennemis
 */
void dessine_explosion(const Liste_explosion* liste_explosion) {
	Explosion* tmp;

	if (liste_explosion->taille != 0) {
		tmp = liste_explosion->tete;
		while (tmp != NULL) {
			MLV_draw_image(explosion_sprites[tmp->frame_actuelle], tmp->x - 5, tmp->y - 5);
			tmp = tmp->suivant;
		}
	}
}


/*
Fonction qui donne une impression de défilement de l'écran
*/
void defilement_background(int* y) {
	if ((*y) >= HAUTEUR) {
		(*y) = 0;
	} else {
		(*y)++;
	}
	MLV_draw_image(tab_image[6], LARGEUR, 0);
	MLV_draw_image(tab_image[5], 0, *y);
	MLV_draw_image(tab_image[5], 0, *y - HAUTEUR);
}


/*
Fonction qui dessine un entier (ici score ou temps) sur le coté de l'écran
*/
void dessine_int(char* chaine_a_afficher, int valeur, int pos_x, MLV_Color couleur) {
	char str[10], string[20];
	strcpy(string, chaine_a_afficher);
	sprintf(str, "%d", valeur);
	strcat(string, str);

	MLV_draw_adapted_text_box(pos_x, 10, string, 9, MLV_rgba(255,0,0,0), couleur, MLV_rgba(255,0,0,0), MLV_TEXT_LEFT);
}


void dessine_fenetre(const Allie* joueur, const Liste_ennemi* liste_ennemi, const Liste_ennemi* boss, const Liste_explosion* liste_explosion, int* y, int* nb_alea, int hp_vaisseau, int temps_ecoule) {
	MLV_draw_filled_rectangle(0, 0, LARGEUR_FENETRE, HAUTEUR, MLV_COLOR_BLACK);
	defilement_background(y);
	dessine_vaisseau(joueur -> vaisseau, 0);
	dessine_missile(&(joueur -> missiles), 0);
	dessine_ennemi(liste_ennemi);
	dessine_boss(boss, nb_alea, hp_vaisseau);
	dessine_missile(&(liste_ennemi -> missiles), 1);
	dessine_missile(&(boss -> missiles), 1);
	dessine_explosion(liste_explosion);
	dessine_hp(joueur -> vaisseau -> vie, LARGEUR_FENETRE - LARGEUR - 40, HP, LARGEUR + 20, 80, 30);
	dessine_int("Score : ", joueur->score, LARGEUR + 10, MLV_COLOR_WHITE);
	dessine_int("Temps : ", temps_ecoule, LARGEUR_FENETRE - 107, MLV_COLOR_RED);
	MLV_actualise_window();
}


void dessine_menu(Option option, int valeur) {
	assert(valeur >= 0);
	assert(valeur <= 1);
	MLV_draw_filled_rectangle(0, 0, LARGEUR_FENETRE, HAUTEUR, MLV_COLOR_BLACK);
	if (valeur == MAIN_MENU) {
		MLV_draw_image(tab_image[15], 0, 0);
	} else {
		MLV_draw_image(tab_image[16], 0, 0);
	}

	if (valeur == HIGHSCORE_MENU) {	// On est dans le menu Highscore
		dessine_highscore_dans_menu();
	}

	dessine_options(option, valeur);

	MLV_actualise_window();
}


void recupere_taille_options(Option option) {
	while (option != NULL) {
		MLV_get_image_size(tab_image[option->position_image], &(option->width), &(option->height));
		option = option->suivant;
	}
}


void dessine_options(Option option, int valeur) {
	int i = 0;

	while (option != NULL) {		
		if (valeur == MAIN_MENU) {	// On est dans le menu principale
			if (strcmp(option->titre, "back") != 0) {	// Donc on n'affiche pas Back
				if (option->selection == 1) {
					MLV_draw_image(tab_image[option->position_image_selection], MENU_W_ORIG + i*40, MENU_H_ORIG + i*50);
				} else {
					MLV_draw_image(tab_image[option->position_image], MENU_W_ORIG + i*40, MENU_H_ORIG + i*50);			
				}
				i++;
			}
		} else if (valeur == HIGHSCORE_MENU) {	// On est dans le menu Highscore
			if (strcmp(option->titre, "back") == 0) {	// Donc on affiche Back et rien d'autre
				if (option->selection == 1) {
					MLV_draw_image(tab_image[option->position_image_selection], 40, 40);
				} else {
					MLV_draw_image(tab_image[option->position_image], 40, 40);
				}
			}
		}
		option = option->suivant;
	}
}


/*
Fonction qui affiche les meilleurs scores dans le menu
*/
void dessine_highscore_dans_menu() {
	char score[20];
	int i = 0;
	MLV_Font* font;
	FILE* fichier;
	char chemin_fichier[8192];
	
	strcpy(chemin_fichier, CHEMIN);
	strcat(chemin_fichier, "Highscore.txt");
	fichier = fopen(chemin_fichier, "r");
	
	strcpy(chemin_fichier, CHEMIN);
	strcat(chemin_fichier, "fonts/ChineseTakeaway.ttf");
	font = MLV_load_font(chemin_fichier, 40);

	if (fichier == NULL) {
		fprintf(stderr, "Pas de fichier Highscore\n");
		return;
	}
	if (font == NULL) {
		fprintf(stderr, "Pas de font disponible\n");
		return;
	}

	while (fgets(score, 20, fichier) != NULL) {
		MLV_draw_adapted_text_box_with_font(LARGEUR_HIGHSCORE + 30, 40*i, score, font, 9, MLV_rgba(255,0,0,0), MLV_COLOR_WHITE, MLV_rgba(255,0,0,0), MLV_TEXT_LEFT);
		i++;
	}

	fclose(fichier);
	MLV_free_font(font);
}


int survole_et_selectionne_option(Option option, int valeur) {
	int x, y, i = 0;
	Option tmp = option;

	MLV_get_mouse_position(&x, &y);

	while (option != NULL) {
		if (valeur == MAIN_MENU) {	// On est dans le menu principal
			// Vérifie si la souris est sur une option
			if (MENU_W_ORIG + i*40 < x && x < MENU_W_ORIG + i*40 + option->width && MENU_H_ORIG + i*50 < y && y < MENU_H_ORIG + i*50 + option->height && strcmp(option->titre, "back") != 0) {
				return survole_option(tmp, option);

			} else {
				change_selection(tmp, "");	// Change toutes les options à non sélectionnée
			}
			i++;
		} else if (valeur == HIGHSCORE_MENU) {	// On est dans le menu Highscore, donc on a que Back
			// Vérifie si la souris est sur une option
			if (40 < x && x < 40 + option->width && 40 < y && y < 40 + option->height && strcmp(option->titre, "back") == 0) {
				return survole_option(tmp, option);

			} else {
				change_selection(tmp, "");	// Change toutes les options à non sélectionnée
			}
		}
		option = option->suivant;
	}
	return -1;
}


int survole_option(Option tmp, const Option option) {
	change_selection(tmp, option->titre);	// Change l'état de l'option a Sélectionnée
	if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
		return selectionne_option(option->titre);				
	}
	return -1;
}


int selectionne_option(char* titre) {
	if (strcmp(titre, "start") == 0) {
		return 1;
	} else if (strcmp(titre, "highscore") == 0) {
		return 2;
	} else if (strcmp(titre, "quit") == 0) {
		return 0;
	} else if (strcmp(titre, "back") == 0) {
		return 3;
	}
	return -1;
}


void sauvegarde_nom_joueur_pour_highscore(char** nom_joueur) {
	MLV_wait_input_box(
		LARGEUR + 10, HAUTEUR / 2,
		LARGEUR_FENETRE - LARGEUR - 20, 30,
		MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_DIM_GRAY,
		"Votre nom : ",
		nom_joueur
	);
	(*nom_joueur)[3] = '\0';

	MLV_actualise_window();
}

