# NOTE: By splitting the compilation process up per source file, if we change
#       only one of the source files, we only have to recompile that one source
#       files; we can reuse the existing remaining object files.
a.out: test.o swap.o
	gcc test.o swap.o

test.o: test.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c test.c

swap.o: swap.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c swap.c

# NOTE: The exception is that when debugging, we probably want to recompile
#       everything from scratch every time, so as to avoid inadvertently using
#       stale object files.
debug: test.c swap.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -g test.c swap.c
