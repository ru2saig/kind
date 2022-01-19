kind: main.c
	$(CC) $< -g3 --std=c99 -pedantic -Wall -o $@ -lX11 -lXi `pkg-config --cflags gtk+-3.0`
clean:
	rm -f kind
