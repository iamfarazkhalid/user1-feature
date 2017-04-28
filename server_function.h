// .h file for the server functions
// written for deliverable one
// updated by Nicolette for deliverable 2

#ifndef "SERVER_FUNCTIONS.H"
#define "SERVER_FUNCTIONS.H"


void BindToAddress (int sockfd, struct sockaddr_in serv_addr, int portno);

void AcceptConnectionCall (struct cli_addr, struct sockaddr *,  int sockfd);

void ReadFromClient (char buffer[256], int sockfd, int n);

void WriteToClient (char buffer[256], int sockfd, int n);

void CreateChild(int newsockfd, int sockfd, struct sockaddr_in cli_addr, socklen_t fromlen);

// added by Nicolette
void CreateUDPChild(int n, int sockfd, struct sockaddr_in cli_addr, int clilen);

#endif
