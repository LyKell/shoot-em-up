/**
 * \file Evenement.c
 * \brief Module gérant les interractions joueur/clavier
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module contenant une fonction de gestion des touches selon leurs états.
 *
 */

#include "../include/Evenement.h"


void gestion_touche(int touche[], MLV_Keyboard_button keysym, MLV_Button_state state) {
	switch (keysym) {
		case MLV_KEYBOARD_z:
			if (state == MLV_PRESSED) {
				touche[UP] = 1;
			} else {
				touche[UP] = 0;
			}
			break;

		case MLV_KEYBOARD_q:
			if (state == MLV_PRESSED) {
				touche[LEFT] = 1;
			} else {
				touche[LEFT] = 0;
			}
			break;

		case MLV_KEYBOARD_s:
			if (state == MLV_PRESSED) {
				touche[DOWN] = 1;
			} else {
				touche[DOWN] = 0;
			}
			break;

		case MLV_KEYBOARD_d:
			if (state == MLV_PRESSED) {
				touche[RIGHT] = 1;
			} else {
				touche[RIGHT] = 0;
			}
			break;

		case MLV_KEYBOARD_SPACE:
			if (state == MLV_PRESSED) {
				touche[SPACE] = 1;
			} else {
				touche[SPACE] = 0;
			}
			break;

		case MLV_KEYBOARD_e:
			if (state == MLV_PRESSED) {
				touche[E] = 1;
			} else {
				touche[E] = 0;
			}
			break;

		case MLV_KEYBOARD_a:
			if (state == MLV_PRESSED) {
				touche[A] = 1;
			} else {
				touche[A] = 0;
			}
			break;	

		default:
			break;
	}
}


void remise_zero_touche(int touche[]) {
	int i;
	for (i = 0; i < A + 1; i++) {
		touche[i] = 0;
	}
}
