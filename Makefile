CC=gcc
CFLAGS=-Wall -std=c99
LIBS=-lgmp

all: key_generate signature encryption e3rsa

key_generate: key_generate.c
	$(CC) $(CFLAGS) -o key_generate key_generate.c $(LIBS)

signature: signature.c
	$(CC) $(CFLAGS) -o signature signature.c $(LIBS)

encryption: encryption.c
	$(CC) $(CFLAGS) -o encryption encryption.c $(LIBS)

e3rsa: main.c
	$(CC) $(CFLAGS) -o e3rsa main.c $(LIBS)

clean:
	rm -f key_generate signature encryption e3rsa
