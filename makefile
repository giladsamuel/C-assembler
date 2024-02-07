CC = gcc
CFLAGS = -ansi -pedantic -Wall

assambler: assambler.o preprocessor.o hash_table.o str_helper.o
	$(CC) $(CFLAGS) assambler.o preprocessor.o hash_table.o str_helper.o -o assambler

assambler.o: assambler.c preprocessor.h hash_table.h str_helper.h
	$(CC) -c $(CFLAGS) assambler.c -o assambler.o

preprocessor.o: preprocessor.c preprocessor.h str_helper.h hash_table.h
	$(CC) -c $(CFLAGS)  preprocessor.c -o preprocessor.o

hash_table.o: hash_table.c hash_table.h str_helper.h
	$(CC) -c $(CFLAGS) hash_table.c -o hash_table.o

str_helper.o: str_helper.c str_helper.h
	$(CC) -c $(CFLAGS) str_helper.c -o str_helper.o

clean:
	rm -f *.o assambler