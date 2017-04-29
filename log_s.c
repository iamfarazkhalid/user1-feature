/* Creates a datagram server.  The port 
   number is passed as an argument.  This
   server runs forever */
   
   // the following code is a modified version of code found on http://www.linuxhowtos.org/C_C++/socket.htm
   // the changes were made by Nicolette and Kent

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
//#include "log_funct.h" // not necisary
#include <fstream>
#include <string>

// comment block written by Nicolette
// the following is a To-Do list/ reminders of what this file is for
// this c file is for the logging of things happening on the official server
// most likely need a log functions file. or can just use the normal server functions file
// need to make sure that the port it is communicating with is always 9999
// communicates to server via a UDP port (which is why this version of the code was downloaded from the tutorial

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
   int sock, length, n, childpd;
 int port_number;//syed
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[1024];
   char IPbuf[30];
   char Timebuf[50];
	ofstream myfile;
   
   if (argc < 2) { 
      fprintf(stderr, "ERROR, no port provided\n");
      exit(0);
   }
   port_number=*(argv[argc-1]);//convert the string port number into integer ,syedhassan
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(port_number);  // I think this atio part needs to be changed to 9999, since portno is known
   if (bind(sock,(struct sockaddr *)&server,length)<0) 
       error("binding");
   fromlen = sizeof(struct sockaddr_in);
   myfile.open(echo.log);
   while (1) { // i think here is the part where we need to make child processes to handle each request and print the things to the file
       n = recvfrom(sock,IPbuf,30,0,(struct sockaddr *)&from,&fromlen); // get the IP address
	   n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen); // get the message
	   n = recvfrom(sock,Timebuf,50,0,(struct sockaddr *)&from,&fromlen); // get the timestamp
//       if (n < 0) error("recvfrom"); // dont bother to check if it errored
	   string timestr(Timebuf); // convert timestamp to a string
	   string messgstr(buf);	// convert the message to a string
	   string IPstr(IPbuf);		// convert the IP address to a string

	   if (messgstr == "echo_s is stoping")// By Emnet help and suggestion by Nicollet
	      {
	      exit(0);
	      }
	   childpd = fork();
	   if (childpd == 0) { // we are working with the child
		// call the write function
		//writeToFile(/*timestamp, buf (need to make that a string), IP address of client, myfile*/);
		myfile << timestr << '\t' << '"' << messgstr << '"' << " was recived from " << IPstr << '\n';
		// this should append every entry onto the log file
	   }
	   else{
		   // do nothing
		   // only send child to do stuff
	   }
	   // specifically these writes i think
      // write(1,"Received a datagram: ",21);  // this one maybe writes the timestamp and the tabs
      // write(1,buf,n);						// this one writes the message sent over, maybe it can even include the IP? Have to see how that would work on the other server
	   // then we need another one here that writes the IP address the message came from originally
      // n = sendto(sock,"Got your message\n",17,
      //            0,(struct sockaddr *)&from,fromlen);
      // if (n  < 0) error("sendto");
   }
   myfile.close(log.txt);
   return 0;
 }

