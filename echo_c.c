#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include "client_functions.h"

// this file was written by Nicolette


// this is the final product of the client.c code after merging the different 
// aspects of modification to the original code from the tutorial

// the functions can be found in Client_Functions
// that file also has comments on most of the lines explaining what each statement does
// the way the calls should be made and what variables are needed are found in the comments
// of this code


// ClientWCommentsV1

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) 
{
    int sockfd, portno, n;
	unsigned int length;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
	//create a socket
	// seems a little short right now to make its own function
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
	// end of making a socket
    server = gethostbyname(argv[1]);
	// connect to a server
	// call would be:
	ConectToServer(server, serv_addr, portno, sockfd);
	
	if (argv[3] == "UDP")
	{
		length=sizeof(struct sockaddr_in);
		WriteUDPServer(buffer, sockfd, n);
		ReadUDPServer(buffer, sockfd, n);
		
	}
   else{
	   if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
	//end of connecting
	//write to server
	// call would be:
	
	 WriteToServer(buffer, sockfd, n)
   
	//end of write to server
	// read from server
	// call would be:
	 ReadFromServer(buffer, sockfd, n)
    
	// end of read from server
   }
    close(sockfd);
    return 0;
}
