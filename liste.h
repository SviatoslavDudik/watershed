#ifndef __LISTE_H__
#define __LISTE_H__

#include <stdint.h>
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

liste *new_liste();
void liste_add_tete(liste *l, uint32_t i, uint32_t j);
maillon *liste_rem_tete(liste *l);
void liste_free(liste *l);

#endif
