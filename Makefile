.PHONY: clean
CC=gcc
CFLAGS=-g -std=c11 -fpic -Wall -D_DEFAULT_SOURCE
BINS=cache
LIBS=libcache.so


all: $(BINS) $(LIBS)

cache: cache.o liblist.so
	$(CC) $(CFLAGS) -L. -llist -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

lib%.so: %.o
	$(CC) $(CFLAGS) -shared -o $@ $<

clean:
	rm -f *.o $(BINS) $(LIBS)
