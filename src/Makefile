PROG = server
OBJS = server.o run_server.o start_server.o client_request.o 

CC = gcc
CFLAGS = -g -Wall

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all : $(PROG)

$(PROG) : server.h $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean :
	rm -rf $(PROG) $(OBJS)
