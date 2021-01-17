#------------------------------------------------------------------------------
# Despina Patronas, Dpatrona
# 2021 Winter CSE 101 pa1
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make ModelListTest     make ModelListTest
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -std=c11 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c11 -Wall -c Lex.c

ListClient: ListClient.o List.o
	gcc -std=c11 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -std=c11 -Wall -c ListClient.c

ModelListTest: ModelListTest.o List.o
	gcc -std=c11 -Wall -o ModelListTest ModelListTest.o List.o

ModelListTest.o : ModelListTest.c List.h
	gcc -std=c11 -Wall -c ModelListTest.c

List.o : List.c List.h
	gcc -std=c11 -Wall -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

checkClient : 
	valgrind --leak-check=full ListClient

checkLex :
	valgrind --track-origins=yes Lex
	valgrind --leak-check=full Lex in3 blah3


