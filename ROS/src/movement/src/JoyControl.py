#!/usr/bin/env python3
# This will move channel 0 from min to max position repeatedly.
from __future__ import division
from std_msgs.msg import Int8, String
import rospy
import pygame
import serial 

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

class stru:
	def__init__(self):
		self.mode = A
		self.direction = 0

#Special message type 
Mod_and_direc = stru()

#Start the communication with Arduino 
serial_comm_port = serial.Serial('/dev/ttyACM0',9600)

#Start pygame 
pygame.init()

#Start ROS Node
pub = rospy.Publisher('move_direction', Int8, queue_size = 10 )
rospy.init_node('joy_servo', anonymous=True)

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
        pub.publish(0)
		
		#Send through serial 
		Mod_and_direc.direction = 0
		serial_comm_port.write(Mod_and_direc)
		
    elif event.type == pygame.JOYAXISMOTION and event.value < 0 and event.axis == 1:
        #print("AXIS_LEFT_VERTICAL U")
		
		#Publish in ROS 
        rospy.loginfo('Up')
        pub.publish(1)
		
		#Send through serial 
		Mod_and_direc.direction = 1
		serial_comm_port.write(Mod_and_direc)
    elif event.type == pygame.JOYAXISMOTION and event.value == 1 and event.axis == 0:
        #print("AXIS_LEFT_HORIZONTAL R")
        
		#Publish in ROS 
		rospy.loginfo('Right')
        pub.publish(2)
		
		#Send through serial 
		Mod_and_direc.direction = 2
		serial_comm_port.write(Mod_and_direc)
    elif event.type == pygame.JOYAXISMOTION and event.value == 1 and event.axis == 1:
        #print("AXIS_LEFT_VERTICAL D")
        
		#Publish in ROS 
		rospy.loginfo('Down')
        pub.publish(3)
		
		#Send through serial 
		Mod_and_direc.direction = 3
		serial_comm_port.write(Mod_and_direc)
    if event.type == pygame.JOYBUTTONDOWN:
        if event.button == PS3_BUTTON_X:
            #print("BUTTON_X")
            rospy.loginfo('X')
            pub.publish(4)
			Mod_and_direc.mode = X
			serial_comm_port.write(Mod_and_direc)
        elif event.button == PS3_BUTTON_Y:
            #print("BUTTON_Y")
            rospy.loginfo('Y')
            pub.publish(5)
			Mod_and_direc.mode = Y
			serial_comm_port.write(Mod_and_direc)
        elif event.button ==PS3_BUTTON_B:
            #print("BUTTON_B")
            rospy.loginfo('B')
            pub.publish(6)
			Mod_and_direc.mode = B
			serial_comm_port.write(Mod_and_direc)
        elif event.button == PS3_BUTTON_A:
            #print("BUTTON_A")
            rospy.loginfo('A')
            pub.publish(7)
			Mod_and_direc.mode = A
			serial_comm_port.write(Mod_and_direc)
        elif event.button == PS3_BUTTON_RB :
            #print("BUTTON_RB")
            rospy.loginfo('RB')
            pub.publish(8)
			Mod_and_direc.mode = R
			serial_comm_port.write(Mod_and_direc)
        elif event.button == PS3_BUTTON_RT :
            #print("BUTTON_RT")
            rospy.loginfo('RT')
            pub.publish(9)
			Mod_and_direc.mode = M
			serial_comm_port.write(Mod_and_direc)
        elif event.button == PS3_BUTTON_LB :
            #print("BUTTON_LB")
            rospy.loginfo('LB')
            pub.publish(10)
			Mod_and_direc.mode = L
			serial_comm_port.write(Mod_and_direc)
        elif event.button == PS3_BUTTON_LT :
            #print("BUTTON_LT")
            rospy.loginfo('LT')
            pub.publish(11)
			Mod_and_direc.mode = N
			serial_comm_port.write(Mod_and_direc)
        elif event.button == PS3_BUTTON_Back :
            #print("BUTTON_Back")
            rospy.loginfo('Back')
            pub.publish(12)
			Mod_and_direc.mode = K
			serial_comm_port.write(Mod_and_direc)
        elif event.button == PS3_BUTTON_Start:
            #print("BUTTON_Start")
            rospy.loginfo('Start')
            pub.publish(13)
			Mod_and_direc.mode = S
			serial_comm_port.write(Mod_and_direc)
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


