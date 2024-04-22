sh: sh.c execute_commands.c execute_commands.h
	gcc -Wall -Wextra -pedantic -std=c11 sh.c execute_commands.c -o sh

ls-grep: ls-grep.c grep_file.c grep_file.h
	gcc -Wall -Wextra -lc -pedantic -std=c11 ls-grep.c grep_file.c -o ls-grep

all: *.c *.h
	gcc -Wall -Wextra -pedantic -std=c11 *.c 

clean:
	rm sh
	rm ls-grep
