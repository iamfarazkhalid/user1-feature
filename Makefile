# writen by Kent and Nicolette

FLAGS = -wall -lsocket
CC = g++
DEBUG = -g
CLFAGS = -wall $(DEBUG)

all : client client_functions server server_functions log

client: client.o
	$(CC) $(FLAGS) $(CFLAGS) -c  echo_c.c

client_functions:     client_functions.o
	$(CC) $(FLAGS) $(CFLAGS) -o client_functions.o

client_functions.o: client_functions.c client_functions.h
	$(CC) $(FLAGS) $(CFLAGS) -c client_functions.c

server:	   server.o
	$(CC) $(FLAGS) $(CFLAGS) -o echo_s.o

server.o: server.c
	$(CC) $(FLAGS) $(CFLAGS) -c echo_s.c

server_functions:	server_functions.o
	$(CC) $(FLAGS) $(CFLAGS) -o server_functions.o

server_functions.o: server_functions.c server_functions.h
	$(CC) $(FLAGS) $(CFLAGS) -c server_functions.c
	
log: log_s.o
	$(CC) $(FLAGS) $(CFLAGS) -o log_s.o
	
log_s.o:	log_s.c 
	$(CC) $(FLAGS) $(CFLAGS) -c log_s.c
	
clean:
	rm client client.o client_functions client_functions.o server server.o server_functions server_functions.o log log_s.o	

