A = [-2.8 -1.4 0 0 
      1.4 0 0 0 
      -1.8 -0.3 -1.4 -0.6
      0 0 0.6 0];
B = [1
    0
    1
    0];
C = [0 0 0 1];
D = [0];
SYS_ss = ss(A,B,C,D)
[num,den] = ss2tf(A,B,C,D);
SYS_tf = tf(num,den)
[Z,P,K] = ss2zp(A,B,C,D);
SYS_zpk = zpk(Z,P,K)
P = pole(SYS_ss)