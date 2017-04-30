/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void dostuff(int); /* function prototype */
// system call fails 
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, pid;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;	// internet address.
	//Port number on which the server will accept connections.
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);	//system call creates a new socket.
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));		//Sets all values in a buffer to zero.
     portno = atoi(argv[1]);					//Convert this from a string of digits to an integer.
     serv_addr.sin_family = AF_INET;			//Address family.
     serv_addr.sin_addr.s_addr = INADDR_ANY;	//IP address of the host.
     serv_addr.sin_port = htons(portno);		//Converts a port number in host byte order to a port number in network byte order.
     //System call binds a socket to an address.
	 if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);							//Listen on the socket for connections.
     clilen = sizeof(cli_addr);
	 //System call causes the process to block until a client connects to the server. 
     while (1) {
         newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");
         //If it succeeded creat a new process and send the client to it.
		 pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
     } /* end of while */
     close(sockfd);
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff (int sock)
{
   int n;
   char buffer[256];		//The server reads characters from the socket connection into this buffer.
      
   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");
   printf("Here is the message: %s\n",buffer);
   n = write(sock,"Server: I got your message",26);
   if (n < 0) error("ERROR writing to socket");
}
