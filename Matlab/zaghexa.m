s = 'Rz(q1).Rx(q2).Ty(L1).Rx(q3).Tz(L2)';
% set the dimensions of the two leg links
femur = 0.1;  tebia = 0.1;
% applying DH convention
%                    theta   d    a     alpha  
links(1) = Link([    0       0    0      pi/2 ], 'standard');
links(2) = Link([    0       0    femur   0   ], 'standard');
links(3) = Link([    0       0   -tebia   0   ], 'standard');
% create a single leg representation
leg = SerialLink(links, 'name', 'leg', 'offset', [pi/2   0  -pi/2]);
% define the key parameters of the gait trajectory, walking in the x-direction
xf = 50; xb = -xf;     % forward and backward limits for foot on ground
y = 50;                % distance of foot from body along y-axis
zu = 20; zd = 50;      % height of foot when up and down
% define the path taken by the foot
path = [xf y zd; xb y zd; xb y zu; xf y zu; xf y zd] * 0.001;
path = [path; path];
% time of the path is 6 seconds 
%(5 seconds for walking and 1 second for reset)
tpath = [5 0.2 0.2 0.2 0.2 0.2 ]';
tpath = [1; tpath; tpath];
% parameters of mstraj() function 
% mstraj(path, max speed in xyz directions, duration of path, ..
%.. initial coordinates, acceleration time, smoothness of robot)
p = mstraj(path, [], tpath, path(1,:), 0.01, 0);
pcycle = p(100:500,:);
% applying inverse kinematics
qcycle = leg.ikine( transl(p), [], [1 1 1 0 0 0] );
% dimensions of the robot's body
W = 0.1; L = 0.2;
plotopt = {'noraise', 'nobase', 'noshadow', 'nowrist', 'nojaxes', 'delay', 0};
% create the legs of the robot with a unique name
% and represent the position of each leg on the body
legs(1) = SerialLink(leg, 'name', 'leg1');
legs(2) = SerialLink(leg, 'name', 'leg2', 'base', transl(-L/2, 0, 0));
legs(3) = SerialLink(leg, 'name', 'leg3', 'base', transl(-L, 0, 0));
legs(4) = SerialLink(leg, 'name', 'leg4', 'base', transl(0, -W, 0)*trotz(pi));
legs(5) = SerialLink(leg, 'name', 'leg5', 'base', transl(-L/2, -W, 0)*trotz(pi));
legs(6) = SerialLink(leg, 'name', 'leg6', 'base', transl(-L, -W, 0)*trotz(pi));
% create a fixed size axis for the robot, and set z positive downward
clf;
axis([-0.3 0.1 -0.2 0.2 -0.15 0.05]);
set(gca,'Zdir', 'reverse')
hold on
% draw the robot's body
patch([0 -L -L 0], [0 0 -W -W], [0 0 0 0], 'FaceColor', 'r', 'FaceAlpha', 0.5)
% initiate the legs in the axes
for i=1:6
    legs(i).plot(qcycle(1,:), plotopt{:});
end
hold off
% walking the robot
k = 1;
while 1
    legs(1).animate( gait(qcycle, k, 0,   0));
    legs(2).animate( gait(qcycle, k, 100, 0));
    legs(3).animate( gait(qcycle, k, 200, 0));
    legs(4).animate( gait(qcycle, k, 300, 1));
    legs(5).animate( gait(qcycle, k, 400, 1));
    legs(6).animate( gait(qcycle, k, 500, 1));
    drawnow
    k = k+1;
end
