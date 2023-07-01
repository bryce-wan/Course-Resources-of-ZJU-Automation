clear;clc;
syms n Omega w0 a k

assume(n,'integer');
% define k = n/2
assume(k,'integer');
assume(Omega,'positive');

x1(n) = 0.5.^n;
x2(n) = (a.^n)*(1/2)*(1/(1i))*(exp(1i*n*w0)-exp(-1i*n*w0));
x3(n) = 0.5.^n;

X1 = symsum(x1(n)*exp(-1i*Omega*n),n,-3,inf);
X2 = symsum(x2(n)*exp(-1i*Omega*n),n,0,inf);
X3 = symsum(x3(2*k)*exp(-1i*Omega*2*k),k,0,inf);

fprintf("X1=\n");
pretty(X1);
fprintf("X2=\n");
pretty(X2);
fprintf("X3=\n");
pretty(X3);


