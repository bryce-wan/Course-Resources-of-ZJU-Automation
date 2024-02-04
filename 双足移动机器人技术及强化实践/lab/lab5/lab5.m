clc,clear;
syms    nx  ox  ax  dx ...
        ny  oy  ay  dy ...
        nz  oz  az  dz;
th_0 = [0 -pi/2 0 pi/2 pi/2 0];
th= [0 0 0 0 0 0];
X_lists = [0.117 -0.066 0.3 0.42 0.32];
Y_lists = [0.334 0.339 0.25 0 -0.25];
Z_lists = [0.499 0.444 0.26 0.36 0.16];
r_lists = [-2.019 -2.618 -2.64 3.14 3];
p_lists = [-0.058 -0.524 0.59 1 0.265];
y_lists = [-2.190 -3.141 -2.35 -1.57 -0.84];

i = 1;
r = r_lists(i);
p = p_lists(i);
y = y_lists(i);
X = X_lists(i);
Y = Y_lists(i);
Z = Z_lists(i);

T_ = [X;Y;Z];
red = [0 0 0 1]; 
R = [1 0 0; 0 cos(r) -sin(r); 0 sin(r) cos(r)] * [cos(p) 0 sin(p); 0 1 0; -sin(p) 0 cos(p)] * [cos(y) -sin(y) 0; sin(y) cos(y) 0; 0 0 1];
T = [R T_];
T = [T;red];
disp(T)

nx = T(1,1);ox = T(1,2);ax = T(1,3);dx = T(1,4);
ny = T(2,1);oy = T(2,2);ay = T(2,3);dy = T(2,4);
nz = T(3,1);oz = T(3,2);az = T(3,3);dz = T(3,4);

a = [0 0.185 0.170 0 0 0];
d = [0.230 -0.054 0 0.077 0.077 0.0855];
A = dy - d(6)*ay;
B = dx - d(6)*ax;
C = d(2)+d(4);
th(1) = atan2(A,B)+atan2(C,sqrt(B^2+A^2-C^2))-pi;  %+-atan2(C,sqrt(B^2+A^2-C^2))
% th(1) = atan(A/B)+atan(C/sqrt(B^2+A^2-C^2));  %+-atan2(C,sqrt(B^2+A^2-C^2))

th(5) = -acos(ax*sin(th(1))-ay*cos(th(1)));      %+-acos(

A = ny*cos(th(1))-nx*sin(th(1));
B = oy*cos(th(1))-ox*sin(th(1));
C = -sin(th(5));

% th(6) = atan2(A,B)+atan2(C,0);
th(6) = atan(A/B)+atan(C/0);


M = dx*cos(th(1)) + dy*sin(th(1)) - ay*d(6)*sin(th(1)) - ax*d(6)*cos(th(1)) - d(5)*ny*sin(th(1))*sin(th(6)) - d(5)*ox*cos(th(1))*cos(th(6)) - d(5)*nx*cos(th(1))*sin(th(6)) - d(5)*oy*cos(th(6))*sin(th(1));
N = d(1) - dz + az*d(6) + d(5)*oz*cos(th(6)) + d(5)*nz*sin(th(6));
th(3) = -acos((M^2+N^2-a(2)^2-a(3)^2)/(2*a(2)*a(3)));    %+-acos(

s2 = ((a(3)*cos(th(3))+a(2))*N-a(3)*sin(th(3))*M)/(a(2)^2+a(3)^2+2*a(2)*a(3)*cos(th(3)));
c2 = (M+a(3)*sin(th(3))*s2)/(a(3)*cos(th(3))+a(2));

th(2) = -atan2(s2,c2);
% th(2) = -atan(s2/c2);

th(4) = asin((oz*sin(th(6)) - nz*cos(th(6)))/cos(th(5))) -th(2)-th(3);
th = (th - th_0)/pi*180;
fprintf("theta_1 = %.2f\n",th(1));
fprintf("theta_2 = %.2f\n",th(2));
fprintf("theta_3 = %.2f\n",th(3));
fprintf("theta_4 = %.2f\n",th(4));
fprintf("theta_5 = %.2f\n",th(5));
fprintf("theta_6 = %.2f\n",th(6));