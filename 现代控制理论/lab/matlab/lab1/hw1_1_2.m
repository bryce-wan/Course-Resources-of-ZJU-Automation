sys1 = tf([0,1],[1,1]);
sys2 = tf([0,1],[1,4]);
sys3 = tf([0,1],[1,2]);
sys4 = tf([0,1],[1,5]);
sys5 = tf([0,1],[1,3]);
input = tf([1],[1]);
output = tf([1],[1]);
% syms s
% sys1 = 1/(s+1);
% sys2 = 1/(s+4);
% sys3 = 1/(s+2);
% sys4 = 1/(s+5);
% sys5 = 1/(s+3);
% sys6 = 1;

sys=append(sys1,sys2,sys3,sys4,sys5,input,output);
Q = [1,6,4,-5;
    2,5,0,0;
    3,1,-2,0;
    4,3,0,0;
    5,3,0,0
    7,5,0,0];
sysc=connect(sys,Q,6,7);
SYS=tf(sysc)
