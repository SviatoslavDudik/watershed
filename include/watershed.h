#ifndef __WATERSHED_H__
#define __WATERSHED_H__

#include "hashtable.h"
#include "image.h"
#include <stdint.h>

myimage CalculerGradient(myimage img, uint16_t rayon);
void CalculerLPE(myimage gradient, myimage m);

#endif
