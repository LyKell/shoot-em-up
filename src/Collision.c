/**
 * \file Collision.c
 * \brief Module tous ce qui concerne les collisions
 * \author BERGERON Youssef SAVANE Kevin
 * \date 11 Janvier 2020
 *
 * Module gérant les collisions entre vaisseau et les collisions missiles/vaisseau.
 *
 */
#include <MLV/MLV_all.h>
#include <math.h>

#include "../include/Collision.h"
#include "../include/Missile.h"


/*
Fonction renvoyant le maximum entre a et b
*/
int max(int a, int b) {
	return a < b ? b : a;
}


/*
Fonction renvoyant le minimum entre a et b
*/
int min(int a, int b) {
	return a < b ? a : b;
}


/*
Fonction traitant de l'intersection de deux rectangles
*/
int inter(int x1, int y1,  
				 int x2, int y2, 
				  int x3, int y3,  
				   int x4, int y4,
					int* xhg, int* yhg,
					 int* xbd, int* ybd) {

	/* Haut gauche */
	int x5 = max(x1, x3); 
	int y5 = max(y1, y3); 
	
	/* Bas droite*/
	int x6 = min(x2, x4); 
	int y6 = min(y2, y4); 

	/* pas d'intersection */
	if (x5 > x6 || y5 > y6)  { 
		return 0; 
	} 

	/* Haut gauche de l'intersection */
	*xhg = x5; 
	*yhg = y5; 

	/* Bas droite de l'intersection */
	*xbd = x6; 
	*ybd = y6; 

	return 1;
}


/*
Fonction qui analyse la collision entre une liste de missile , et un vaisseau selon un camp et la largeur et la hauteur du vaisseau
S'il s'agit de la collision avec notre vaisseau une vie sera perdu, sinon un ennemis en position pos_ennemis sera supprimer de la liste
*/ 
int collision_missile_vaisseau(Liste_missile* missiles, Liste_ennemi* ennemis, Vaisseau** vaisseau, int camp, int pos_ennemi, int largeur, int hauteur, Liste_explosion* liste_explosion) {
	Missile* tmp;
	int xhg, yhg, xbd, ybd;
	int pos_missile;
	int vie_perdu = 0;

	if (missiles -> taille != 0) {
		tmp = missiles -> tete;
		pos_missile = 1;
		while (tmp != NULL) {
			if (inter(tmp -> x, tmp -> y, tmp -> x + TAILLE_MISSILE / 2, tmp -> y + TAILLE_MISSILE / 2,
						(*vaisseau) -> x, (*vaisseau) -> y, (*vaisseau) -> x + largeur, (*vaisseau) -> y + hauteur,
						 &xhg, &yhg, &xbd, &ybd)) {
				if (camp == 0) { /* Cas où notre vaisseau est touché */
					vie_perdu += 1;
					tmp = supprime_missile(missiles, tmp, pos_missile);
				} else { /* Cas ou un autre vaisseau est touché */
					(*vaisseau) -> vie -= 1;
					tmp = supprime_missile(missiles, tmp, pos_missile);
					if ((*vaisseau) -> vie == 0) { /* La vie doit être à 0 pour disparaitre */ 
						*vaisseau = supprime_ennemi(ennemis, *vaisseau, pos_ennemi, liste_explosion);
						return 1;
					}
					return 0;
				}
			} else{
				tmp = tmp -> suivant;
				pos_missile += 1;
			}
		}
	}
	return vie_perdu;
}


