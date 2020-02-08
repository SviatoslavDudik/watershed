#include "liste.h"

liste *new_liste() {
	liste *l;
	l = (liste*) malloc(sizeof(liste));
	if (l == NULL) {
		fprintf(stderr,"Erreur d'allocation mémoire\n");
		assert(0);
	}
	l->tete = NULL;
	l->queue = NULL;
	l->taille = 0;
	return l;
}

maillon *new_maillon(uint32_t i, uint32_t j) {
	maillon *m;
	m = (maillon*) malloc(sizeof(maillon));
	if (m == NULL) {
		assert(0);
	}
	m->i = i;
	m->j = j;
	m->suivant = NULL;
	return m;
}

void liste_add_tete(liste *l, uint32_t i, uint32_t j) {
	maillon *m;
	m = new_maillon(i, j);
	m->suivant = l->tete;
	l->tete = m;
	if (liste_est_vide(l)) {
		l->queue = m;
	}
	l->taille += 1;
}

maillon *liste_rem_tete(liste *l) {
	maillon *p;
	if (liste_est_vide(l)) {
		assert(0);
	}
	p = l->tete;
	l->tete = p->suivant;
	if (l->taille == 1) {
		l->queue = NULL;
	}
	l->taille -= 1;
	return p;
}

_Bool liste_est_vide(liste *l) {
	return (l->taille == 0);
}

void liste_free(liste *l) {
	while (!liste_est_vide(l))
		free(liste_rem_tete(l));
	free(l);
}

