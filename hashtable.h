#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define HASHSIZE 256

typedef liste *hashtable[HASHSIZE];


hashtable *new_hash();
void hash_add(hashtable *h, uint32_t i, uint32_t j, uint8_t grad);
maillon *hash_rem(hashtable *h, uint8_t grad);
void hash_free(hashtable *h);

#endif
