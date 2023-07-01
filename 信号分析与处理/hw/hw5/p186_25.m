clear;clc;

syms t n k Omega A B

fs=1000;
Ts=1/fs;

xa(t)=A*cos(200*pi*t)+B*cos(500*pi*t);
x(n)=xa(n*Ts);

N=20;

X=(1/N)*symsum(x(n)*exp(-1i*(2*pi/N)*k*n),n,0,N-1);
disp(X);
% pretty(X);
