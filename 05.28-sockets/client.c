#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    uint32_t ipaddr;
    int fd, n;
    char buf[81];

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
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    connect(fd, addr->ai_addr, addr->ai_addrlen);

    ipaddr = ntohl(((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);
    printf("Connected to %d.%d.%d.%d.\n",
     (ipaddr & 0xFF000000) >> 24,
     (ipaddr & 0x00FF0000) >> 16,
     (ipaddr & 0x0000FF00) >> 8,
     (ipaddr & 0x000000FF) >> 0);

    /* NOTE: In POSIX, all I/O appears to be file I/O, and sockets are no
     *       exception. Note that it is possible that the network is too busy
     *       to send the entire buffer at once, in which case it is our
     *       responsibility to try to send the rest later. */
    while ((n = read(STDIN_FILENO, buf, 80)) > 0) {
        int i = 0;

        while (i < n) {
            i += write(fd, buf + i, n - i);
        }
    }

    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
