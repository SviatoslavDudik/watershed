#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "lodepng.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct {
	uint32_t largeur;
	uint32_t hauteur;
	uint8_t **rouge;
} myimage;

/* lit le fichier nom_fichier et renvoie l'image lue */
myimage LireImage(char *nom_fichier);

/* écrit l'image img dans le fichier nom_fichier */
void EcrireImage(myimage img, char *nom_fichier);

/* alloue l'image vide de taille largeur*hauteur */
myimage AllouerImage(uint32_t hauteur, uint32_t largeur);

/* libère img de la mémoire */
void LibererImage(myimage img);

/* La fonction écrit l'image img dans le fichier nom_fichier avec des couleurs
 * différentes en gardant le niveau de rouge et en choisissant aléatoirement
 * les mêmes niveaux de vert et de bleu pour toutes les couleurs
 */
void EcrireImageCouleursAleatoires(myimage img, char *nom_fichier);

/* La fonction écrit l'image img dans le nom_fichier en ajoutant le contour.
 * Le paramètre contour est une image de même taille que img dont le champ
 * rouge contient pour un pixel donné :
 * 0 si ce n'est pas un contour
 * une valeur non nulle si c'est un contour
 * Le contour sera mis en rouge dans l'image finale
 */
void EcrireImageContour(myimage img, myimage contour, char *nom_fichier);

#endif
