CC = gcc
CFLAGS = -g -ansi -pedantic -Wall

assambler: assambler.o preprocessor.o hash_table.o str_helper.o first_pass.o second_pass.o instructions.o directives.o
	$(CC) $(CFLAGS) assambler.o preprocessor.o hash_table.o str_helper.o first_pass.o second_pass.o instructions.o directives.o -o assambler

assambler.o: assambler.c preprocessor.h hash_table.h str_helper.h
	$(CC) -c $(CFLAGS) assambler.c -o assambler.o

preprocessor.o: preprocessor.c preprocessor.h str_helper.h hash_table.h
	$(CC) -c $(CFLAGS)  preprocessor.c -o preprocessor.o

hash_table.o: hash_table.c hash_table.h str_helper.h
	$(CC) -c $(CFLAGS) hash_table.c -o hash_table.o

str_helper.o: str_helper.c str_helper.h
	$(CC) -c $(CFLAGS) str_helper.c -o str_helper.o

first_pass.o: first_pass.c first_pass.h
	$(CC) -c $(CFLAGS) first_pass.c -o first_pass.o

second_pass.o: second_pass.c second_pass.h
	$(CC) -c $(CFLAGS) second_pass.c -o second_pass.o

instructions.o: instructions.c instructions.h
	$(CC) -c $(CFLAGS) instructions.c -o instructions.o

directives.o: directives.c directives.h
	$(CC) -c $(CFLAGS) directives.c -o directives.o

clean:
	rm -f *.o assambler