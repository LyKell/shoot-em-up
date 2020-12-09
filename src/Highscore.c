/**
 * \file Highscore.c
 * \brief Module qui gère les meilleurs scores
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module s'occupant d'insérer un meilleur score dans un fichier Highscore .
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Highscore.h"
#include "../include/Ressource.h"


int nouveau_score(FILE* fichier, const char* nom_joueur, int score) {
	fprintf(fichier, "%s %d\n", nom_joueur, score);
	return 1;
}


void gestion_highscore(const char* nom_joueur, int score) {
	Score meilleur_score[10];
	int i = 0, j, nouveau = 0;
	FILE* fichier;
	char chemin_fichier[8192];
	strcpy(chemin_fichier, CHEMIN);
	strcat(chemin_fichier, "Highscore.txt");

	fichier = fopen(chemin_fichier, "r");
	if (fichier == NULL) {
		fprintf(stderr, "Pas de fichier Highscore\n");
		return;
	}

	while (fscanf(fichier, "%s ", meilleur_score[i].name) != EOF) {
		fscanf(fichier, "%d\n", &(meilleur_score[i].score));
		i += 1;
	}

	fclose(fichier);
	fichier = fopen(chemin_fichier, "w");

	if (i == 0) {	/* No score saved in the file */
		nouveau_score(fichier, nom_joueur, score);
		fclose(fichier);
		return;
	}

	if (i != 10) {
		j = 0;
		while (j < i) {	/* j < number of score */
			if (score > meilleur_score[j].score) {
				fprintf(fichier, "%s %d\n", meilleur_score[j].name, meilleur_score[j].score);
				j += 1;
			} else {
				nouveau = nouveau_score(fichier, nom_joueur, score);
				while (j < i) {
					fprintf(fichier, "%s %d\n", meilleur_score[j].name, meilleur_score[j].score);
					j += 1;
				}
			}
		}
		if (nouveau != 1) {
			nouveau_score(fichier, nom_joueur, score);
		}
	} else {
		if (score < meilleur_score[0].score) {
			fclose(fichier);
			return;
		}
		j = 1;
		while (j < i) {
			if (score > meilleur_score[j].score) {
				fprintf(fichier, "%s %d\n", meilleur_score[j].name, meilleur_score[j].score);
				j += 1;
			} else {
				nouveau = nouveau_score(fichier, nom_joueur, score);
				while (j < i) {
					fprintf(fichier, "%s %d\n", meilleur_score[j].name, meilleur_score[j].score);
					j += 1;
				}
			}
		}
		if (nouveau != 1) {
			nouveau_score(fichier, nom_joueur, score);
		}
	}
	fclose(fichier);
}

