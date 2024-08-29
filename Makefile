all: tp.o automato.o matriz.o
	@gcc tp.o automato.o matriz.o -o exe
	@rm -r tp.o automato.o matriz.o
tp.o: tp.c
	@gcc tp.c -c -Wall
automato.o: automato.c
	@gcc automato.c -c -Wall
matriz.o: matriz.c
	@gcc matriz.c -c -Wall
val:
	@gcc -g -o exeval matriz.c automato.c tp.c -Wall
valrun: val
	@valgrind --leak-check=full --track-origins=yes -s ./exeval
run:
	@./exe
