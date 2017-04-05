# This will move channel 0 from min to max position repeatedly.
from __future__ import division
import time
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

def processControl(event):

    if event.type == pygame.JOYAXISMOTION:
# left stick
        if event.axis == PS3_AXIS_LEFT_VERTICAL:
        elif event.axis == PS3_AXIS_LEFT_HORIZONTAL:

while (True):
    time.sleep(0.1)
# read in joystick events
    events = pygame.event.get()

# and process them
    for event in events:
        processControl(event)
