# NOTE: By splitting the compilation process up and making the individual
#       object files first, if we ever change one source file, we only have to
#       recompile the corresponding object file.
a.out: test.o swap.o
	gcc test.o swap.o

test.o: test.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c test.c

swap.o: swap.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c swap.c

# NOTE: However, when debugging, we'll recompile everything from scratch so as
#       to ensure that we don't inadvertently use an older version of our code.
#       We don't care (yet) about efficiency; we care about correctness.
debug: test.c swap.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -g test.c swap.c
