clear;clc;

n=-10:10;

f=5*discrete_dirac(n+4)+2*discrete_dirac(n+1)-4*discrete_dirac(n-1)+3*discrete_dirac(n-3);

stem(n,f);


