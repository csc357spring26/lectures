list.o: list.c list.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c list.c

# NOTE: Arguably, while we are debugging, it is okay if we have warnings; that
#       may just be because we aren't done yet. It's only once we compile the
#       final version of our code that we want to use -Werror.
debug:
	gcc -Wall -Wextra -ansi -pedantic -g -c list.c

# NOTE: While we are periodically testing and iteratively developing, we should
#       make sure to run our tests through Valgrind, so as to catch any leaks
#       or other misuses of memory early on.
test: debug
	gcc -Wall -Wextra -ansi -pedantic -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
