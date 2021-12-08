CC=gcc
OPTS=-g -std=c99 -Werror

all: main.o predictor.o tournament.o gshare.o pshare.o
	$(CC) $(OPTS) -lm -o ./build/predictor ./build/main.o ./build/predictor.o ./build/tournament.o ./build/gshare.o ./build/pshare.o

main.o: main.c predictor.h
	$(CC) $(OPTS) -o ./build/main.o -c main.c

predictor.o: predictor.h predictor.c tournament.o gshare.o pshare.o 
	$(CC) $(OPTS) -o ./build/predictor.o -c predictor.c
	
tournament.o: tournament.h tournament.c
	$(CC) $(OPTS) -o ./build/tournament.o -c tournament.c
	
pshare.o: pshare.h pshare.c
	$(CC) $(OPTS) -o ./build/pshare.o -c pshare.c
	
gshare.o: gshare.h gshare.c
	$(CC) $(OPTS) -o ./build/gshare.o -c gshare.c

clean:
	rm -f ./build/*.o ./build/predictor;