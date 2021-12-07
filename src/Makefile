CC=gcc
OPTS=-g -std=c99 -Werror

all: main.o predictor.o gshare.o pshare.o
	$(CC) $(OPTS) -lm -o ./build/predictor ./build/main.o ./build/predictor.o ./build/gshare.o ./build/pshare.o

main.o: main.c predictor.h
	$(CC) $(OPTS) -o ./build/main.o -c main.c

predictor.o: predictor.h predictor.c gshare.o pshare.o
	$(CC) $(OPTS) -o ./build/predictor.o -c predictor.c
	
gshare.o: gshare.h gshare.c
	$(CC) $(OPTS) -o ./build/gshare.o -c gshare.c

pshare.o: pshare.h pshare.c
	$(CC) $(OPTS) -o ./build/pshare.o -c pshare.c
	
clean:
	rm -f ./build/*.o ./build/predictor;