// file that contains the functions for the client
// written by Nicolette Railsback

// connect to the server

#include "client_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void ConnectToServer(struct hostent *server, struct sockaddr_in serv_addr, int portno, int sockfd)
{
	if (server == NULL)								// make sure a server name was given
		{
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
		}
	bzero((char*) &serv_addr, sizeof(serv_addr));		// initialize variables
	serv_addr.sin_family = AF_INET;							// default way to initialize this, unless you want to do something crazy
	bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);						// converts protno to network byte order and puts it in sin_port
}

void WriteToServer(char buffer[256], int sockfd, int n)
{
	printf("Please enter the message: ");			// prompt user
    bzero(buffer,256);							// clear buffer
    fgets(buffer,255,stdin);					// get input
    n = write(sockfd,buffer,strlen(buffer));	// write to server through socket
    if (n < 0) 									// if the n returned was negative, somethign went wrong
	{
         error("ERROR writing to socket");
	}
    bzero(buffer,256);							// clear buffer
}

void ReadFromServer(char buffer[256], int sockfd, int n)
{
	n = read(sockfd,buffer,255);		// read returns n as the num of characters read
    if (n < 0)							// if n is negative, something went wrong
	{
         error("ERROR reading from socket");
	}
    printf("%s\n",buffer);				// print the n characters from buffer to console
}

// following functions were created by Nicolette but using code copied and pasted from Afham
// who got the code from the tutorial
void WriteUDPServer(char buffer [256], int sockfd, int n)
{
	printf("Please enter the message: "); // print the message to be sent to server
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   n=sendto(sockfd,buffer,                                              // sends message to the server
            strlen(buffer),0,(const struct sockaddr *)&server,length);
   if (n < 0) error("Sendto");                                           // error message if message failed to send
}

void ReadUDPServer(char buffer [256], int sockfd, int n)
{
	n = recvfrom(sockfd,buffer,256,0,(struct sockaddr *)&from, &length);   // Receives message rom the server
   if (n < 0) error("recvfrom");                                       // error message if message failed to arrive
   write(1,"Got an ack: ",12);   // Message to be sent 
   write(1,buffer,n);
}