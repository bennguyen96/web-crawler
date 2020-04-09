CC=gcc
CFLAGS=-g
CFLAGS+=-Wall

crawler: src/crawler.o src/io.o src/uriparse.o src/llist.o
	$(CC) $(CFLAGS) -o crawler src/crawler.o src/io.o src/uriparse.o src/llist.o

crawler.o: src/crawler.c
	$(CC) $(CFLAGS) -c src/crawler.c

io.o: src/io.c
	$(CC) $(CFLAGS) -c src/io.c

uriparse.o: src/uriparse.c
	$(CC) $(CFLAGS) -c src/uriparse.c

llist.o: src/llist.c
	$(CC) $(CFLAGS) -c src/llist.c

clean:
	rm crawler src/*.o

test:
	./crawler http://ibdhost.com