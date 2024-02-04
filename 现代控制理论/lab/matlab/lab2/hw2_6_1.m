% 利用课堂知识直接编程法
syms k1 k2 s;
K = [k1,k2];
A = [-2,-3
    4,-9];

B = [3
    1];
I = [1,0
    0,1];
Acl = A-B*K;

det(s*I-Acl);
aim = s^2 + 2*s + 5;
[k1,k2] = solve(30+14*k2++24*k1 == 5,11+k2+3*k1 == 2,k1,k2);
k1 = vpa(k1,5)
k2 = vpa(k2,5)
% 利用matlab 函数 place 或 acker 方法)
K0 = place(A,B,[-1+j*2,-1-j*2])