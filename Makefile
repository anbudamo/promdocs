CC=gcc
LFLAGS=-lprom -lpromhttp -lmicrohttpd
BIN=main
OBJECTS=main.o parse.o
HEADERS=parse.h

$(BIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN) $(LFLAGS)

%.o: %.c %.h
	$(CC) -c $< -o $@ 

parse: parse.c
	$(CC) $< -o $@

clean:
	rm -f $(BIN) $(OBJECTS)
