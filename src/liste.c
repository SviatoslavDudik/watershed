#include "liste.h"

/* crée une nouvelle liste chaînée */
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

/* crée un nouveau maillon contenant i et j comme données */
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

/* ajoute un maillon avec les données i,j à la tête de la liste l */
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

/* La fonction supprime la tête de la liste l et renvoie le
 * maillon supprimé. Le maillon renvoyé doit être libérer avec la
 * fonction free */
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

/* renvoie vrai si liste l est vide, faux sinon */
_Bool liste_est_vide(liste *l) {
	return (l->taille == 0);
}

/* libère la liste l de la mémoire */
void liste_free(liste *l) {
	while (!liste_est_vide(l))
		free(liste_rem_tete(l));
	free(l);
}

