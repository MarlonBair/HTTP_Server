#include "server.h"

int main(int argc, char** argv) {

    // Get index of input port if applicable
    int portIndex = -1;
    for(int i = 1; i < argc - 1; i++) {
        if(strcmp(argv[i], "-p") == 0) {
            portIndex = i + 1;
            break;
        }
    }

    // Get listener socket
    int fd = -1;
    
    if(portIndex != -1) {
        start_server(&fd, argv[portIndex]);
    } else {
        start_server(&fd, "8080");	// Default port
    }

    // Run server loop
    run_server(fd);
}
