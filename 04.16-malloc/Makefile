a.out: test.o ops.o
	gcc test.o ops.o

test.o: test.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c test.c

ops.o: ops.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c ops.c

debug: test.c ops.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -g test.c ops.c
