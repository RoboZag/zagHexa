function [initialAngles] = calibration()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%- initial feet positions
%- Standup function in our robot code 
%- Set all coxa angles to 60 deg in each leg to get the current value
%  of the postion for x,y,z 
%- Note that the zero postion in the simulation is at 30 deg
%  so we will have to add 30 deg to all coxa angles 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%leg 1
Coxa_1 = -pi/2;
Femur_1 = -pi;
Tibia_1 = -pi/2;
%leg 2
Coxa_2 = -2*pi/3;
Femur_2 = -pi;
Tibia_2 = -pi/2;
%leg 3
Coxa_3 = -5*pi/6;
Femur_3 = -pi;
Tibia_3 = -pi/2;
%leg 4
Coxa_4 = -pi/2;
Femur_4 = -pi;
Tibia_4 = -pi/2;
%leg 5 
Coxa_5 = -2*pi/3;
Femur_5 = -pi;
Tibia_5 = -pi/2;
%leg 6
Coxa_6 = -5*pi/6;
Femur_6 = -pi;
Tibia_6 = -pi/2;

initialAngles = [Coxa_1, Femur_1, Tibia_1, ...
                 Coxa_2, Femur_2, Tibia_2, ...
                 Coxa_3, Femur_3, Tibia_3, ...
                 Coxa_4, Femur_4, Tibia_4, ...
                 Coxa_5, Femur_5, Tibia_5, ...
                 Coxa_6, Femur_6, Tibia_6];
end