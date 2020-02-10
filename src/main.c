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

	/* on calcule les lignes de partage des eaux
	 * et elles seront dans marqueurs */
	CalculerLPE(grad, marqueurs);

	/* on sauvegarde le résultat */
	nom = nom_resultat(argv[1]);
	EcrireImage(marqueurs, nom);
	/* EcrireImageCouleursAleatoires(marqueurs, nom); */
	LibererImage(grad);
	free(nom);

	/* pour calculer le contour on calcule d'abord le gradient des lignes de
	 * partage des eaux */
	grad = CalculerGradient(marqueurs, 1);
	LibererImage(marqueurs);

	nom = nom_contour(argv[1]);
	/* on écrit l'image en la superposant avec le gradient calculé à parir des LPE */
	EcrireImageContour(img, grad, nom);
	LibererImage(img);
	LibererImage(grad);
	free(nom);
	return 0;
}

/* prend en paramètre le nom de l'image et renvoie le nom que le résultat doit
 * porter. Par exemple, si nom = "test.png", alors la fonction renverra "test_res.png */
char *nom_resultat(char *nom) {
	uint8_t n;
	char *res;
	char *pos;
	n = strlen(nom);
	res = (char*) malloc((n+5)*sizeof(char));
	pos = strrchr(nom, '.');
	res[0] = '\0';
	if (pos != NULL) {
		strncat(res, nom, pos-nom);	/* res = "test" */
		strcat(res, "_res");		/* res = "test_res" */
		strcat(res, pos);			/* res = "test_res.png" */
	}
	else {
		strcpy(res, nom);			/* res = "test" */
		strcat(res, "_res");		/* res = "test_res" */
	}
	return res;
}

/* prend en paramètre le nom de l'image et renvoie le nom que l'image avec le contour doit
 * porter. Par exemple, si nom = "test.png", alors la fonction renverra "test_contour.png */
char *nom_contour(char *nom) {
	uint8_t n;
	char *res;
	char *pos;
	n = strlen(nom);
	res = (char*) malloc((n+9)*sizeof(char));
	pos = strrchr(nom, '.');
	res[0] = '\0';
	if (pos != NULL) {
		strncat(res, nom, pos-nom);/* res = "test" */
		strcat(res, "_contour");   /* res = "test_contour" */
		strcat(res, pos);          /* res = "test_contour.png" */
	}
	else {
		strcpy(res, nom);          /* res = "test" */
		strcat(res, "_contour");   /* res = "test_contour" */
	}
	return res;
}
