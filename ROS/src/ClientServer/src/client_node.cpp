#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int sockfd, portno, n;
struct sockaddr_in serv_addr;	// internet address
struct hostent *server;
char buffer[256];	


// system call fails 
void error(const char *msg)
{
    	perror(msg);
    	exit(0);
}

void callback(const std_msgs::String::ConstPtr& msg)
{
	/* do some thing when you receive a message */
	//ROS_INFO("I heard from ROS: [%s]", msg­>data.c_str()); 
	//Close the socket connection 
	close(sockfd);
}

void start(int argc, char *argv[])
{
	// Check the port number on which the server will accept connections
	if(argc < 3){
	std::cout<<stderr<<"usage "<<argv[0]<<" hostname port\n";
	exit(0);
	}
	//Convert the port number from a string of digits to an integer
	portno = atoi(argv[2]);
	//System call creates a new socket Internet
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET domain for any two hosts on the Internet
	if (sockfd < 0) 
        error("ERROR opening socket");
	//Take the name as an argument and returns a pointer to a hostent containing information about that host
	server = gethostbyname(argv[1]);
	if (server == NULL) {
        std::cout<<stderr<<"ERROR, no such host\n";
        exit(0);
   	}
	//Initializes the buffer to zeros
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;		//Code for the address family
	bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    	serv_addr.sin_port = htons(portno);	//Convert the port number to an internet format 
	//Establish a connection to the server
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        	error("ERROR connecting");
	
}

void send_data()
{
	//Send data 
    	std::cout<<("Please enter the message: ");
	//Message
    	bzero(buffer,256);
	//Read from the keyboard
    	fgets(buffer,255,stdin);
	//write to the socket
   	n = write(sockfd,buffer,strlen(buffer));
    	if (n < 0) 
         	error("ERROR writing to socket");
	
}

// If you want to receive from network
/*void read_data()
{
	//Empty the buffer and be ready to recieve  
    	bzero(buffer,256);
    	//Read from the socket
	n = read(sockfd,buffer,255);
    	if (n < 0) 
         	error("ERROR reading from socket");
	
	
}*/


int main(int argc, char *argv[])
{
	/* The client will send the data through the network and it will wait 
	   for a respone from the server through ROS or the network */
	ros::init(argc, argv, "Client");
	ros::NodeHandle clientHandle;
	ros::Subscriber sub = clientHandle.subscribe("Server_Clinet", 1000, callback);
	start(argc, argv);
	send_data();
	//Print the recieved message on the screen 
    	//printf("I heard from network:%s\n",buffer);
    	return 0;
}	

