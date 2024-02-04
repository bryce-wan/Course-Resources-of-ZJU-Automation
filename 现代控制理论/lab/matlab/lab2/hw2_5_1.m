NUM = [0.632];
DEN = [1,-1.368,0.568];
SYS = tf(NUM,DEN,-1)
t = 0:0.01:10;
f = square(2*pi*t);     %T = 2*pi/(2*pi) = 1
% plot(t,f);
dlsim(NUM,DEN,f)