CC=gcc
CFLAGS = -Wall -g -std=c11 -pedantic -ansi 

all: glob permutations_of_string

glob:
	$(CC) $(CFLAGS) glob.c -o main_glob

permutations_of_string:
	$(CC) $(CFLAGS) permutations_of_string.c      -o main_permutations_of_string 
	$(CC) $(CFLAGS) printf_format_columns.c       -o main_printf_format_columns
	$(CC) $(CFLAGS) scanf_read_int.c              -o main_scanf_read_int
	$(CC) $(CFLAGS) strlen_null_terminate_error.c -o main_strlen_null_terminate_error
	$(CC) $(CFLAGS) strncmp_off_by_one.c          -o main_strncmp_off_by_one


clean:
	rm -rf ./*.dSYM
	rm main_*
