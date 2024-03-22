clc;clear;
% Define symbolic variables
syms theta1 theta2 theta3 theta4 theta5 theta6;
syms d1 d2 d4 d5 d6;
syms alpha1 alpha4 alpha5;
syms a2 a3;
syms px py pz; % End-effector position
syms roll pitch yaw; % End-effector orientation (in terms of roll, pitch, yaw angles)
syms nx ny nz ox oy oz ax ay az dx dy dz

% Define transformation matrices
T01 = dhTransform(theta1, d1, -90, 0);
T12 = dhTransform(theta2, d2, 0, a2);
T23 = dhTransform(theta3, 0, 0, a3);
T34 = dhTransform(theta4, d4, 90, 0);
T45 = dhTransform(theta5, d5, 90, 0);
T56 = dhTransform(theta6, d6, 0, 0);

T06 = [nx ox ax dx;
       ny oy ay dy;
       nz oz az dz;
       0  0  0  1];
% disp(T06)

% T15 = T12 * T23 * T34 * T45;
% T15_ = inv(T01) * T06 * inv(T56);
% disp(T15)
% disp(T15_)

% T16 = T12 * T23 * T34 * T45 * T56;
% T16_ = inv(T01) * T06;
% disp(simplify(T16))
% disp(simplify(T16_))

T15 = T12 * T23 * T34 * T45;
T15_ = inv(T01) * T06 *inv(T56);
disp(simplify(T15))
disp(simplify(T15_))

% T14 = T12 * T23 * T34;
% T14_ = inv(T01) * T06 *inv(T56) *inv(T45);
% disp(simplify(T14))
% disp(simplify(T14_))

solutions = solve([d2 + d4 - d6*cos(theta5) == dy*cos(theta1) - dx*sin(theta1), ... %T16 34
                   -cos(theta5) == ay*cos(theta1) - ax*sin(theta1)], ...% T16 33
                   [theta1, theta5], ReturnConditions=false);
disp(simplify(solutions.theta1))






% Function to calculate a DH transformation matrix
function T = dhTransform(theta, d, alpha, a)
    T = [cos(theta), -sin(theta) * cosd(alpha), sin(theta) * sind(alpha), a * cos(theta);
         sin(theta), cos(theta) * cosd(alpha), -cos(theta) * sind(alpha), a * sin(theta);
         0, sind(alpha), cosd(alpha), d;
         0, 0, 0, 1];
end
