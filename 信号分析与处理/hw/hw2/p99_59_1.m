clear;clc;

syms t1 an bn n
T1 = 4; 
f = 1/T1; 
w1 = 2*pi*f;
range = [-T1/2,T1/2];
fun=heaviside(t1+1)-heaviside(t1-1);
an = 2/T1*int(fun*cos(n*w1*t1),t1,range);
bn = 2/T1*int(fun*sin(n*w1*t1),t1,range);
X=(an-bn*1i)/2;

% disp(an)
% disp(bn)
pretty(X)