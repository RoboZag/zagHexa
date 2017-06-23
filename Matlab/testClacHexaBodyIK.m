%% desired new position
PosX = 0; PosY = 0; PosZ = 0;
RotX = 0; RotY = 0; RotZ = 0;

%% set the dimensions of the leg links
%Note: the real values must be supplied here
Coxa = 12;
Femur = 35;
Tibia = 72;
BodySideLength = 80;
BodySideWidth = 80;
%% leg DH parameters
% Joint  theta_i     alpha_i     ai        di
% 1       theta_1     pi/2        Coxa      0
% 2       theta_2     0           Femur     0
% 3       theta_3     0           Tibia     0

% THETA D A ALPHA
L(1) = Link ([0, 0, Coxa,  pi/2]);
L(2) = Link ([0, 0, Femur, 0]);
L(3) = Link ([0, 0, Tibia, 0]);

%% create leg and clone it to create other legs
leg1 = SerialLink(L,'name', 'leg1', 'base', transl(BodySideLength,0,0)*trotz(pi),'offset',[30/180*pi, 0,0]);
leg2 = SerialLink(leg1, 'name', 'leg2', 'base', transl(0,0,0)*trotz(pi));
leg3 = SerialLink(leg1, 'name', 'leg3', 'base', transl(-BodySideLength,0,0)*trotz(pi));
leg6 = SerialLink(leg1, 'name', 'leg4', 'base', transl(BodySideLength,BodySideWidth,0));
leg5 = SerialLink(leg1, 'name', 'leg5', 'base', transl(0,BodySideWidth,0));
leg4 = SerialLink(leg1, 'name', 'leg6', 'base', transl(-BodySideLength,BodySideWidth,0));


%% ploting the leg at initial position (all angles are 60 deg.)
plotopt = {'noraise', 'nobase', 'noshadow', 'nowrist', 'nojaxes', 'delay', 0};

thisLegAngles = calibration(); %[0 0 0];
%leg.plot([0 0 0])
%leg.plot([1.0472,1.0472,1.0472], 'nobase', 'noshadow');

% create a fixed size axis for the robot, and set z positive downward
% draw the robot's body

patch([-BodySideLength BodySideLength BodySideLength -BodySideLength],... 
      [0  0              BodySideWidth BodySideWidth],... 
      [0 0 0 0],'FaceColor', 'y', 'FaceAlpha', 0.5);

leg1.plot(thisLegAngles(1:3), plotopt{:});
% set(gca, 'Zdir', 'reverse'); view(75, 40);

hold on
leg2.plot(thisLegAngles(4:6), plotopt{:});
leg3.plot(thisLegAngles(7:9), plotopt{:});
leg4.plot(thisLegAngles(10:12), plotopt{:});
leg5.plot(thisLegAngles(13:15), plotopt{:});
leg6.plot(thisLegAngles(16:18), plotopt{:});
hold off
set(gca, 'Zdir', 'reverse');
view(75, 40);
axis([-2*BodySideLength 2*BodySideLength -2*BodySideWidth 2.5*BodySideWidth -100 100]);

%% just move the body forward

for qq=1:40      % to move 8 steps
    % calculated new position based on the full body kinematics
    [legAngles]=clacHexaBodyIK(qq, PosY,PosZ, RotX, RotY, RotZ);
    thisLegAngles=legAngles(1:3)
    
    % ploting the leg at the new position
    leg1.plot(legAngles(1:3), 'nobase');
    % set(gca, 'Zdir', 'reverse');
    %view(75, 40);
    
    hold on
    leg2.plot(legAngles(4:6), 'nobase');
    leg3.plot(legAngles(7:9), 'nobase');
    leg4.plot(legAngles(10:12), 'nobase');
    leg5.plot(legAngles(13:15), 'nobase');
    leg6.plot(legAngles(16:18), 'nobase');
    hold off
end
