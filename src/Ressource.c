/**
 * \file Ressource.c
 * \brief Module qui s'occupe du dossier contenant les images, sons, etc
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Testera l'existence du dossier indiqué.
 *
 */

#include "../include/Ressource.h"

#include <stddef.h>
#include <dirent.h>

int test_repertoire(){
	if (opendir(CHEMIN) == NULL)
		return 0;
	return 1;
}
