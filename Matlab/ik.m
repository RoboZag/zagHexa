x = 5;
y = 3;
Coxa = 12;
Femur = 35;
Tibia = 72;
Zoffset = 5;
%L1 = square root(x^2 + y^2)
L1 = sqrt(x^2+y^2)
%L1 = square root(Zoffset + (L1-coxa)^2)
L = sqrt(Zoffset + (L1-Coxa)^2)
%gama = arctan(x/y)    
gama = atan(x/y)    % angle between L & Y
%alpha1 = arccos(Zoffset/L)
alpha1 = acos(Zoffset/L)   %angle between L & X
%alpha2 = arccos((femur^2+L^2-tibia^2)/2*femur*L)
alpha2 = acos((Femur^2 + L^2 - Tibia^2)/2*Femur*L)  % angle between L&femur
alpha = alpha1 + alpha2
%beta = arccos((femur^2+tibia^2-L^2)/2*femur*tibia)
beta = acos((Femur^2 + Tibia^2 - L^2)/2*Femur*Tibia) % angle between femur&tibia
