a.out: test.c swap.c
	gcc -Wall -Wextra -Werror -ansi -pedantic test.c swap.c

# NOTE: Under the assumption that the programmer knows what they are doing, the
# 		C compiler strips out information such as line numbers that would be
# 		useful when debugging. The "-g" flag puts that information back in.
debug: test.c swap.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -g test.c swap.c
