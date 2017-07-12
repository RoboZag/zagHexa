#!/usr/bin/env python3
# This will move channel 0 from min to max position repeatedly.
from __future__ import division
from std_msgs.msg import Int8, String
import rospy
import pygame
#import serial 

# Key mappings
PS3_BUTTON_A = 0
PS3_BUTTON_B = 1
PS3_BUTTON_X = 2
PS3_BUTTON_Y = 3
PS3_BUTTON_LB = 4
PS3_BUTTON_RB = 5
PS3_BUTTON_LT = 6
PS3_BUTTON_RT = 7
PS3_BUTTON_Back = 8
PS3_BUTTON_Start = 9


#Start the communication with Arduino 
#serial_comm_port = serial.Serial('/dev/ttyACM0',9600)

#Start pygame 
pygame.init()

#Start ROS Node
rospy.init_node('Joystick_node', anonymous=True)
pub = rospy.Publisher('Joystick_', Int8, queue_size = 10 )

# Wait for a joystick
while pygame.joystick.get_count() == 0:
    print ("waiting for joystick")
    rospy.Rate(1).sleep()    
    pygame.joystick.get_count()
    pygame.joystick.quit()
    pygame.joystick.init()
    
#Start joystick connection 
j = pygame.joystick.Joystick(0)
j.init()
print (j.get_name(), " is connected")

#joystick information
joystick_count = pygame.joystick.get_count()
print("joystick_count")
print(joystick_count)
print("--------------")
 
numaxes = j.get_numaxes()
print("numaxes")
print(numaxes)
print("--------------")
 
numbuttons = j.get_numbuttons()
print("numbuttons")
print(numbuttons)
print("--------------")
 
def buttonscontrol(event):

#Mapinng butttons    
    if event.type == pygame.JOYAXISMOTION and event.value < 0 and event.axis == 0:
        #print("AXIS_LEFT_HORIZONTAL L")
	    #Publish in ROS 
        rospy.loginfo('left')
        pub.publish('L')
		
		#Send through serial 
		#Mode = 'L'		
    elif event.type == pygame.JOYAXISMOTION and event.value < 0 and event.axis == 1:
        #print("AXIS_LEFT_VERTICAL U")
		
		#Publish in ROS 
        rospy.loginfo('Up')
        pub.publish('U')
		
		#Send through serial 
		#Mode = 'U'
    elif event.type == pygame.JOYAXISMOTION and event.value == 1 and event.axis == 0:
        #print("AXIS_LEFT_HORIZONTAL R")
        
		#Publish in ROS 
		rospy.loginfo('Right')
        pub.publish('R')
		
		#Send through serial 
		#Mode = 'R'
    elif event.type == pygame.JOYAXISMOTION and event.value == 1 and event.axis == 1:
        #print("AXIS_LEFT_VERTICAL D")
		#Publish in ROS 
		rospy.loginfo('Down')
        pub.publish('D')
		
		#Send through serial 
		#Mode = 'D'
    if event.type == pygame.JOYBUTTONDOWN:
        if event.button == PS3_BUTTON_X:
            #print("BUTTON_X")
            rospy.loginfo('X')
            pub.publish('X')
			#Mode = 'X'
        elif event.button == PS3_BUTTON_Y:
            #print("BUTTON_Y")
            rospy.loginfo('Y')
            pub.publish('Y')
			#Mode = 'Y'
        elif event.button ==PS3_BUTTON_B:
            #print("BUTTON_B")
            rospy.loginfo('B')
            pub.publish('B')
			#Mode= 'B'
        elif event.button == PS3_BUTTON_A:
            #print("BUTTON_A")
            rospy.loginfo('A')
            pub.publish('A')
			#Mode= 'A'
        elif event.button == PS3_BUTTON_RB :
            #print("BUTTON_RB")
            rospy.loginfo('RB')
            pub.publish('M')
			#Mode = 'M'
        elif event.button == PS3_BUTTON_RT :
            #print("BUTTON_RT")
            rospy.loginfo('RT')
            pub.publish('N')
			#Mode = 'N'
        elif event.button == PS3_BUTTON_LB :
            #print("BUTTON_LB")
            rospy.loginfo('LB')
            pub.publish('O')
			#Mode = 'P'
        elif event.button == PS3_BUTTON_LT :
            #print("BUTTON_LT")
            rospy.loginfo('LT')
            pub.publish('P')
			#Mode = 'P'
        elif event.button == PS3_BUTTON_Back :
            #print("BUTTON_Back")
            rospy.loginfo('Back')
            pub.publish('K')
			#Mode = 'K'
        elif event.button == PS3_BUTTON_Start:
            #print("BUTTON_Start")
            rospy.loginfo('Start')
            pub.publish('S')
			#Mode = 'S'
        #serial_comm_port.write(Mode)
        rospy.Rate(10).sleep()
        

#Announcment for start 
rospy.loginfo('Begin')
pub.publish(0000)

while True:

    #read in joystick events
    events = pygame.event.get()
   
    # and process them
    for event in events:
        buttonscontrol(event)


