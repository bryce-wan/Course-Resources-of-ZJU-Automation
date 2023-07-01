close all; clear; clc;
syms t w x1 x2 x3 x4 t2

t2=t^2;

x1=exp(-1*1i*t)*dirac(t-2);
F1=fourier(x1);

%将sgn(x)利用阶跃函数进行转化
x2=heaviside(t-sqrt(2))+heaviside(-t-sqrt(2))-(heaviside(t+sqrt(2))-heaviside(t-sqrt(2)));
F2=fourier(x2);

x3=exp(-5*t)*heaviside(t+2);
F3=fourier(x3);

x4=heaviside(t-1);
F4=fourier(x4);

disp(F1)
disp(F2)
disp(F3)
disp(F4)
