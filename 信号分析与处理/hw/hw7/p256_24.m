clear; clc;
a=[1 3 3];
b=[1];
subplot(211);
impulse(b,a,5);
subplot(212);
step(b,a,5);