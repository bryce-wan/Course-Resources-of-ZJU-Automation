% 书上的方法
A = [1,0,0
    0,2,1
    0,0,2];

B = [1
    0
    1];

C = [1,1,0];

syms s l1 l2 l3
I = [1,0,0
    0,1,0
    0,0,1];
% 求目标特征方程系数
aim = conv([1,3],conv([1,4],[1,5]))
% 翻转一下，让常数系数在前
aim = fliplr(aim)
L = [l1
    l2
    l3];

Aol = A-L*C;

% 合并同类项
origin = collect(det(s*I-Aol),s)
% 提取系数
f1 = coeffs(origin,s)
[l1,l2,l3] = solve(f1==aim)

%matlab 函数 estim 方法)
sys = ss(A,B,C,[0]);
SYS = estim(sys,[120;-103;210]);
SYS = zpk(SYS)