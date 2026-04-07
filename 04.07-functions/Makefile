# NOTE: There is no need to compile "add.h", which was included in "test.c".
#       Essentially, the contents of "add.h" are already part of "test.c" by
#       the time "test.c" is compiled.
a.out: test.c add.c
	gcc -Wall -Wextra -Werror -ansi -pedantic test.c add.c
