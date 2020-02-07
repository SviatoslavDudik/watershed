#include "hashtable.h"

hashtable *new_hash() {
	uint16_t i;
	hashtable *h;
	printf("hash size = %lu\n", sizeof(hashtable));
	h = (hashtable*) malloc(sizeof(hashtable));
	if (h == NULL) {
		fprintf(stderr,"Erreur d'allocation mémoire\n");
		assert(0);
	}
	for (i = 0; i<HASHSIZE; i++)
		(*h)[i] = new_liste();
	return h;
}

void hash_add(hashtable *h, uint32_t i, uint32_t j, uint8_t grad) {
	liste_add_tete((*h)[grad], i, j);
}

maillon *hash_rem(hashtable *h, uint8_t grad) {
	return liste_rem_tete((*h)[grad]);
}

void hash_free(hashtable *h) {
	uint16_t i;
	for (i = 0; i<HASHSIZE; i++)
		liste_free((*h)[i]);
	free(h);
}

