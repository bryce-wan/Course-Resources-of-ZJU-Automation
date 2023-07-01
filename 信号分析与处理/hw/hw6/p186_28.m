clear;clc;
syms n z;

Xz1=(8*z-19)/(z^2-5*z+6);
Xz2=z*(2*z^2-11*z+12)/((z-1)*(z-2)^2);
Xz3=(1-2*z^(-1))/(z^(-1)-2);

x1=iztrans(Xz1);
x2=iztrans(Xz2);
x3=iztrans(Xz3);

fprintf("x1=\n");
disp(x1);
fprintf("x2=\n");
disp(x2);
fprintf("x3=\n");
disp(x3);
