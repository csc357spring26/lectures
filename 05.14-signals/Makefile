CFLAGS = -Wall -Wextra -std=gnu11 -pedantic

all: parent child

debug: CFLAGS += -g
debug: clean all

child: child.o
	gcc -o child child.o

parent: parent.o
	gcc -o parent parent.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
