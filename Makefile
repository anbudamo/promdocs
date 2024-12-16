CC=gcc
LFLAGS=-lprom -lpromhttp -lmicrohttpd -lm
BIN=main
OBJECTS=main.o parse.o metric.o
HEADERS=parse.h metric.h

$(BIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN) $(LFLAGS)

%.o: %.c %.h
	$(CC) -c $< -o $@ 

parse: parse.c
	$(CC) $< -o $@

clean:
	rm -f $(BIN) $(OBJECTS)
