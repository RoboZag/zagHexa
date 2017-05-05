/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int sockfd, newsockfd, portno, pid, n;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;
char buffer[256];
std_msgs::String message;
std::stringstream stringPub;

void recvmessage(int); 

void start(int argc, char *argv[]);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{     
	//initiate ROS node with name Server 
    ros::init(argc, argv, "Server");
    ros::NodeHandle serverHandler;
	// initiate ROS topic 
    ros::Publisher pub = serverHandler.advertise<std_msgs::String>("Server_Clinet", 1000);
	//Start the server 
    start(argc, argv);
	//Listen to find a client 
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (ros::ok()) {
        newsockfd = accept(sockfd, 
            (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)  {
            close(sockfd);
		//Clear contents of string stream
            stringPub.str(std::string()); 
            recvmessage(newsockfd);
	    pub.publish(message); // Send some message to ROS 
	    n = write(newsockfd,"Server: I got your message",26); // Send some message to the network 
            if (n < 0) error("ERROR writing to socket");
            exit(0);
        }
        else close(newsockfd);
    } /* end of while */
    close(sockfd);
    return 0; /* we never get here */
}


void start(int argc, char *argv[])
{
	std::cout<<("Start the server\n\n");
	if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    	}
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    	if (sockfd < 0) 
        	error("ERROR opening socket");
    	bzero((char *) &serv_addr, sizeof(serv_addr));
    	portno = atoi(argv[1]);
    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_addr.s_addr = INADDR_ANY;
    	serv_addr.sin_port = htons(portno);
    	if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) 
            	error("ERROR on binding");
     
}
/******** recvmessage() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void recvmessage (int sock)
{
   /* The message will received from the network then we will 
      do soemthing to this message and send data to ROS or the network */
   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");
   //Prepare to publish by convert the buffer to a ros message 
   stringPub << buffer;
	/* do something when you receive a message */
   message.data = stringPub.str();
   ROS_INFO("Here is the message:");
}
