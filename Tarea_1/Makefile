main: main_b.c main_l.c
	gcc -o ocultador main_l.c laberinto.h -I -Wall
	gcc -o buscador  main_b.c laberinto.h -I -Wall

clean:
	rm -r laberinto ocultador buscador