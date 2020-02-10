#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define HASHSIZE 256

typedef liste *hashtable[HASHSIZE];

/* crée une nouvelle table de hachage */
hashtable *new_hash();

/* ajoute dans la table de hachage h un maillon avec les données i,j.
 * La liste choisie à le numéro grad  */
void hash_add(hashtable *h, uint32_t i, uint32_t j, uint8_t grad);

/* renvoie le premier maillon contenu dans la liste numéro grad */
maillon *hash_rem(hashtable *h, uint8_t grad);

/* La fonction renvoie le numéro de la première liste non vide.
 * Si la table de hachage est vide, alors -1 est renvoyé */
int16_t hash_first_not_empty(hashtable *h);

/* libère la table de hachage h de la mémoire */
void hash_free(hashtable *h);

#endif
