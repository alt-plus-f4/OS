sh: sh.c execute_commands.c
	gcc -Wall -Wextra -pedantic -std=c11 sh.c execute_commands.c -o sh

ls-grep: ls-grep.c
	gcc -Wall -Wextra -pedantic -std=c11 ls-grep.c -o ls-grep

line-count: line-count.c
	gcc -Wall -Wextra -pedantic -std=c11 line-count.c -o line-count


all: *.c
	gcc -Wall -Wextra -pedantic -std=c11 *.c 

clean:
	rm *.o
	rm sh