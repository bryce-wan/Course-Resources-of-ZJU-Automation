clc;clear;

syms t;

y=(t^3+t+2).*dirac(t-1);

res=int(y,t,-inf,inf);

res

