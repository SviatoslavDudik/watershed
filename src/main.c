#include "image.h"
#include "watershed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *nom_resultat(char *nom);
char *nom_contour(char *nom);

int main(int argc, char **argv) {
	myimage img, grad, marqueurs;
	char *nom;
	if (argc < 3) {
		fprintf(stderr, "Usage : %s <image> <image_marqueurs>\n", argv[0]);
		exit(1);
	}
	img = LireImage(argv[1]);
	grad = CalculerGradient(img, 1);
	marqueurs = LireImage(argv[2]);

	CalculerLPE(grad, marqueurs);

	nom = nom_resultat(argv[1]);
	EcrireImage(marqueurs, nom);
	LibererImage(grad);
	free(nom);

	grad = CalculerGradient(marqueurs, 1);
	LibererImage(marqueurs);

	nom = nom_contour(argv[1]);
	EcrireImageContour(img, grad, nom);
	LibererImage(img);
	LibererImage(grad);
	free(nom);
	return 0;
}

char *nom_resultat(char *nom) {
	uint8_t n;
	char *res;
	char *pos;
	n = strlen(nom);
	res = (char*) malloc((n+5)*sizeof(char));
	pos = strrchr(nom, '.');
	res[0] = '\0';
	if (pos != NULL) {
		strncat(res, nom, pos-nom);
		strcat(res, "_res");
		strcat(res, pos);
	}
	else {
		strcpy(res, nom);
		strcat(res, "_res");
	}
	return res;
}

char *nom_contour(char *nom) {
	uint8_t n;
	char *res;
	char *pos;
	n = strlen(nom);
	res = (char*) malloc((n+9)*sizeof(char));
	pos = strrchr(nom, '.');
	res[0] = '\0';
	if (pos != NULL) {
		strncat(res, nom, pos-nom);
		strcat(res, "_contour");
		strcat(res, pos);
	}
	else {
		strcpy(res, nom);
		strcat(res, "_contour");
	}
	return res;
}
