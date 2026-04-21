list.o: list.c list.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c list.c

# NOTE: Arguably, while we are in the process of testing and debugging, warnings
#       are okay; a warning may simply mean that we haven't gotten around to
#       implementing the corresponding functionality yet.
debug:
	gcc -Wall -Wextra -ansi -pedantic -g -c list.c

# NOTE: While we are periodically testing and iteratively developing, we should
#       make sure to run our tests through Valgrind, so as to catch any leaks
#       or other misuses of memory early on.
test: debug
	gcc -Wall -Wextra -ansi -pedantic -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
