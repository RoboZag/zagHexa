clear
clc
BodySideLength = 45;
Coxa = 12;
Femur = 35; 
Tibia = 72;
PosX = 1;
PosY = 1;
PosZ = 8;
RotX = 3;
RotY = 1;
RotZ = 6;

BodyCenterOffset1 = BodySideLength/2;
BodyCenterOffset2 = sqrt(BodySideLength^2 - BodyCenterOffset1^2);

%Body center offset X
BodyCenterOffsetX_1 = BodyCenterOffset1;
BodyCenterOffsetX_2 = BodySideLength;
BodyCenterOffsetX_3 = BodyCenterOffset1;
BodyCenterOffsetX_4 = -BodyCenterOffset1;
BodyCenterOffsetX_5 = -BodySideLength;
BodyCenterOffsetX_6 = -BodyCenterOffset1;

%Body center offset Y
BodyCenterOffsetY_1 = BodyCenterOffset2;
BodyCenterOffsetY_2 = 0;
BodyCenterOffsetY_3 = -BodyCenterOffset2;
BodyCenterOffsetY_4 = -BodyCenterOffset2;
BodyCenterOffsetY_5 = 0;
BodyCenterOffsetY_6 = BodyCenterOffset2;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%- initial feet positions
%- Standup function in our robot code 
%- Set all angles to 60 deg in each leg to get the current value
%  of the postion for x,y,z 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%leg 1
feetposX_1 = cos((60/180)*pi)*(Coxa + Femur);
feetposY_1 = sin((60/180)*pi)*(Coxa + Femur);
feetposZ_1 = Tibia;
%leg 2
feetposX_2 = Coxa + Femur;
feetposY_2 = 0;
feetposZ_2 = Tibia;
%leg 3
feetposX_3 = cos((60/180)*pi)*(Coxa + Femur);
feetposY_3 = sin((-60/180)*pi)*(Coxa + Femur);
feetposZ_3 = Tibia;
%leg 4
feetposX_4 = -cos(60/180*pi)*(Coxa + Femur);
feetposY_4 = sin(-60/180*pi)*(Coxa + Femur);
feetposZ_4 = Tibia;
%leg 5 
feetposX_5 = -(Coxa + Femur);
feetposY_5 = 0;
feetposZ_5 = Tibia;
%leg 6
feetposX_6 = -cos(60/180*pi)*(Coxa + Femur);
feetposY_6 = sin(60/180*pi)*(Coxa + Femur);
feetposZ_6 = Tibia;

