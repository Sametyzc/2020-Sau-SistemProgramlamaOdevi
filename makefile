derlecalistir:program calistir

fields.o:
	gcc -I "./include/libfdr" -c ./src/libfdr/fields.c -o ./lib/libfdr/fields.o
dllist.o:
	gcc -I "./include/libfdr" -c ./src/libfdr/dllist.c -o ./lib/libfdr/dllist.o
jrb.o:
	gcc -I "./include/libfdr" -c ./src/libfdr/jrb.c -o ./lib/libfdr/jrb.o
jval.o:
	gcc -I "./include/libfdr" -c ./src/libfdr/jval.c -o ./lib/libfdr/jval.o
game.o:
	gcc -I "./include/libfdr" -I "./include" -c ./src/game.c -o ./lib/game.o
tree.o:
	gcc -I "./include/libfdr" -I "./include" -c ./src/tree.c -o ./lib/tree.o
main.o:
	gcc -I "./include/libfdr" -I "./include" -c ./src/main.c -o ./lib/main.o

program:main.o fields.o dllist.o jrb.o jval.o game.o tree.o
	gcc ./lib/libfdr/fields.o ./lib/libfdr/jrb.o ./lib/libfdr/jval.o ./lib/libfdr/dllist.o ./lib/main.o ./lib/tree.o ./lib/game.o -o ./bin/program -lm

calistir:
	./bin/program 2 1 4 500 0.25 < ./doc/Oyuncu_Bilgileri.txt
