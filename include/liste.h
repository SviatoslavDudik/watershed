#ifndef __LISTE_H__
#define __LISTE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct maillon_s {
	uint32_t i;
	uint32_t j;
	struct maillon_s *suivant;
} maillon;

typedef struct {
	maillon *tete;
	maillon *queue;
	uint64_t taille;
} liste;

/* crée une nouvelle liste chaînée */
liste *new_liste();

/* ajoute un maillon avec les données i,j à la tête de la liste l */
void liste_add_tete(liste *l, uint32_t i, uint32_t j);

/* La fonction supprime la tête de la liste l et renvoie le
 * maillon supprimé. Le maillon renvoyé doit être libérer avec la
 * fonction free */
maillon *liste_rem_tete(liste *l);

/* renvoie vrai si liste l est vide, faux sinon */
_Bool liste_est_vide(liste *l);

/* libère la liste l de la mémoire */
void liste_free(liste *l);

#endif
