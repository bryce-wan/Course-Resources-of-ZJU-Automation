clear;clc;
syms w t w0
H=fourier(1/(pi*t));
X=fourier(cos(w0*t),t,w);
Y=X*H;
y=ifourier(Y);
disp(y)
