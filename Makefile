CC = gcc
CFLAGS = -std=c99 -O2 -pedantic -Wall -Wno-deprecated-declarations

all: kind


util.o: util.c
	$(CC) $(CFLAGS) -c $< -o $@

trayicons.o: trayicons.c
	$(CC) $(CFLAGS) `pkg-config --cflags gtk+-3.0` -c $<  -o $@ `pkg-config --libs gtk+-3.0`

kind: kind.c trayicons.o util.o
	$(CC) $(CFLAGS) `pkg-config --cflags gtk+-3.0` $<  trayicons.o util.o -o $@ -lX11 -lXi `pkg-config --libs gtk+-3.0`
clean:
	rm -f kind
	rm trayicons.o

install: 
	mkdir -p /usr/share/kind/
	cp -r icons /usr/share/kind
	cp kind /usr/local/bin

install-systemd: # moves a service file over. Check if a valid directory for this, first?
	cp kind.service /usr/lib/systemd/user/
	systemctl --user enable --now kind.service