/*
Fonction qui analyse la collision entre deux vaisseaux selon un camp et la largeur et la hauteur des deux vaisseaux impliqués
S'il s'agit de la collision avec notre vaisseau une vie sera perdu et un choc élastique sera crée, sinon un ennemis en position 
pos_ennemis sera supprimer de la liste
*/ 
int collision_vaisseau_vaisseau(Liste_ennemi* ennemis, Vaisseau** vaisseau1, Vaisseau** vaisseau2, double* ax, double* ay, int camp, int pos_ennemi, int pos_ennemi2,
									int largeur1, int hauteur1, int largeur2, int hauteur2, Liste_explosion* liste_explosion) {
	int xhg, yhg, xbd, ybd;
	double angle;
	if (inter((*vaisseau1) -> x, (*vaisseau1) -> y, (*vaisseau1) -> x + largeur1, (*vaisseau1) -> y + hauteur1,
						(*vaisseau2) -> x, (*vaisseau2) -> y, (*vaisseau2) -> x + largeur1, (*vaisseau2) -> y + hauteur2,
						 &xhg, &yhg, &xbd, &ybd)) {

		if (camp == 0) { /* Collision de notre vaisseau */
			/* Choc Elastique */
			angle = angle_tir((*vaisseau1) -> x + largeur1 / 2 , (*vaisseau1) -> y + hauteur1 / 2, (*vaisseau2) -> x + largeur2 / 2, (*vaisseau2) -> y  + hauteur2 / 2);
			*ax += cos(angle) * ((*vaisseau1) -> vitesse + (*vaisseau2) -> vitesse + 2);
			*ay += sin(angle) * ((*vaisseau1) -> vitesse + (*vaisseau2) -> vitesse + 2);

			/* Disparition si vie à 0 */
			(*vaisseau1) -> vie -= 1;
			if ((*vaisseau1) -> vie == 0) {
				*vaisseau1 = supprime_ennemi(ennemis, *vaisseau1, pos_ennemi, liste_explosion);
				return 1;
			}
			return 0;
		}
		supprime_ennemi(ennemis, *vaisseau2, pos_ennemi2, liste_explosion);
		*vaisseau1 = supprime_ennemi(ennemis, *vaisseau1, pos_ennemi, liste_explosion);
		return 1;
	}
	return 0;
}


void gestion_collision(Allie* joueur, Liste_ennemi* liste_ennemi, int largeur, int hauteur, Liste_explosion* liste_explosion, const MLV_Sound* son) {
	Vaisseau *tmp, *tmp1;
	int pos_ennemi, pos_tmp1, touche;

	/* Collision des missiles ennemis avec notre vaisseau */
	joueur -> vaisseau -> vie -= collision_missile_vaisseau(&(liste_ennemi -> missiles), liste_ennemi, &(joueur -> vaisseau), 
									0, 0, LARGEUR_VAISSEAU, HAUTEUR_VAISSEAU, NULL);

	if (liste_ennemi -> taille != 0) {
		tmp =  liste_ennemi -> tete;
		pos_ennemi = 1;

		while (tmp != NULL) {
			touche = 0;

			/* Collision des missiles ennemis avec un ennemis */
			if (collision_missile_vaisseau(&(liste_ennemi -> missiles), liste_ennemi, &tmp, 1, pos_ennemi, largeur, hauteur, liste_explosion) != 1) { 

				/* Collision des missiles alliés avec un ennemis */
				if (collision_missile_vaisseau(&(joueur -> missiles), liste_ennemi, &tmp, 1, pos_ennemi, largeur, hauteur, liste_explosion) != 1) {

					/* Collision entre notre vaisseau et un vaisseau ennemi */
					if (collision_vaisseau_vaisseau(liste_ennemi,  &tmp, &(joueur -> vaisseau), &(joueur -> ax), &(joueur -> ay),
							0, pos_ennemi, 0, largeur, hauteur, LARGEUR_VAISSEAU, HAUTEUR_VAISSEAU, liste_explosion) == 0) {
						pos_tmp1 = pos_ennemi + 1;
						tmp1 = tmp -> suivant;

						while (tmp1 != NULL) {
							/* Collision entre deux vaisseaux ennemis */
							if (collision_vaisseau_vaisseau(liste_ennemi, &tmp, &tmp1, NULL, NULL, 1, pos_ennemi, pos_tmp1,
								largeur, hauteur, largeur, hauteur, liste_explosion) == 1) {
								joueur -> score += 2;
								touche = 1;
								joue_son(son);
								break;
							}		
							tmp1 = tmp1 -> suivant;
							pos_tmp1 += 1;
						}
						if (touche != 1) {
							tmp = tmp -> suivant;
							pos_ennemi += 1;
						}
					} else {
						joueur -> vaisseau -> vie -= 1;
						joueur -> score += 1;
						joue_son(son);
					}
				} else {
					joueur -> score += 1;
					joue_son(son);
				}
			} else {
				joueur -> score += 1;
				joue_son(son);
			}
		}
	}
}
