clear
clc
% DH-Paramters Using Peter Corke Robotics tool
% ZagHexa Dim 
coxa = 5;  femur = 10;  tibia = 13;
length = 0.2;  width = 0.1;
% Create Link using this code
% L = Link([Th  d     a     alpha])
L(1)= Link([0   5     coxa    pi/2]);
L(2)= Link([0   0     femur     0 ]);
L(3)= Link([0   0     tibia     0 ]);

% create the legs of the robot with a unique name
% and represent the position of each leg on the body
ZagHexa(1) = SerialLink(L,'name', 'leg1', 'base', transl(0, 0, 0)); 
ZagHexa(2) = SerialLink(L,'name', 'leg2', 'base', transl(-length/2, 0, 0));
ZagHexa(3) = SerialLink(L,'name', 'leg3', 'base', transl(-length, 0, 0));
ZagHexa(4) = SerialLink(L,'name', 'leg4', 'base', transl(0, -width, 0)*trotz(pi));
ZagHexa(5) = SerialLink(L,'name', 'leg5', 'base', transl(-length/2, -width, 0)*trotz(pi));
ZagHexa(6) = SerialLink(L,'name', 'leg6', 'base', transl(-length, -width, 0)*trotz(pi));

%clf;
%axis([-0.3 0.1 -0.2 0.2 -0.15 0.05]);
%set(gca,'Zdir', 'reverse')
%hold on
%patch([0 -length -length 0], [0 0 -width -width], [0 0 0 0], 'r')


%ZagHexa.fkine([ q1 ,q2 ,q3 ])

 while(1) 

  for i =3:-1:1
  q1 = 0 ; q2 = 0 ; q3 = -pi/2;
  for q2=0:pi/36:pi/6
    ZagHexa(i).plot([q1 ,q2 ,q3 ])
    hold on
  end
  for q1=0:pi/36:pi/6
    ZagHexa(i).plot([q1 ,q2 ,q3 ])
    hold on
  end
  for q2=pi/6:-pi/36:0
    ZagHexa(i).plot([q1 ,q2 ,q3])
    hold on
  end
  end
  
  for i =6:-1:4
  q1 = 0 ; q2 = 0 ; q3 = -pi/2;
  for q2=0:pi/36:pi/6
    ZagHexa(i).plot([q1 ,q2 ,q3 ])
    hold on
  end
  for q1=0:-pi/36:-pi/6
    ZagHexa(i).plot([q1 ,q2 ,q3 ])
    hold on
  end
  for q2=pi/6:-pi/36:0
    ZagHexa(i).plot([q1 ,q2 ,q3])
   hold on
  end
  end
  for i = 3:-1:1
    for q1=pi/6:-pi/36:0
    ZagHexa(i).plot([q1, q2, q3])
    hold on
    end
  end
  for i = 6:-1:4
    for q1=-pi/6:pi/36:0
    ZagHexa(i).plot([q1, q2, q3])
    hold on
    end
  end
 end
