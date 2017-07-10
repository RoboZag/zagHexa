#!/usr/bin/env python 
# This will move channel 0 from min to max position repeatedly.
from __future__ import division
from std_msgs.msg import Int8
import rospy
import pygame

# Key mappings
PS3_AXIS_O = 2
PS3_AXIS_X = 2
PS3_AXIS_LEFT_VERTICAL = 1
PS3_AXIS_LEFT_HORIZONTAL = 0
PS3_AXIS_DPAD_UP = 2
PS3_AXIS_DPAD_RIGHT = 2
PS3_AXIS_DPAD_DOWN = 2
PS3_AXIS_DPAD_LEFT = 2

pygame.init()

# Wait for a joystick
while pygame.joystick.get_count() == 0:
    # print "waiting for joystick count = %i"
    pygame.joystick.get_count()
    pygame.joystick.quit()
    pygame.joystick.init()

j = pygame.joystick.Joystick(0)
j.init()
j.get_name()

def processcontrol(event):

    pub = rospy.Publisher('move_direction', Int8, queue_size = 10 )
    rospy.init_node('joy_servo', anonymous=True)
    rate = rospy.Rate(10)
    #while not rospy.is_shutdown():
    if event.type == pygame.JOYAXISMOTION:
        if event.axis == PS3_AXIS_LEFT_VERTICAL:
            rospy.loginfo('down')
            pub.publish(1)
        elif event.axis == PS3_AXIS_LEFT_HORIZONTAL:
            rospy.loginfo('left')
            pub.publish(2)
        elif event.axis == PS3_AXIS_O:
            rospy.loginfo('n')
            pub.publish(3)
        elif event.axis ==PS3_AXIS_X :
            rospy.loginfo('m')
            pub.publish(3)
        elif event.axis == PS3_AXIS_DPAD_DOWN :
            rospy.loginfo('k')
            pub.publish('r')
        elif event.axis ==PS3_AXIS_DPAD_LEFT :
            rospy.loginfo('g')
        rate.sleep()

while True:
    # read in joystick events
    #try:
    events = pygame.event.get()
        # and process them
    for event in events:
        processcontrol(event)
    #except roypy.ROSInterruptException:
        #rospy.loginfo(' Wait ')
        
