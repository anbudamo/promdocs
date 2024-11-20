CC=gcc
LFLAGS=-lprom -lpromhttp -lmicrohttpd
BIN=main

main:
	$(CC) main.c -o $(BIN) $(LFLAGS)

clean:
	rm $(BIN)
