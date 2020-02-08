#include "watershed.h"

uint8_t ValeurMax(myimage img, uint32_t i, uint32_t j, uint16_t rayon);
uint8_t ValeurMin(myimage img, uint32_t i, uint32_t j, uint16_t rayon);

myimage CalculerGradient(myimage img, uint16_t rayon) {
	uint32_t i, j;
	myimage res;
	/* création d'une image vide de même taille */
	res = AllouerImage(img.hauteur, img.largeur);
	for (i = 0; i<img.hauteur; i++)
		for (j = 0; j<img.largeur; j++)
			res.rouge[i][j] = ValeurMax(img, i, j, rayon) - ValeurMin(img, i, j, rayon);
	return res;
}

void CalculerLPE(myimage gradient, myimage m) {
	hashtable *h;
	maillon *pixel;
	uint32_t i, j, k, l;
	int16_t grad;
	if (m.largeur > gradient.largeur || m.hauteur > gradient.hauteur) {
		fprintf(stderr, "Les marqueurs ne peuvent pas excéder la taille de l'image\n");
		assert(0);
	}
	h = new_hash();
	for (i = 0; i<m.hauteur; i++) {
		for (j = 0; j<m.largeur; j++) {
			if (m.rouge[i][j] != 0)
				hash_add(h, i, j, gradient.rouge[i][j]);
		}
	}
	while ((grad=hash_first_not_empty(h)) >= 0) {
		pixel = hash_rem(h, grad);
		i = pixel->i;
		j = pixel->j;
		free(pixel);
		k = i>0 ? i-1 : i;
		while (k <= i+1 && k < m.hauteur) {
			l = j>0 ? j-1 : j;
			while (l <= j+1 && l < m.largeur) {
				if (m.rouge[k][l] == 0) {
					m.rouge[k][l] = m.rouge[i][j];
					hash_add(h, k, l, gradient.rouge[k][l]);
				}
				l++;
			}
			k++;
		}
	}
	hash_free(h);
}

uint8_t ValeurMax(myimage img, uint32_t i, uint32_t j, uint16_t rayon) {
	uint32_t k, l;
	uint8_t max;
	max = img.rouge[i][j];
	/* k prend pour valeur i-rayon sauf si cette valeur est négative. Dans ce
	 * cas on commence à 0 */
	k = i<=rayon ? 0 : i-rayon;
	while (k <= i+rayon && k < img.hauteur) {
		/* l = j-rayon si cette valeur est positive. Sinon l = 0 */
		l = j<=rayon ? 0 : j-rayon;
		while (l <= j+rayon && l < img.largeur) {
			if (max < img.rouge[k][l])
				max = img.rouge[k][l];
			l++;
		}
		k++;
	}
	return max;
}

uint8_t ValeurMin(myimage img, uint32_t i, uint32_t j, uint16_t rayon) {
	uint32_t k, l;
	uint8_t min;
	min = img.rouge[i][j];
	/* k prend pour valeur i-rayon sauf si cette valeur est négative. Dans ce
	 * cas on commence à 0 */
	k = i<=rayon ? 0 : i-rayon;
	while (k <= i+rayon && k < img.hauteur) {
		/* l = j-rayon si cette valeur est positive. Sinon l = 0 */
		l = j<=rayon ? 0 : j-rayon;
		while (l <= j+rayon && l < img.largeur) {
			if (min > img.rouge[k][l])
				min = img.rouge[k][l];
			l++;
		}
		k++;
	}
	return min;
}
