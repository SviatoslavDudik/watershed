#include "hashtable.h"

/* crée une nouvelle table de hachage */
hashtable *new_hash() {
	uint16_t i;
	hashtable *h;
	h = (hashtable*) malloc(sizeof(hashtable));
	if (h == NULL) {
		fprintf(stderr,"Erreur d'allocation mémoire\n");
		assert(0);
	}
	for (i = 0; i<HASHSIZE; i++)
		(*h)[i] = new_liste();
	return h;
}

/* ajoute dans la table de hachage h un maillon avec les données i,j.
 * La liste choisie à le numéro grad  */
void hash_add(hashtable *h, uint32_t i, uint32_t j, uint8_t grad) {
	liste_add_tete((*h)[grad], i, j);
}

/* renvoie le premier maillon contenu dans la liste numéro grad */
maillon *hash_rem(hashtable *h, uint8_t grad) {
	return liste_rem_tete((*h)[grad]);
}

/* La fonction renvoie le numéro de la première liste non vide.
 * Si la table de hachage est vide, alors -1 est renvoyé */
int16_t hash_first_not_empty(hashtable *h) {
	int16_t i;
	for (i = 0; i<HASHSIZE; i++) {
		if (!liste_est_vide((*h)[i]))
			return i;
	}
	return -1;
}

/* libère la table de hachage h de la mémoire */
void hash_free(hashtable *h) {
	uint16_t i;
	for (i = 0; i<HASHSIZE; i++)
		liste_free((*h)[i]);
	free(h);
}

