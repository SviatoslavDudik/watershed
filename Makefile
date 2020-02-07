CC=gcc
OPTIONS=-Wall -ansi -pedantic

main: main.o watershed.o image.o lodepng.o
	$(CC) $(OPTIONS) $^ -o $@

main.o: main.c watershed.h image.h lodepng.h
	$(CC) $(OPTIONS) $< -c
watershed.o: watershed.c watershed.h image.h lodepng.h
	$(CC) $(OPTIONS) $< -c
image.o: image.c image.h lodepng.h
	$(CC) $(OPTIONS) $< -c
lodepng.o: lodepng.c lodepng.h
	$(CC) $(OPTIONS) $< -c

clean:
	rm *.o
