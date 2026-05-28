#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, n, m;
    char buf[81];
    struct pollfd clients[17];

    /* NOTE: This program, the "server" will passively wait for other processes
     *       on other computers to connect to it. The server need not know the
     *       clients' addresses or ports, but it does need to request a port to
     *       which the clients can connect. */
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, argv[1], &hints, &addr);

    /* NOTE: Using the information produced by "getaddrinfo", the server must
     *       first open a socket bound to that specific port. */
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(fd, addr->ai_addr, addr->ai_addrlen);

    /* NOTE: Then, the server must listen for new connections. For simplicity,
     *       we assume we never have to handle more than 16 simultaneous
     *       clients. */
    listen(fd, 16);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    clients[0].fd = fd;
    clients[0].events = POLLIN;
    m = 1;

    while (poll(clients, m, m > 1 ? -1 : 10000)) {
        int i;

        /* NOTE: Since "poll" doesn't know whether or not one client is more
         *       important than the rest, it only tells us that at least one
         *       client has data; it doesn't tell us which one. */
        for (i = 0; i < m; i++) {
            if (clients[i].revents & POLLIN) {
                if (i == 0) {
                    /* NOTE: If we cared to know information about the client we accepted, such
                     *       as its address, we could pass pointers to structures that would
                     *       be populated with that data. */
                    clients[m].fd = accept(clients[0].fd, NULL, NULL);
                    clients[m].events = POLLIN;
                    fcntl(clients[m].fd, F_SETFL, O_NONBLOCK);
                    m++;
                }
                else {
                    while ((n = read(clients[i].fd, buf, 80)) > 0) {
                        buf[n] = '\0';
                        printf("Read \"%s\" from a client-to-server socket.\n", buf);
                    }

                    /* NOTE: With the socket connected to the client set to non-blocking,
                     *       there are two ways to break the above loop: either the
                     *       connection is closed or there is no data available at the
                     *       moment. */
                    if (n == 0 || errno != EAGAIN) {
                        close(clients[i].fd);
                        clients[i] = clients[m - 1];
                        m--;
                    }
                }
            }
        }
    }

    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
