/*
  - Create the socket cpp
  - Return the socketfd 
*/

#include <client_l.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


#define MESSAGE_FREQ 1

void client_l::error(const char *msg) {
    perror(msg);
    exit(0);
}

int client_l::initiate_Client(int argc, char *argv[])
{
	if (argc < 3) {
       		fprintf(stderr,"Usage: $ rosrun comm_tcp client_node <hostname> <port> --arguments\nArguments:\n -e : Echo mode\n");
       		exit(0);
    	}	
	portno = atoi(argv[2]);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    	if (sockfd < 0) 
        error("ERROR opening socket");
    	server = gethostbyname(argv[1]); // name or IPv4
    	bzero((char *) &serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    	serv_addr.sin_port = htons(portno);
    	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
	return sockfd;
}



