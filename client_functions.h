// .h file for client_functions

// written by Nicolette

#ifndef "CLIENT_FUNCTIONS.H"
#define "CLIENT_FUNCTIONS.H"


void ConnectToServer(struct hostent *server, struct sockaddr_in serv_addr, int portno, int sockfd);

void WriteToServer(char buffer[256], int sockfd, int n);

void ReadFromServer(char buffer[256], int sockfd, int n);

void WriteUDPServer(char buffer [256], int sockfd, int n);

void ReadUDPServer(char buffer [256], int sockfd, int n);

#endif