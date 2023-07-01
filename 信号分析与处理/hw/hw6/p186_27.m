clear;clc;
syms n z a

x1=(a^n)*(-1)^n*heaviside(n);
x2=(2^(n-1)-(-2)^(n-1))*heaviside(n);

Fz1=ztrans(x1);
Fz2=ztrans(x2);

fprintf("Fz1=\n");
disp(Fz1);
fprintf("Fz2=\n");
disp(Fz2);