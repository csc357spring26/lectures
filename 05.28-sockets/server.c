#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;

    /* NOTE: This program, the "server" will passively wait for other processes
     *       on other computers to connect to it. The server need not know the
     *       clients' addresses or ports, but it does need to request a port to
     *       which the clients can connect. */
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, argv[1], &hints, &addr);

    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
