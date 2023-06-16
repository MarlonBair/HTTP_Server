#include "server.h"

// Error variable
int e;

// To shutdown variable
int to_shutdown = 0;

// Catch input signals to shutdown server
void catch_signal(int signal) {
	to_shutdown = 1;
}

// Gracefully shutdown server	
void exit_server(int fd, struct epoll_event *events) {

	 // Close listener socket
    e = close(fd);
    if(e == -1) { error("Close error"); }

    free(events);
    
	printf("Server shutdown successful\n");
	exit(1);
}

void run_server(int fd) {

	// Number of sockets
    int fdsCount = 1;
	    
	 // Collection of sockets and events data
    struct epoll_event event;
    struct epoll_event *events;

    signal(SIGINT, catch_signal);
    signal(SIGTERM, catch_signal);

    // Create event of listener socket
    int epoll_fd = epoll_create1(0);
    if(epoll_fd == -1) { error("epoll create error"); }
    event.data.fd = fd;
    event.events = EPOLLIN;

    // Add lisener epoll to events collection
    e = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    if(e == -1) { error("epoll_ctl error"); }

    events = calloc(MAX_POLLS_LEN, sizeof(event));

    printf("Server started successfully\n");

    // Server loop
    for(; ;) {

    	if(to_shutdown) {
    		exit_server(fd, events);
    	}

        // Poll sockets to see if client is connecting
        int readable_polls = epoll_wait(epoll_fd, events, MAX_POLLS_LEN, -1);

        // If no active sockets
        if(readable_polls == -1 || readable_polls == 0) {
            continue;
        }

        // Iterate through sockets to find client
        for(int i = 0; i < fdsCount; i++) {
        
            if(events[i].events == 0) { continue; };
            if(!(events[i].events == EPOLLIN)) {
                close(events[i].data.fd);
                continue;
            }

            // If listener, accept new client
            if(events[i].data.fd == fd) {

                int new_fd = accept(fd, NULL, NULL);

                if(new_fd <= -1 && errno != EWOULDBLOCK) { error("accept error"); }

                // Add client socket to event collection
                event.data.fd = new_fd;
                event.events = EPOLLIN;
                fdsCount++;
                e = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &event);
                if(e == -1) { error("epoll_ctl error"); }

            } else {

                // Handle client input and output, then close socket
                client_request(events[i].data.fd);
                close(events[i].data.fd);

            }

        }
    }   
}
