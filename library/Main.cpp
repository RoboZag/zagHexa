#include <Walking_Patterns.h>
#include <ros/ros.h>
#include <std_msgs/String.h>

char data;
int mode = 1; //mode 1 for translation, mode 2 for tending, mode 3 for up and down
Walking_Patterns walking = Walking_Patterns()
void oncall(const std_msgs::String::ConstPtr& msg)
{
	if (data == '1')
	{
		if (mode == 1)
			walking.tripod_forward();
		if (mode == 2)
			walking.tilt_forward();
		if (mode == 3)
			walking.standup();
	}
	if (data == '2')
	{
		if (mode == 1)
			walking.tripod_left();
		if (mode == 2)
			walking.tilt_left();
		//if (mode == 3)
			//do something 
	}
	if (data == '3')
	{
		if (mode == 1)
			walking.tripod_backward();
		if (mode == 2)
			walking.tilt_backward();
		if (mode == 3)
			walking.sitdown();
	}
	if (data == '4')
	{
		if (mode == 1)
			walking.tripod_right();
		if (mode == 2)
			walking.tilt_right();
		//if (mode == 3)
			// do something
	}
	/*if (data == 'x')
	{
		// When x is call
	}
	if (data == 't')
	{
		// When t is call
	}*/
	if (data == 'c')
		mode++;
	if (data == 's')
		walking.reset_angles();
	if (mode > 3)
		mode = 1;
	ROS.INFO("data = [%s]", msg-> data.c_str());
}

void start()
{
	// set the angles to the refrance 
	walking.calibrate();
}

int main(int argc, char **argv)
{
	start();
	ros::init(argc, argv, "servo_joy");
	ros::NodeHandle servoHandler;
	ros::Subscriber sub = servoHandler.subscribe("move_direction", 1000, oncall);
	ros::spin();
	return 0;
}
