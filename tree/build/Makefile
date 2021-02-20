CC=gcc
RESULT=tree

main.o:
	$(CC) -g ../main.c

compil:
	$(CC) -g -Wall -c ../*.c

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
	rm ./$(RESULT)
