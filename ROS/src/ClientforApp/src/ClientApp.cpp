/*
  - Create ROS node 
  - Open socket 
  - Write to the socket that i want the index
  - Read the index string and save the value to buffer
  - Publish the value to ROS 
*/

/*
  Protocol:
  - Get the wanted mode from ROS by subscribing to /client_messages topic 
  - Send int to the server to choose the wanted mode of data sending
  - Server will select the mode
  - Receive the data from the server
*/

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>

#include <client_l.h>
#include <iostream>

client_l req;

using namespace std;


class mode{
  private:
      int modeofcalling;
  public:
      void callback(const std_msgs::Int16::ConstPtr& msg); // Set modeofcalling by the value from topic
      int getvalue();
};
void mode::callback(const std_msgs::Int16::ConstPtr& msg) {
    modeofcalling = msg->data;
}

int mode::getvalue()
{
   return modeofcalling;
}

int main(int argc, char *argv[]) {

    // Node
    ros::init(argc, argv, "Client_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(MESSAGE_FREQ); // set the rate as defined in the macro MESSAGE_FREQ
    std_msgs::String message;
    std::stringstream ss;
    ros::Publisher GA_pub = nh.advertise<std_msgs::String>("/Sensors_values", 1000);
    mode choice;
    ros::Subscriber client_sub = nh.subscribe("/Oreading", 100 , &mode::callback, &choice);


    // Socket
    int n,send_mode;
    char buffer[256] = { 0 };
    int sockfd = req.initiate_Client(argc, argv);

    // Read and Write into socket
    while(ros::ok()) 
    {
      //Write
      send_mode = choice.getvalue();
      n = write(sockfd,&send_mode,sizeof(int));
      if (n < 0) 
	  req.error("ERROR writing to socket");

      // Receve the data in buffer
      bzero(buffer,255);
      n = read(sockfd,buffer,255);
      if (n < 0)
          req.error("ERROR reading reply");
      cout<< buffer <<"\n";

      //Publish to ROS
      ss << buffer;
      message.data = ss.str();
      GA_pub.publish(message);
      ros::spinOnce();
   }
   return 0;
}
