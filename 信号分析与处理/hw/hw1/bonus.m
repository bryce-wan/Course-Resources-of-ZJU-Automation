clc;clear;

t=-1:0.01:2;
x=((t>0)-(t>1));
h=(-t+1).*(t>0 & t<=1);
y=conv(x,h);
y=y*0.01;
k=2*length(t)-1;
k3=linspace(2*t(1),2*t(end),k);
subplot(2,2,1)

plot(t,x);
title('x(t)')
xlabel('t')
ylabel('x(t)')

subplot(2,2,2)
plot(t,h)
title('h(t)')
xlabel('t')
ylabel('h(t)')

subplot(2,2,3)
plot(k3,y);
h=get(gca,'position');
h(3)=2.5*h(3);
set(gca,'position',h);
title('y(t)=x(t)*h(t)');
xlabel('t');
ylabel('y(t)');

