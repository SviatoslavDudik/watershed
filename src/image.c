#include "image.h"

/* lit le fichier nom_fichier et renvoie l'image lue */
myimage LireImage(char *nom_fichier) {
	uint32_t largeur, hauteur, err, i, j;
	myimage img;
	uint8_t *image;
	err = lodepng_decode32_file(&image, &largeur, &hauteur, nom_fichier);
	if (err) {
		fprintf(stderr, "Erreur lecture de l'image %s : %s\n", nom_fichier, lodepng_error_text(err));
		assert(0);
	}
	img.hauteur = hauteur;
	img.largeur = largeur;
	img.rouge = (uint8_t**) malloc(sizeof(uint8_t*)*hauteur);
	if (img.rouge == NULL) {
		fprintf(stderr, "Erreur d'allocation mémoire\n");
		assert(0);
	}
	for (i = 0; i<hauteur; i++) {
		img.rouge[i] = (uint8_t*) malloc(sizeof(uint8_t)*largeur);
		if (img.rouge[i] == NULL) {
			fprintf(stderr, "Erreur d'allocation mémoire\n");
			assert(0);
		}
		for (j = 0; j<largeur; j++) {
			/* (i*largeur+j) donne le numéro du pixel (i,j).  On multiplie par
			 * 4 pour avoir le canal rouge seulement */
			img.rouge[i][j] = image[4*(i*largeur+j)];
		}
	}
	free(image); /* On n'a plus besoin */
	return img;
}

/* écrit l'image img dans le fichier nom_fichier */
void EcrireImage(myimage img, char *nom_fichier) {
	uint32_t err, i, j;
	uint64_t tmp;
	uint8_t *image;
	image = (uint8_t*) malloc(sizeof(uint8_t)*4*img.largeur*img.hauteur);
	if (image == NULL) {
		fprintf(stderr, "Erreur d'allocation mémoire\n");
		assert(0);
	}
	for (i = 0; i<img.hauteur; i++) {
		for (j = 0; j<img.largeur; j++) {
			/*  le numéro de la case correspondant au pixel (i,j) */
			tmp = 4*(i*img.largeur + j);
			image[tmp] = img.rouge[i][j];	/* rouge */
			image[tmp+1] = img.rouge[i][j];	/* vert */
			image[tmp+2] = img.rouge[i][j];	/* bleu */
			image[tmp+3] = 255;				/* alpha */
		}
	}
	err = lodepng_encode32_file(nom_fichier, image, img.largeur, img.hauteur);
	if (err) {
		fprintf(stderr, "Erreur écriture de l'image dans %s : %s\n", nom_fichier, lodepng_error_text(err));
		assert(0);
	}
	free(image);
}

/* alloue l'image vide de taille largeur*hauteur */
myimage AllouerImage(uint32_t hauteur, uint32_t largeur) {
	uint32_t i;
	myimage img;
	img.hauteur = hauteur;
	img.largeur = largeur;
	img.rouge = (uint8_t**) malloc(sizeof(uint8_t*)*hauteur);
	if (img.rouge == NULL) {
		fprintf(stderr, "Erreur d'allocation mémoire\n");
		assert(0);
	}
	for (i = 0; i<hauteur; i++) {
		img.rouge[i] = (uint8_t*) malloc(sizeof(uint8_t)*largeur);
		if (img.rouge[i] == NULL) {
			fprintf(stderr, "Erreur d'allocation mémoire\n");
			assert(0);
		}
	}
	return img;
}

/* libère img de la mémoire */
void LibererImage(myimage img) {
	uint32_t i;
	for (i = 0; i<img.hauteur; i++)
		free(img.rouge[i]);
	free(img.rouge);
}

/* La fonction écrit l'image img dans le fichier nom_fichier avec des couleurs
 * différentes en gardant le niveau de rouge et en choisissant aléatoirement
 * les mêmes niveaux de vert et de bleu pour toutes les couleurs
 */
void EcrireImageCouleursAleatoires(myimage img, char *nom_fichier) {
	uint32_t err, i, j;
	uint64_t tmp;
	uint8_t g, b;
	uint8_t *image;
	image = (uint8_t*) malloc(sizeof(uint8_t)*4*img.largeur*img.hauteur);
	if (image == NULL) {
		fprintf(stderr, "Erreur d'allocation mémoire\n");
		assert(0);
	}
	srand(time(NULL));
	g = rand() % 256;
	b = rand() % 256;
	for (i = 0; i<img.hauteur; i++) {
		for (j = 0; j<img.largeur; j++) {
			/*  le numéro de la case correspondant au pixel (i,j) */
			tmp = 4*(i*img.largeur + j);
			image[tmp] = img.rouge[i][j];	/* rouge */
			image[tmp+1] = g;				/* vert */
			image[tmp+2] = b;				/* bleu */
			image[tmp+3] = 255;				/* alpha */
		}
	}
	err = lodepng_encode32_file(nom_fichier, image, img.largeur, img.hauteur);
	if (err) {
		fprintf(stderr, "Erreur écriture de l'image dans %s : %s\n", nom_fichier, lodepng_error_text(err));
		assert(0);
	}
	free(image);
}

/* La fonction écrit l'image img dans le nom_fichier en ajoutant le contour.
 * Le paramètre contour est une image de même taille que img dont le champ
 * rouge contient pour un pixel donné :
 * 0 si ce n'est pas un contour
 * une valeur non nulle si c'est un contour
 * Le contour sera mis en rouge dans l'image finale
 */
void EcrireImageContour(myimage img, myimage contour, char *nom_fichier) {
	uint32_t err, i, j;
	uint64_t tmp;
	uint8_t *image;
	if (contour.hauteur != img.hauteur || contour.largeur != img.largeur) {
		fprintf(stderr, "Le contour doit être de la même taille que l'image\n");
		assert(0);
	}
	image = (uint8_t*) malloc(sizeof(uint8_t)*4*img.largeur*img.hauteur);
	if (image == NULL) {
		fprintf(stderr, "Erreur d'allocation mémoire\n");
		assert(0);
	}
	for (i = 0; i<img.hauteur; i++) {
		for (j = 0; j<img.largeur; j++) {
			/*  le numéro de la case correspondant au pixel (i,j) */
			tmp = 4*(i*img.largeur + j);
			if (contour.rouge[i][j] == 0) {
				/* pas contour */
				image[tmp] = img.rouge[i][j];	/* rouge */
				image[tmp+1] = img.rouge[i][j];	/* vert */
				image[tmp+2] = img.rouge[i][j];	/* bleu */
			}
			else {
				/* contour */
				image[tmp] = 255;				/* rouge */
				image[tmp+1] = 0;				/* vert */
				image[tmp+2] = 0;				/* bleu */
			}
			image[tmp+3] = 255;					/* alpha */
		}
	}
	err = lodepng_encode32_file(nom_fichier, image, img.largeur, img.hauteur);
	if (err) {
		fprintf(stderr, "Erreur écriture de l'image dans %s : %s\n", nom_fichier, lodepng_error_text(err));
		assert(0);
	}
	free(image);
}
