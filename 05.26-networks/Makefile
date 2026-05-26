CFLAGS = -Wall -Wextra -std=gnu11 -pedantic

all: parent child client server

debug: CFLAGS += -g
debug: clean all

parent: parent.o
	gcc -o parent parent.o

child: child.o
	gcc -o child child.o

client: client.o
	gcc -o client client.o

server: server.o
	gcc -o server server.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
