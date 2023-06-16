#define _GNU_SOURCE
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_POLLS_LEN 32
#define MAX_ANSWER 500

void error(char* msg);

void start_server(int *listener, char* port);

void run_server(int fd);

void client_request(int fd);
