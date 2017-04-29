/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "server_functions.h"
#include <signal.h>
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// by Emnet Nadew
// Zombies clog the process in the kernel and it is a process which has terminated but not fully permited to die and the parent might execute a wait to inform the death of the child 
void *SigCather(int n)// will be called whenever the parent recieves a Child dies
   {
     wait3(NULL,WNOHANG,NULL);//WNOHANG is a set that causes it to be a non-blocking wait
   }

static bool keepRunning=1;//Emnet will check if the system is running or not and set it true 

void exitFunction(int x)//By Emnet
     keeprunning=0;
 }




int main(int argc, char *argv[])
{
	
	while (keeprunning) // this should make the server loop forever talking to multiple clients by Emnet
	{

      signal(SIGINT, exitFunction);//By  Emnet checking signals 


     int sockfd, newsockfd, portno, length;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 
	 // written by Nicolette 
	 int x = argc - 1; // the last variable is the socket type
	 int i = 1;	// index to go through port numbers
	 string logid;
	 int logport;
	 int childpid;
	 
	
	

	//the argumnet passed for log id is stored in the variable called log id and can be used when needed.
	//Faraz Khalid
	
	logid = argv[argc-2];

	// The argument passed for logport is stored in the varibale called logport
	 	// Afham Ahmed 
	 		logport = argv[argc-1];

	 while (i < (argc - 3))		// this should ensure that every port is being listened on - Nicolette
	 {
		 // Nicolette wrote
		 childpid = fork();
		 if (childpid == 0)
		 {
	 
			 while(1){ // to make sure each port continues to be listened on after the first message
			 
			 signal(SIGCHLD,SingCatcher);// by emnet this will ignore the SIGCHLD signal
			 
			 if (argc < 3) {
				 fprintf(stderr,"ERROR, no port provided or no socket type provided\n");
				 exit(1);
			 }
			 
			
			 // datagram socket
			 if (argv[x] == "UDP") // want to use a datagram socket
			 { // this is temp if since i dont know what to check for right now - Nic
				 
				 sockfd = socket(AF_INET, SOCK_DGRAM, 0);
				 
				 BindToAddress(sockfd, serv_addr, portno);
				 
				 
				clilen = sizeof(struct sockaddr_in);

			//while (1) {                                                         // Trying to receive  any incoming udp datagram
			   
			   CreateUDPChild(n, sockfd, cli_addr, clilen, keepRunning);
		  // }
			 }
				 
			else{ // stream socket
			 
			 sockfd = socket(AF_INET, SOCK_STREAM, 0);
			 
			 BindToAddress(sockfd, serv_addr, portno);
					  
			 listen(sockfd,5);
			 
			 clilen = sizeof(cli_addr);
		//by syedhassan
		//while(1) //an infinite loop which allows multiple simultanious connection
		//{
			CreateChild(newsockfd, sockfd, cli_addr, clilen,keepRuning);
			//}

			  }
			}
		 }
		 else{
			 i++;	// increment i to listen on another port
		 }
	}
	}
}
