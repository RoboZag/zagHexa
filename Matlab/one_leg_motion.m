% determine the sequence of the leg
s = 'Rz(q1).Rx(q2).Ty(L1).Rx(q3).Tz(L2)';
% applying dh convention
dh = DHFactor(s);
dh.tool;
dh.command('leg');

% set the dimensions of the two links of the leg
L1 = 0.1; L2 = 0.1;
leg = eval( dh.command('leg') );
leg;

% forward kinematics at the zero postion
transl( leg.fkine([0,0,0]) );

%ploting the leg with this specifications
leg.plot([0,0,0], 'nobase', 'noshadow');
set(gca, 'Zdir', 'reverse');
view(137,48);

%testing the angles of q1 & q2 &q3
transl( leg.fkine([0.2,0,0]) );
transl( leg.fkine([0,0.2,0]) );
transl( leg.fkine([0,0,0.2]) );

% define the key parameters of the gait trajectory, walking in the x-direction
xf = 50; xb = -xf;           % forward and backward limits for foot on ground
y = 50;                      % distance of foot from body along y-axis
zu = 20; zd = 50;            % height of foot when up and down

% define the path taken by the foot
path = [xf y zd; xb y zd; xb y zu; xf y zu; xf y zd] * 1e-3;
% parameters of mstraj() function 
% mstraj(path, max speed in xyz directions, duration of path, ..
%.. initial coordinates, acceleration time, smoothness of robot)
p = mstraj(path, [], [0, 3, 0.25, 0.5, 0.25]', path(1,:), 0.01, 0);
% applying inverse kinematics
qcycle = leg.ikine( transl(p), [], [1 1 1 0 0 0] );
% to run simulation continueously
% but you can make a time to run it by (pause(msec))
leg.plot(qcycle, 'loop') 