#ifndef __WATERSHED_H__
#define __WATERSHED_H__

#include "hashtable.h"
#include "image.h"
#include <stdint.h>

/* La fonction calcule le gradient de l'image img.
 * Si le rayon = 0 le gradient est toujours nul,
 * plus le rayon est grand plus le gradient sera flou.
 * Valeur de retour: l'image du gradient
 */
myimage CalculerGradient(myimage img, uint16_t rayon);

/* La fonction calcule la ligne de partage des eaux.
 * Le paramètre gradient doit être le gradient d'une image.
 * Le paramètre m est l'image des marqueurs.
 * La fonction stocke le résultat dans m
 */
void CalculerLPE(myimage gradient, myimage m);

#endif
