clear;clc;

syms t1 an bn n
assume(n,{'positive','integer'})
T1 = 2; 
f = 1/T1; 
m = 2*pi*f;
range = [0,T1/2];
fun=sin(m*t1);
an = 2/T1*int(fun*cos(n*m*t1),t1,range);
bn = 2/T1*int(fun*sin(n*m*t1),t1,range);
X=(an-bn*1i)/2;

% disp(an)
% disp(bn)
pretty(X)