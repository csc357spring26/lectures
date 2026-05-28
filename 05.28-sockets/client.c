#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    uint32_t ipaddr;

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       already-running server, which requires knowing the server's
     *       address and port. This requests a 32-bit TCP/IPv4 address, which
     *       is likely the common sense setting. */
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, &addr);

    /* NOTE: It is possible that multiple addresses could be used to access the
     *       same server, so "getaddrinfo" produces a pointer to the head of a
     *       dynamically allocated linked list of addresses for us to try. For
     *       brevity, we assume that the first address always works. */
    ipaddr = ntohl(((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

    printf("Connected to %d.%d.%d.%d.\n",
     (ipaddr & 0xFF000000) >> 24,
     (ipaddr & 0x00FF0000) >> 16,
     (ipaddr & 0x0000FF00) >> 8,
     (ipaddr & 0x000000FF) >> 0);

    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
