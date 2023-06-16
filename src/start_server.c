#include "server.h"

void error(char *msg) {
    perror(msg);
    exit(0);
}

// Start server with listener into socket
void start_server(int *listener, char* port) {

    // Error variable
    int e;

    // Socket parameters
    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = IPPROTO_TCP;

    // Get addresses using parameters
    struct addrinfo *results;
    e = getaddrinfo(NULL, port, &hints, &results);

    if (e != 0) { error("Address error"); }

    // Create a socket using address information
    struct addrinfo *r;
    int fd;
    for (r = results; r != NULL; r = r->ai_next) {

        fd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
        if (fd == -1) {
            continue;
        } else {
            break;
        }

        close(fd);
    }

    freeaddrinfo(results);

    // If no socket is able to be created
    if (r == NULL) { error("Could not connect"); }

    // Allow multiple servers to accept connections on current IP
    int optval = 1;
    e =  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if(e == -1) { error("sso ERROR"); }

    // Allow non-blocking I/O
    e = ioctl(fd, FIONBIO, (char*) &optval);
    if(e == -1) { error("ioctl ERROR"); }

    // Bind socket to port and protocol
    e = bind(fd, r->ai_addr,  r->ai_addrlen);
    if(e == -1) { error("bind ERROR"); }


    // Listener socket for connection requests
    e = listen(fd, SOMAXCONN);
    if(e == -1) { error("listen ERROR"); }

    *listener = fd;

}
