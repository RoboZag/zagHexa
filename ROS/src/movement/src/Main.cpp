#include <std_msgs/Int8.h>
#include <movement/vfloat.h>
#include <ros/ros.h>
#include <BodyIK.h>


BodyIk Hexa;

void oncall(const std_msgs::Int8 msg)
{
	// Waiting for the walking pattern to be modified
}

int main(int argc, char** argv)
{
	movement::vfloat message;

	Hexa.Coxa = 12.0;
	Hexa.Femur = 35.0;
	Hexa.Tibia = 72.0;
	Hexa.BodySideLength = 80.0;

	ros::init(argc, argv, "servo_joy");
	ros::NodeHandle servoHandler;
	ros::Publisher  pub = servoHandler.advertise<movement::vfloat>("/angles1", 1000);
	ros::Subscriber sub = servoHandler.subscribe("move_direction", 1000, oncall);
	ros::Rate loop_rate(10); 

	Hexa.calibration();
	// Hexa.clacHexaBodyIK(PosX, PosY, PosZ, RotX, RotY, RotZ);
	Hexa.clacHexaBodyIK(5, 5, 5,5,5,5);
	/*
		0 RightFront
		1 RightMiddle
		2 RightRear
		3 LeftFront
		4 LeftMiddle
		5 LeftRear

	*/
	while(ros::ok())
	{
		for(int i=0; i < 6; i++)
		{	
			message.data = Hexa.correct_angle(i);
			pub.publish(message);
		}
		ros::spinOnce();
		loop_rate.sleep(); 
		
	}
	/*
	// For Testing the output value 
	for (int j = 0; j < 6; j++)
	{
	for (vec_float::iterator i = Hexa.IKangles[j].begin(); i != Hexa.IKangles[j].end(); i++)
	{
	std::cout << *(i) << "\n";
	}

	}



	int x;
	std::cin >> x;*/
	return 0;

}
