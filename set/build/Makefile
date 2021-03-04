CC=gcc
RESULT=set
PATH_LIST=../../avl_tree
PATH_CLIB=../../clib

main.o:
	$(CC) -g ../main.c

compil_list:
	$(CC) -g -c $(PATH_LIST)/avl_tree.c $(PATH_LIST)/private_avl_tree_ip.c

compil_clib:
	$(CC) -g -c $(PATH_CLIB)/clib.c

compil:
	$(CC) -g -Wall -c ../*.c
	make compil_list
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
	rm ./$(RESULT)
