clear;clc;
syms w w0 t;
assume(w0,{'positive'})

f1=heaviside(w+w0)-heaviside(w-w0);
F1=ifourier(f1,t);

f2=dirac(w+w0)-dirac(w-w0);
F2=ifourier(f2,t);

f3=5*cos(2*w);
F3=ifourier(f3,t);

f4=(heaviside(w)-heaviside(w-1))*exp(-1i*w);
F4=ifourier(f4,t);

fprintf("F1 = %s\n",F1);
fprintf("F2 = %s\n",F2);
fprintf("F3 = %s\n",F3);
fprintf("F4 = %s",F4);

