#include "watershed.h"

uint8_t ValeurMax(myimage img, uint32_t i, uint32_t j, uint16_t rayon);
uint8_t ValeurMin(myimage img, uint32_t i, uint32_t j, uint16_t rayon);

myimage CalculerGradient(myimage img, uint16_t rayon) {
	uint32_t i, j;
	myimage res;
	/* création d'une image vide de même taille */
	res = AllouerImage(img.hauteur, img.largeur);
	for (i = 0; i<img.largeur; i++)
		for (j = 0; j<img.hauteur; j++)
			res.rouge[i][j] = ValeurMax(img, i, j, rayon) - ValeurMin(img, i, j, rayon);
	return res;
}

uint8_t ValeurMax(myimage img, uint32_t i, uint32_t j, uint16_t rayon) {
	uint32_t k, l;
	uint8_t max;
	max = img.rouge[i][j];
	/* k prend pour valeur i-rayon sauf si cette valeur est négative. Dans ce
	 * cas on commence à 0 */
	k = i<=rayon ? 0 : i-rayon;
	while (k <= i+rayon && k < img.largeur) {
		/* l = j-rayon si cette valeur est positive. Sinon l = 0 */
		l = j<=rayon ? 0 : j-rayon;
		while (l <= j+rayon && l < img.hauteur) {
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
	while (k <= i+rayon && k < img.largeur) {
		/* l = j-rayon si cette valeur est positive. Sinon l = 0 */
		l = j<=rayon ? 0 : j-rayon;
		while (l <= j+rayon && l < img.hauteur) {
			if (min > img.rouge[k][l])
				min = img.rouge[k][l];
			l++;
		}
		k++;
	}
	return min;
}
