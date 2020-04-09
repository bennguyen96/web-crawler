CC=gcc
CFLAGS=-g
CFLAGS+=-Wall

crawler: crawler.o
	$(CC) $(CFLAGS) -o crawler crawler.o

crawler.o: crawler.c crawler.h io.c io.h
	$(CC) $(CFLAGS) -c crawler.c io.c

clean:
	rm *.o crawler

test:
	./crawler ibdhost.com