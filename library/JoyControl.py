# This will move channel 0 from min to max position repeatedly.
from __future__ import division
from std_msgs.msg impot String
import rospy
import pygame

# Key mappings
PS3_AXIS_O = 17
PS3_AXIS_X = 18
PS3_AXIS_LEFT_VERTICAL = 1
PS3_AXIS_LEFT_HORIZONTAL = 0
PS3_AXIS_DPAD_UP = 8
PS3_AXIS_DPAD_RIGHT = 9
PS3_AXIS_DPAD_DOWN = 10
PS3_AXIS_DPAD_LEFT = 11

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

    pub = rospy.Publisher('move_direction', String, queue_size = 10 )
    rospy.init_node('joy_servo', anonymous=True)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        if event.type == pygame.JOYAXISMOTION:
            if event.axis == PS3_AXIS_LEFT_VERTICAL:
                rospy.loginfo('l')
                pub.publisher('l')
            elif event.axis == PS3_AXIS_LEFT_HORIZONTAL:
                rospy.loginfo('l')
                pub.publisher('l')
            rate.sleep()

if __name__ = '__main__':
    # read in joystick events
    try:
        events = pygame.event.get()
        # and process them
        for event in events:
            processcontrol(event)
    except roypy.ROSInterruptException:
            pass
        
