clear 
clc
% DH-Paramters Using Peter Corke Robotics toolbox
% ZagHexa Dim 
L1 = -5;  a1 = 5;  a2=10;  a3=13;

% Create Link using this code
% L   = Link ( [ Th  d    a   alph])

  L(1)= Link ( [0  L1    a1    pi/2]);

  L(2)= Link ( [0   0    a2     0]);
  
  L(3)= Link ( [0   0    a3     0 ]);
  
% set limits for joints
  L(1).qlim=[deg2rad(-90) deg2rad(90)];
  
  L(2).qlim=[deg2rad(0) deg2rad(90)];
  
  %L(3).qlim=[deg2rad(-80) deg2rad(120)];
  
  ZagHexa = SerialLink (L,'name','ZagHexa');
  
% initial position of robot
  %qready = [15 0 -18];
  %Td = transl([15 0 -18]);
  %q = ZagHexa.ikine(Td, qready,[1 1 1 0 0 0]);
  %ZagHexa.plot(q);
  while(1)
    for a=1:1:30
    % go to this position 
    Td = transl([15 0 -18+a])
    % IK to the robot
    q = ZagHexa.ikcon(Td);
  
    plot(ZagHexa,q);
     hold on
    end
  end
  
  