#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// system call fails 
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;	// internet address
    struct hostent *server;
    char buffer[256];				//The client write characters from this buffer connection into socket
	// Check the port number on which the server will accept connections
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);			//Convert the port number from a string of digits to an integer
    //System call creates a new socket Internet, AF_INET domain for any two hosts on the Internet
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	
    if (sockfd < 0) 
        error("ERROR opening socket");
    //Take the name as an argument and returns a pointer to a hostent containing information about that host
	server = gethostbyname(argv[1]); 
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));  ////Initializes the buffer to zeros
    serv_addr.sin_family = AF_INET;		//  code for the address family
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
	//Establish a connection to the server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
	//Message
    bzero(buffer,256);
    fgets(buffer,255,stdin);
	//write to the socket
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
	//Empty the buffer and be ready to recieve  
    bzero(buffer,256);
    //Read from the socket
	n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
	//Print the recieved message
    printf("%s\n",buffer);
	//Close the socket connection 
    close(sockfd);
    return 0;
}
