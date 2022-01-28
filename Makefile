CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wno-deprecated-declarations

all: kind

trayicons.o: trayicons.c
	$(CC) $(CFLAGS) `pkg-config --cflags gtk+-3.0` -c $<  -o $@ `pkg-config --libs gtk+-3.0`

kind: kind.c trayicons.o
	$(CC) $(CFLAGS) `pkg-config --cflags gtk+-3.0` $<  trayicons.o -o $@ -lX11 -lXi `pkg-config --libs gtk+-3.0`
clean:
	rm -f kind
	rm trayicons.o
