/**
 * \file Sound.c
 * \brief Module qui gère le son du jeu
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module s'occupant d'initialiser les sons et musiques du jeu
 *
 */

#include "../include/Sound.h"
#include "../include/Ressource.h"

#include <MLV/MLV_all.h>
#include <string.h>


MLV_Music* background_music() {
	MLV_Music* music;
	char chemin_fichier_musique[8192];
	strcpy(chemin_fichier_musique, CHEMIN);
	strcat(chemin_fichier_musique, "bgm/Bad Apple!!.ogg");
	music = MLV_load_music(chemin_fichier_musique);
	if (music == NULL) {
		printf("Impossible de charger le fichier %s.\n", chemin_fichier_musique);
		exit(EXIT_FAILURE);
	}
	return music;
}


void joue_musique(const MLV_Music* music) {
	MLV_play_music(music, 1.0, -1);
}


MLV_Sound* charge_son() {
	MLV_Sound* son;
	char chemin_fichier_son[8192];
	strcpy(chemin_fichier_son, CHEMIN);
	strcat(chemin_fichier_son, "bgm/pldead00.wav");
	son = MLV_load_sound(chemin_fichier_son);
	if (son == NULL) {
		printf("Impossible de charger le fichier %s.\n", chemin_fichier_son);
		exit(EXIT_FAILURE);
	}
	return son;
}


void joue_son(const MLV_Sound* son) {
	MLV_play_sound(son, 0.5);
}
