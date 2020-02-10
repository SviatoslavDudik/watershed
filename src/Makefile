IDIR=../include
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -I$(IDIR)

ODIR=../obj

_DEPS=watershed.h image.h hashtable.h liste.h lodepng.h
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ=main.o watershed.o image.o lodepng.o hashtable.o liste.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm $(ODIR)/*.o
