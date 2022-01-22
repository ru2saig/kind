CFLAGS = -std=c99 -pedantic -Wall -Wno-deprecated-declarations

kind: main.c
	$(CC) $(CFLAGS) `pkg-config --cflags gtk+-3.0` $<  -o $@ -lX11 -lXi `pkg-config --libs gtk+-3.0`
clean:
	rm -f kind
