/**
 * \file Main.c
 * \brief Jeu Shoot'em up
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Jeu Shoot'em up.
 *
 */
 
#include <stdio.h>
#include <time.h>

#include <MLV/MLV_all.h>

#include "../include/Graphique.h"
#include "../include/Vaisseau.h"
#include "../include/Missile.h"
#include "../include/Ennemi.h"
#include "../include/Allié.h"
#include "../include/Evenement.h"
#include "../include/Collision.h"
#include "../include/Menu.h"
#include "../include/Highscore.h"
#include "../include/Sound.h"
#include "../include/Explosion.h"
#include "../include/Ressource.h"

#define POSIX_C_SOURCE 199389L
#define BILLION 1000000000L

int main(int argc, char **argv) {
	/* Variables declarations and initialisations */
	struct timespec new, last, debut;
	MLV_Keyboard_button keysym = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	MLV_Event event;
	MLV_Music* musique = NULL;
	MLV_Sound* son = NULL;
	int touche[A + 1] = {0, 0, 0, 0, 0, 0, 0};

	Option option = NULL;
	char* list_options[] = {"start", "highscore", "quit", "back"};
	char* nom_joueur;
	int i, choice = -1;
	int y = 0;
	int nb_alea = 1;

	int quit;
	int nb_ennemi = 0;
	int point_perdu;
	double accum = 0;
	int temps_ecoule = 0;
	
	Allie joueur;
	Liste_ennemi ennemis;
	Liste_ennemi boss;
	Liste_explosion explosion;


	/* Partie principale */
	cree_fenetre();

	/* Gestion de l'infrastructure sonore */
	if (MLV_init_audio()) {
		fprintf(stderr, "L'infrastructure audio n'a pas pu être initialisée correctement.\n");
		return 2;
	}
	
	if (test_repertoire() == 0){
		fprintf(stderr, "Le répertoire des ressources est mal renseigné.\n");
		return 2;
	}

	/* Ajout des options dans une structure pour les manipuler plus facilement */
	for (i = 3; i >= 0; i--) {
		ajouter_option(&option, list_options[i]);
	}

	init_tab_image(option);
	init_tab_explosion();

	recupere_taille_options(option);

	while (choice != 0) {
		choice = -1;
		quit = 0;
		nb_ennemi = 0;

		do {
			/* Selection de l'option que l'on veut choisir */
			choice = survole_et_selectionne_option(option, MAIN_MENU);
			dessine_menu(option, MAIN_MENU);

			if (choice == 2) {	// Highscore
				while (choice != 3) {
					choice = survole_et_selectionne_option(option, HIGHSCORE_MENU);
					dessine_menu(option, HIGHSCORE_MENU);
				}
			}

		} while (choice != 1 && choice != 0);	// Start


		if (choice == 1) {
			nom_joueur = NULL;
			if (init_allie(&joueur, HAUTEUR, LARGEUR) == 0) {
				return 1;
			}
			init_liste_ennemi(&ennemis);
			init_liste_ennemi(&boss);
			init_liste_explosion(&explosion);
			musique = background_music();
			son = charge_son();
			joue_musique(musique);
			clock_gettime(CLOCK_REALTIME, &debut);

			/* Boucle principale */
			while (!quit) {
				if (MLV_get_random_integer(0, 80) == 0) {
					if (nb_ennemi % BOSS != 1 && boss.tete == NULL) {
						nb_ennemi += 1;
						if (ajout_ennemi(&ennemis, 1, LARGEUR) == 0) {
							return 1;
						}
					} else {
						if (ennemis.tete == NULL && boss.tete == NULL) {
							nb_ennemi += 1;
							if (ajout_ennemi(&boss, (nb_ennemi / 20) + 2,  LARGEUR) == 0) {
								return 1;
							}
							boss.tete -> pattern_depl = MLV_get_random_integer(4, 7);
						}
					}
				}

				/* Récupération du temps en nanosecondes au début de la frame */
				clock_gettime(CLOCK_REALTIME, &last);
				
				temps_ecoule = (int) (last.tv_sec - debut.tv_sec) + ((last.tv_nsec - debut.tv_nsec) / BILLION);

				/* Affichage de la frame actuelle */
				/* CETTE FONCTION APPELLE UNE SEULE FOIS MLV_actualise_window */
				dessine_fenetre(&joueur, &ennemis, &boss, &explosion, &y, &nb_alea, (nb_ennemi / 20) + 2, temps_ecoule);


				/* On récupère ici au plus une touche du clavier à chaque frame */
				event = MLV_get_event(&keysym, NULL, NULL, NULL, NULL,
					NULL, NULL, NULL, &state);

				if (event != MLV_NONE) {
					gestion_touche(touche, keysym, state);
				}

				/* Gestion dese vent associé aux touches */
				action_touche(&joueur, touche, accum, HAUTEUR, LARGEUR);

				/* Déplacement des entités à l'écran */
				point_perdu = actualise_ennemi(&ennemis, joueur.vaisseau, accum, HAUTEUR, LARGEUR, 0, &explosion);
				if (actualise_ennemi(&boss, joueur.vaisseau, accum, HAUTEUR, LARGEUR, 1, &explosion) == -1 || point_perdu == -1)  {
					return 1;
				}
				joueur.vaisseau -> vie -= point_perdu;
				actualise_missile(&(joueur.missiles), HAUTEUR, LARGEUR, joueur.vaisseau -> x, joueur.vaisseau -> y);
				actualise_missile(&(ennemis.missiles), HAUTEUR, LARGEUR, joueur.vaisseau -> x, joueur.vaisseau -> y);
				actualise_missile(&(boss.missiles), HAUTEUR, LARGEUR, joueur.vaisseau -> x, joueur.vaisseau -> y);
				actualise_explosion(&explosion);

				/* Gestion des collisions */
				gestion_collision(&joueur, &ennemis, LARGEUR_VAISSEAU, HAUTEUR_VAISSEAU, &explosion, son);
				gestion_collision(&joueur, &boss, LARGEUR_BOSS, HAUTEUR_BOSS, &explosion, son);

				/* Récupération du temps en nanosecond à la fin de la frame */
				clock_gettime(CLOCK_REALTIME,&new);

				/* On calcule le temps écoulé pendant cette frame */
				accum = (new.tv_sec - last.tv_sec) + ((new.tv_nsec - last.tv_nsec) / BILLION);

				/* On force une attente si la frame était trop courte */
				if (accum < (1.0 / 48.0)) {
					MLV_wait_milliseconds((int)(((1.0 / 48.0) - accum) * 1000));
					accum = 1.0 / 48.0;
				}
				joueur.temps += accum;
				if (joueur.vaisseau -> vie <= 0) {
					quit = 1;
				}
			}
			dessine_fenetre(&joueur, &ennemis, &boss, &explosion, &y, &nb_alea, (nb_ennemi / 20) + 2, temps_ecoule);
			sauvegarde_nom_joueur_pour_highscore(&nom_joueur);
			gestion_highscore(nom_joueur, joueur.score);

			MLV_stop_music();
			MLV_stop_all_sounds();
			free_allie(&joueur);
			free_liste_ennemi(&ennemis, &explosion);
			free_liste_ennemi(&boss, &explosion);
			free_liste_explosion(&explosion);
			free(nom_joueur);
			remise_zero_touche(touche);
		}
	}

	MLV_free_music(musique);
	MLV_free_sound(son);
	MLV_free_audio();

	free_options(option);
	free_tab_image();
	free_tab_explosion();

	MLV_free_window();

	return 0;
}
