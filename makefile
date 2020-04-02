derlecalistir:program calistir

fields.o:
	gcc -I "./include/libfdr" -c ./src/libfdr/fields.c -o ./lib/libfdr/fields.o
dllist.o:
	gcc -I "./include/libfdr" -c ./src/libfdr/dllist.c -o ./lib/libfdr/dllist.o
jval.o:
	gcc -I "./include/libfdr" -c ./src/libfdr/jval.c -o ./lib/libfdr/jval.o
game.o:
	gcc -I "./include/libfdr" -I "./include" -c ./src/game.c -o ./lib/game.o
main.o:
	gcc -I "./include/libfdr" -I "./include" -c ./src/main.c -o ./lib/main.o

program:main.o fields.o dllist.o jval.o game.o
	gcc ./lib/libfdr/fields.o ./lib/libfdr/jval.o ./lib/libfdr/dllist.o ./lib/main.o ./lib/game.o -o ./bin/chain_heal -lm

calistir:
	./bin/chain_heal 2 1 4 500 0.25 < ./doc/small.txt
