CC=gcc
RESULT=list

main.o:
	$(CC) -g ../main.c

compil_clib:
	$(CC) -g -Wall -c ../../clib/clib.c

compil:
	$(CC) -g -Wall -c ../*.c
	make compil_clib
	

link:
	$(CC) *.o -o $(RESULT)


build:
	make compil
	make link


run:
	./$(RESULT)

debug:
	kdbg ./$(RESULT)


clear:
	rm *.o
	rm $(RESULT)

