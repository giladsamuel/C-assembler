CC = gcc
CFLAGS = -g -ansi -pedantic -Wall

assembler: assembler.o preprocessor.o hash_table.o str_helper.o first_pass.o second_pass.o instructions.o directives.o binary_word.o
	$(CC) $(CFLAGS) assembler.o preprocessor.o hash_table.o str_helper.o first_pass.o second_pass.o instructions.o directives.o binary_word.o -o assembler

assembler.o: assembler.c preprocessor.h hash_table.h str_helper.h
	$(CC) -c $(CFLAGS) assembler.c -o assembler.o

preprocessor.o: preprocessor.c preprocessor.h str_helper.h hash_table.h
	$(CC) -c $(CFLAGS)  preprocessor.c -o preprocessor.o

hash_table.o: hash_table.c hash_table.h str_helper.h
	$(CC) -c $(CFLAGS) hash_table.c -o hash_table.o

str_helper.o: str_helper.c str_helper.h
	$(CC) -c $(CFLAGS) str_helper.c -o str_helper.o

first_pass.o: first_pass.c first_pass.h hash_table.h directives.h instructions.h second_pass.h binary_word.h
	$(CC) -c $(CFLAGS) first_pass.c -o first_pass.o

second_pass.o: second_pass.c second_pass.h hash_table.h first_pass.h
	$(CC) -c $(CFLAGS) second_pass.c -o second_pass.o

instructions.o: instructions.c instructions.h binary_word.h instruction_type.h hash_table.h
	$(CC) -c $(CFLAGS) instructions.c -o instructions.o

directives.o: directives.c directives.h hash_table.h first_pass.h binary_word.h
	$(CC) -c $(CFLAGS) directives.c -o directives.o

binary_word.o: binary_word.c binary_word.h instruction_type.h
	$(CC) -c $(CFLAGS) binary_word.c -o binary_word.o

clean:
	rm -f *.o assembler