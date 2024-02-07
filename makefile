CC = gcc
CFLAGS = -ansi -pedantic -Wall

assambler: assambler.o macro.o hash_table.o str_helper.o
	$(CC) $(CFLAGS) assambler.o macro.o hash_table.o str_helper.o -o assambler

assambler.o: assambler.c macro.h
	$(CC) -c $(CFLAGS) assambler.c -o assambler.o

macro.o: macro.c macro.h str_helper.h
	$(CC) -c $(CFLAGS)  macro.c -o macro.o

hash_table.o: hash_table.c hash_table.h
	$(CC) -c $(CFLAGS) hash_table.c -o hash_table.o

str_helper.o: str_helper.c str_helper.h
	$(CC) -c $(CFLAGS) str_helper.c -o str_helper.o

clean:
	rm -f *.o assambler