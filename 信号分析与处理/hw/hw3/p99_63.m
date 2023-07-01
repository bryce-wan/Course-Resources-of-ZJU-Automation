clear; clc;
syms t w tau;

f1=sin(3*pi*(t-2))/(pi*(t-2));
F1=fourier(f1,t,w);

subplot(221);
fplot(w,abs(F1));
axis([-2*pi 2*pi 0 3])
xlabel('w')
ylabel('Magnitude')
title('|X(w)|')
grid on;

subplot(222);
fplot(w,angle(F1));
axis([-2*pi 2*pi -3 3])
xlabel('w')
ylabel('Phi')
title('Phi')
grid on;

f2=sin(pi*t)/(pi*t);
F21=fourier(f2,t,w);
F22=fourier(f2,t,w);
subs(F21,w,tau);
subs(F22,w,w-tau);
F2=(1/(2*pi))*int(subs(F21,w,tau)*subs(F22,w,w-tau),tau,-inf,inf);

subplot(223);
fplot(w,abs(F2));
axis([-2*pi 2*pi 0 3])
xlabel('w')
ylabel('Magnitude')
title('|X(w)|')
grid on;

subplot(224);
fplot(w,angle(F2));
axis([-2*pi 2*pi -3 3])
xlabel('w')
ylabel('Phi')
title('Phi')
grid on;