%Rotation angles 
CrotX = cos(RotX * pi/180);
SrotX = sin(RotX * pi/180);
CrotY = cos(RotY * pi/180);
SrotY = sin(RotY * pi/180);
CrotZ = cos(RotZ * pi/180);
SrotZ = sin(RotZ * pi/180);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% - We want to go to PosX, Posy, PosZ
% - Then we calculate the total distance from the center of the body 
%   to the new PosX, PosY, PosZ for each
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Body IK
%leg 1
    TotalY_1 = feetposY_1 + BodyCenterOffsetY_1 + PosY;
    TotalX_1 = feetposX_1 + BodyCenterOffsetX_1 + PosX;
    BodyIKX_1 = TotalX_1*CrotY*CrotZ-TotalY_1*CrotY*SrotZ+feetposZ_1*SrotY - TotalX_1;
    BodyIKY_1 =(TotalX_1*CrotX*SrotZ+TotalX_1*CrotZ*SrotY*SrotX+TotalY_1*CrotZ*CrotX- ...
                TotalY_1*SrotZ*SrotY*SrotX-feetposZ_1*CrotY*SrotX)-TotalY_1;
    BodyIKZ_1 = (TotalX_1*SrotZ*SrotX - TotalX_1*CrotZ*CrotX*SrotY + TotalY_1*CrotZ*SrotX + ...
                 TotalY_1*CrotX*SrotZ*SrotY + feetposZ_1*CrotY*CrotX) - feetposZ_1;
    %leg 2
    TotalY_2 = feetposY_2 + BodyCenterOffsetY_2 + PosY;
    TotalX_2 = feetposX_2 + BodyCenterOffsetX_2 + PosX;
    BodyIKX_2 = TotalX_2*CrotY*CrotZ-TotalY_2*CrotY*SrotZ+feetposZ_2*SrotY - TotalX_2;
    BodyIKY_2 =(TotalX_2*CrotX*SrotZ+TotalX_2*CrotZ*SrotY*SrotX+TotalY_2*CrotZ*CrotX- ...
                TotalY_2*SrotZ*SrotY*SrotX-feetposZ_2*CrotY*SrotX)-TotalY_2;
    BodyIKZ_2 = (TotalX_2*SrotZ*SrotX - TotalX_2*CrotZ*CrotX*SrotY + TotalY_2*CrotZ*SrotX + ...
                 TotalY_2*CrotX*SrotZ*SrotY + feetposZ_2*CrotY*CrotX) - feetposZ_2;
    
    %leg 3
    TotalY_3 = feetposY_3 + BodyCenterOffsetY_3 + PosY;
    TotalX_3 = feetposX_3 + BodyCenterOffsetX_3 + PosX;
    BodyIKX_3 = TotalX_3*CrotY*CrotZ-TotalY_3*CrotY*SrotZ+feetposZ_3*SrotY - TotalX_3;
    BodyIKY_3 =(TotalX_3*CrotX*SrotZ+TotalX_3*CrotZ*SrotY*SrotX+TotalY_3*CrotZ*CrotX- ...
                TotalY_3*SrotZ*SrotY*SrotX-feetposZ_3*CrotY*SrotX)-TotalY_3;
    BodyIKZ_3 = (TotalX_3*SrotZ*SrotX - TotalX_3*CrotZ*CrotX*SrotY + TotalY_3*CrotZ*SrotX + ...
                 TotalY_3*CrotX*SrotZ*SrotY + feetposZ_3*CrotY*CrotX) - feetposZ_3;
    %leg 4
    TotalY_4 = feetposY_4 + BodyCenterOffsetY_4 + PosY;
    TotalX_4 = feetposX_4 + BodyCenterOffsetX_4 + PosX;
    BodyIKX_4 = TotalX_4*CrotY*CrotZ-TotalY_4*CrotY*SrotZ+feetposZ_4*SrotY - TotalX_4;
    BodyIKY_4 =(TotalX_4*CrotX*SrotZ+TotalX_4*CrotZ*SrotY*SrotX+TotalY_4*CrotZ*CrotX- ...
                TotalY_4*SrotZ*SrotY*SrotX-feetposZ_4*CrotY*SrotX)-TotalY_4;
    BodyIKZ_4 = (TotalX_4*SrotZ*SrotX - TotalX_4*CrotZ*CrotX*SrotY + TotalY_4*CrotZ*SrotX + ...
                 TotalY_4*CrotX*SrotZ*SrotY + feetposZ_4*CrotY*CrotX) - feetposZ_4;
    %leg 5
    TotalY_5 = feetposY_5 + BodyCenterOffsetY_5 + PosY;
    TotalX_5 = feetposX_5 + BodyCenterOffsetX_5 + PosX;
    BodyIKX_5 = TotalX_5*CrotY*CrotZ-TotalY_5*CrotY*SrotZ+feetposZ_5*SrotY - TotalX_5;
    BodyIKY_5 =(TotalX_5*CrotX*SrotZ+TotalX_5*CrotZ*SrotY*SrotX+TotalY_5*CrotZ*CrotX- ...
                TotalY_5*SrotZ*SrotY*SrotX-feetposZ_5*CrotY*SrotX)-TotalY_5;
    BodyIKZ_5 = (TotalX_5*SrotZ*SrotX - TotalX_5*CrotZ*CrotX*SrotY + TotalY_5*CrotZ*SrotX + ...
                 TotalY_5*CrotX*SrotZ*SrotY + feetposZ_5*CrotY*CrotX) - feetposZ_5;

    %leg 6
    TotalY_6 = feetposY_6 + BodyCenterOffsetY_6 + PosY;
    TotalX_6 = feetposX_6 + BodyCenterOffsetX_6 + PosX;
    BodyIKX_6 = TotalX_6*CrotY*CrotZ-TotalY_6*CrotY*SrotZ+feetposZ_6*SrotY - TotalX_6;
    BodyIKY_6 =(TotalX_6*CrotX*SrotZ+TotalX_6*CrotZ*SrotY*SrotX+TotalY_6*CrotZ*CrotX- ...
                TotalY_6*SrotZ*SrotY*SrotX-feetposZ_6*CrotY*SrotX)-TotalY_6;
    BodyIKZ_6 = (TotalX_6*SrotZ*SrotX - TotalX_6*CrotZ*CrotX*SrotY + TotalY_6*CrotZ*SrotX + ...
                 TotalY_6*CrotX*SrotZ*SrotY + feetposZ_6*CrotY*CrotX) - feetposZ_6;
    
    %leg IK
    %leg 1
    NewPosX_1 = feetposX_1 + PosX + BodyIKX_1;
    NewPosY_1 = feetposY_1 + PosY + BodyIKY_1;
    NewPosZ_1 = feetposZ_1 + PosZ + BodyIKZ_1;
    TranformX_1 = NewPosX_1 * cos(30*pi/180) - NewPosY_1 * sin(30*pi/180);
    TranformY_1 = NewPosX_1 * sin(30*pi/180) + NewPosY_1 * cos(30*pi/180);
    CoxaFeetDist_1 = sqrt(NewPosX_1^2 + NewPosY_1^2);
    IKSW_1 = sqrt((CoxaFeetDist_1 - Coxa )^2 + NewPosZ_1^2);
    IKA1_1 = atan((CoxaFeetDist_1 - Coxa)/NewPosZ_1);
    IKA2_1 = acos((Tibia^2 - Femur^2 - IKSW_1^2)/(-2 * IKSW_1 *Femur));
    TAngle_1 = acos((IKSW_1^2 - Tibia^2 - Femur^2)/(-2 * Femur *Tibia));
    IKTibiaAngle_1 = 90 - TAngle_1 * 180/pi;
    IKFemurAngle_1 = (IKA1_1 + IKA2_1) * 180/pi - 90 ;
    IKCoxaAngle_1 = atan2(TranformX_1, TranformY_1) * 180/pi;


    %leg 2
    NewPosX_2 = feetposX_2 + PosX + BodyIKX_2;
    NewPosY_2 = feetposY_2 + PosY + BodyIKY_2;
    NewPosZ_2 = feetposZ_2 + PosZ + BodyIKZ_2;
    TranformX_2 = NewPosX_2 * cos(90*pi/180) - NewPosY_2 * sin(90*pi/180);
    TranformY_2 = NewPosX_2 * sin(90*pi/180) + NewPosY_2 * cos(90*pi/180);
    CoxaFeetDist_2 = sqrt(NewPosX_2^2 + NewPosY_2^2);
    IKSW_2 = sqrt((CoxaFeetDist_2 - Coxa )^2 + NewPosZ_2^2);
    IKA1_2 = atan((CoxaFeetDist_2 - Coxa)/NewPosZ_2);
    IKA2_2 = acos((Tibia^2 - Femur^2 - IKSW_2^2)/(-2 * IKSW_2 *Femur));
    TAngle_2 = acos((IKSW_2^2 - Tibia^2 - Femur^2)/(-2 * Femur *Tibia));
    IKTibiaAngle_2 = 90 - TAngle_2 * 180/pi;
    IKFemurAngle_2 = (IKA1_2 + IKA2_2) * 180/pi - 90;
    IKCoxaAngle_2 = 90 - atan2(TranformY_2, TranformX_2) * 180/pi;
    
    %leg 3
    NewPosX_3 = feetposX_3 + PosX + BodyIKX_3;
    NewPosY_3 = feetposY_3 + PosY + BodyIKY_3;
    NewPosZ_3 = feetposZ_3 + PosZ + BodyIKZ_3;
    TranformX_3 = NewPosX_3 * cos(150*pi/180) - NewPosY_3 * sin(150*pi/180);
    TranformY_3 = NewPosX_3 * sin(150*pi/180) + NewPosY_3 * cos(150*pi/180);
    CoxaFeetDist_3 = sqrt(NewPosX_3^2 + NewPosY_3^2);
    IKSW_3 = sqrt((CoxaFeetDist_3 - Coxa )^2 + NewPosZ_3^2);
    IKA1_3 = atan((CoxaFeetDist_3 - Coxa)/NewPosZ_3);
    IKA2_3 = acos((Tibia^2 - Femur^2 - IKSW_3^2)/(-2 * IKSW_3 *Femur));
    TAngle_3 = acos((IKSW_3^2 - Tibia^2 - Femur^2)/(-2 * Femur *Tibia));
    IKTibiaAngle_3 = 90 - TAngle_3 * 180/pi;
    IKFemurAngle_3 =(IKA1_3 + IKA2_3) * 180/pi - 90;
    IKCoxaAngle_3 = 90 - atan2(TranformY_3, TranformX_3) * 180/pi ;

    %leg 4
    NewPosX_4 = feetposX_4 + PosX + BodyIKX_4;
    NewPosY_4 = feetposY_4 + PosY + BodyIKY_4;
    NewPosZ_4 = feetposZ_4 + PosZ + BodyIKZ_4;
    TranformX_4 = NewPosX_4 * cos(210*pi/180) - NewPosY_4 * sin(210*pi/180);
    TranformY_4 = NewPosX_4 * sin(210*pi/180) + NewPosY_4 * cos(210*pi/180);
    CoxaFeetDist_4 = sqrt(NewPosX_4^2 + NewPosY_4^2);
    IKSW_4 = sqrt((CoxaFeetDist_4 - Coxa )^2 + NewPosZ_4^2);
    IKA1_4 = atan((CoxaFeetDist_4 - Coxa)/NewPosZ_4);
    IKA2_4 = acos((Tibia^2 - Femur^2 - IKSW_4^2)/(-2 * IKSW_4 *Femur));
    TAngle_4 = acos((IKSW_4^2 - Tibia^2 - Femur^2)/(-2 * Femur *Tibia));
    IKTibiaAngle_4 = 90 - TAngle_4 * 180/pi;
    IKFemurAngle_4 = (IKA1_4 + IKA2_4) * 180/pi - 90;
    IKCoxaAngle_4 = 90 - atan2(TranformY_4, TranformX_4) * 180/pi ;
    
    %leg 5
    NewPosX_5 = feetposX_5 + PosX + BodyIKX_5;
    NewPosY_5 = feetposY_5 + PosY + BodyIKY_5;
    NewPosZ_5 = feetposZ_5 + PosZ + BodyIKZ_5;
    TranformX_5 = NewPosX_5 * cos(270*pi/180) - NewPosY_5 * sin(270*pi/180);
    TranformY_5 = NewPosX_5 * sin(270*pi/180) + NewPosY_5 * cos(270*pi/180);
    CoxaFeetDist_5 = sqrt(NewPosX_5^2 + NewPosY_5^2);
    IKSW_5 = sqrt((CoxaFeetDist_5 - Coxa )^2 + NewPosZ_5^2);
    IKA1_5 = atan((CoxaFeetDist_5 - Coxa)/NewPosZ_5);
    IKA2_5 = acos((Tibia^2 - Femur^2 - IKSW_5^2)/(-2 * IKSW_5 *Femur));
    TAngle_5 = acos((IKSW_5^2 - Tibia^2 - Femur^2)/(-2 * Femur *Tibia));
    IKTibiaAngle_5 = 90 - TAngle_5 * 180/pi;
    IKFemurAngle_5 = (IKA1_5 + IKA2_5) * 180/pi - 90;
    IKCoxaAngle_5 = 90 - atan2(TranformY_5, TranformX_5) * 180/pi ;
    
    %leg 6
    NewPosX_6 = feetposX_6 + PosX + BodyIKX_6;
    NewPosY_6 = feetposY_6 + PosY + BodyIKY_6;
    NewPosZ_6 = feetposZ_6 + PosZ + BodyIKZ_6;
    TranformX_6 = NewPosX_6 * cos(330*pi/180) - NewPosY_6 * sin(330*pi/180);
    TranformY_6 = NewPosX_6 * sin(330*pi/180) + NewPosY_6 * cos(330*pi/180);
    CoxaFeetDist_6 = sqrt(NewPosX_6^2 + NewPosY_6^2);
    IKSW_6 = sqrt((CoxaFeetDist_6 - Coxa )^2 + NewPosZ_6^2);
    IKA1_6 = atan((CoxaFeetDist_6 - Coxa)/NewPosZ_6);
    IKA2_6 = acos((Tibia^2 - Femur^2 - IKSW_6^2)/(-2 * IKSW_6 *Femur));
    TAngle_6 = acos((IKSW_6^2 - Tibia^2 - Femur^2)/(-2 * Femur *Tibia));
    IKTibiaAngle_6 = 90 - TAngle_6 * 180/pi;
    IKFemurAngle_6 = (IKA1_6 + IKA2_6) * 180/pi - 90;
    IKCoxaAngle_6 = 90 - atan2(TranformY_6, TranformX_6) * 180/pi;
    
    %servo angles
%leg 1 
CoxaAngle_1 = IKCoxaAngle_1 
FemurAngle_1 = IKFemurAngle_1
TibiaAngle_1 = IKTibiaAngle_1

%leg 2
CoxaAngle_2 = IKCoxaAngle_2
FemurAngle_2 = IKFemurAngle_2
TibiaAngle_2 = IKTibiaAngle_2

%leg 3
CoxaAngle_3 = IKCoxaAngle_3 
FemurAngle_3 = IKFemurAngle_3
TibiaAngle_3 = IKTibiaAngle_3

%leg 4
CoxaAngle_4 = IKCoxaAngle_4 
FemurAngle_4 = IKFemurAngle_4
TibiaAngle_4 = IKTibiaAngle_4

%leg 5
CoxaAngle_5 = IKCoxaAngle_5 
FemurAngle_5 = IKFemurAngle_5
TibiaAngle_5 = IKTibiaAngle_5
    
%leg 6
CoxaAngle_6 = IKCoxaAngle_6 
FemurAngle_6 = IKFemurAngle_6
TibiaAngle_6 = IKTibiaAngle_6

