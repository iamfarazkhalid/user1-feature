//Name: Faraz Khalid
// This is the server_function.c file which contains all the common functions found in server.c

#include "server_function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

void BindToAddress (int sockfd, struct sockaddr_in serv_addr,  int portno) {

     if (sockfd < 0) 
        error("ERROR opening socket"); // Make sure the socket is successfully opened. If not, print out the error message.
     bzero((char *) &serv_addr, sizeof(serv_addr)); //initialization of all the variables.
     portno = atoi(argv[1]); //the port number connection was passed as an argument and is now being initialized to the variable, portno.
     serv_addr.sin_family = AF_INET; 
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno); //The portno variable is converted into a network byte order and is put into sin_port.
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) //calls the bind function.
     {
	   error("ERROR on binding"); //if it is unsuccessful, then print error message.
     }
}

void AcceptConnectionCall (struct scokaddr_in cli_addr, struct sockaddr *,  int sockfd) {
	clilen = sizeof(cli_addr); //stores the size of the address of the client. This is essential to accept the system call. One of the arguments for it.
     	
	//accept() causes the process to block until a client connects to the server.
	//The accept() wakes up when a connection from a client has been successfully established.
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); 
     		if (newsockfd < 0) //If newsockfd is a negative number, it means that the connection failed to establish.
		{ 
          		error("ERROR on accept"); //If connection fails, print error message.
		}	
    	bzero(buffer,256); //clears the buffer
}

void ReadFromClient (char buffer[256], int sockfd, int n) {
	
	n = read(newsockfd,buffer,255); // read returns as the number of charecters read and then saves that value to "n".
	if (n < 0) //if n is a negative number, something went wrong and error message is printed.
	{
		error("ERROR reading from socket"); //if n < 0, print error message.
	}

	printf("Here is the message: %s\n",buffer); //prints the message to the console.
}

void WriteToClient (char buffer[256], int sockfd, int n) {

	n = write(newsockfd,"I got your message",18); //send a pre-prepared message to client.
     	if (n < 0) // if n is a negative numbers, something went wrong
	{
		error("ERROR writing to socket"); //error message is displayed.
	}
}

// function added by Nicolette based on code from Afham
void CreateUDPChild(int n, int sockfd, struct sockaddr_in cli_addr, int clilen)
{
		// added by Nicolette for Deliverable 2
		int sock2, length;
		struct sockaddr_in server;
		socklen_t tolen;
		tolen = sizeof(struct sockaddr_in);
		
		// set up the timestamp as the time the child was created
		time_t callTime;
		struct tm * timeStamp;
		time(&callTime);
		timeStamp = localTime(&callTime);
		


		n = recvfrom(sockfd,buffer,256(struct sockaddr *)&cli_addr,&clilen);
       if (n < 0) error("recvfrom");
       write(1,"Received a datagram: ",21);
       write(1,buffer,n);
       n = sendto(sockfd,"Got your message\n",17,         // sends message back to client if connection is successful
                  0,(struct sockaddr *)&cli_addr,clilen);
       if (n  < 0) error("sendto");
	   
	   // added by Nicolette for Deliverable 2
	   sock2 = socket(AF_INET, SOCK_DGRAM, 0); 
		if (sock2 < 0) error("Opening socket");
		length = sizeof(server);
		bzero(&server,length);
		server.sin_family=AF_INET;
		server.sin_addr.s_addr=INADDR_ANY;
		server.sin_port=htons(9999);
	   bind(sock2,(struct sockaddr *)&server,length)
	   clilen = sizeof(struct sockaddr_in);
	   sendto(1, cli_addr, clilen, 0, (struct soackaddr *)&server, tolen);			// this is IP address?
	   sendto(1, buffer, n, 0, (struct soackaddr *)&server, tolen);					// this is message from client
	   sendto(1, timeStamp, 50, 0, (struct soackaddr *)&server, tolen);		// this should write timestamp?
	   

}	


void CreateChild(int newsockfd, int sockfd, struct sockaddr_in cli_addr, socklen_t fromlen)
{
		// added by Nicolette for Deliverable 2
		int sock2, length;
		struct sockaddr_in server;
		socklen_t tolen;
		tolen = sizeof(struct sockaddr_in);
		
		// set up the timestamp as the time the child was created
		// added by Nicolette for Deliverable 2
		time_t callTime;
		struct tm * timeStamp;
		time(&callTime);
		timeStamp = localTime(&callTime);


		newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
	
	
	// added by Nicolette for Deliverable 2
	   sock2 = socket(AF_INET, SOCK_DGRAM, 0); 
		if (sock2 < 0) error("Opening socket");
		length = sizeof(server);
		bzero(&server,length);
		server.sin_family=AF_INET;
		server.sin_addr.s_addr=INADDR_ANY;
		server.sin_port=htons(9999);
	   bind(sock2,(struct sockaddr *)&server,length)
	   clilen = sizeof(struct sockaddr_in);
	   sendto(1, cli_addr, clilen, 0, (struct soackaddr *)&server, tolen);			// this is IP address?
	   sendto(1, buffer, n, 0, (struct soackaddr *)&server, tolen);					// this is message from client
	   sendto(1, timeStamp, 50, 0, (struct soackaddr *)&server, tolen);		// this should write timestamp?
}

