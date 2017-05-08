clear
clc
% DH-Paramters Using Peter Corke Robotics toolbox
% ZagHexa Dim 
L1 = -5;  a1 = 5;  a2=10;  a3=13;

% Create Link using this code
% L   = Link([ Th  d    a   alph])
  L(1)= Link([0  L1    a1    pi/2]);
  L(2)= Link([0   0    a2     0]);
  L(3)= Link([0   0    a3     0 ]);
  
 ZagHexa = SerialLink (L,'name','ZagHexa');

 %ZagHexa.fkine([ q1 ,q2 ,q3 ])

  while(1)
  q1 = 0 ; q2 = 0 ; q3 = -pi/2;
  for q2=0:pi/36:pi/6
    ZagHexa.plot([q1 ,q2 ,q3 ])
    hold on
  end
  for q1=0:pi/36:pi/6
    ZagHexa.plot([q1 ,q2 ,q3 ])
    hold on
  end
  for q2=pi/6:-pi/36:0
  ZagHexa.plot([q1 ,q2 ,q3])
  hold on
  end
  for q1=pi/6:-pi/36:0
  ZagHexa.plot([q1, q2, q3])
  hold on
  end
  end

  