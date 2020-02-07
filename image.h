#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "lodepng.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	uint32_t largeur;
	uint32_t hauteur;
	uint8_t **rouge;
} myimage;

myimage LireImage(char *nom_fichier);
void EcrireImage(myimage img, char *nom_fichier);
myimage AllouerImage(uint32_t hauteur, uint32_t largeur);
void LibererImage(myimage img);

#endif
