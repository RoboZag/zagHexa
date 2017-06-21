/*
  - Create the socket header
*/
#ifndef _client_l_H
#define _client_l_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>

#define MESSAGE_FREQ 1


class client_l{
 public:
	void error(const char *msg);
	int initiate_Client(int argc, char *argv[]);
 private:
	int sockfd, portno;
	struct sockaddr_in serv_addr;
    	struct hostent *server;
};
#endif
