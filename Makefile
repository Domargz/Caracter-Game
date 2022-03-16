bin/main: bin/main.o bin/game.o
	gcc  -g -o bin/main bin/main.o bin/game.o -lncurses 

bin/main.o: src/main.c	
	gcc -g -c -o bin/main.o src/main.c 

bin/game.o: src/game.c src/game.h	
	gcc -g -c -o bin/game.o src/game.c

run:
	./bin/main