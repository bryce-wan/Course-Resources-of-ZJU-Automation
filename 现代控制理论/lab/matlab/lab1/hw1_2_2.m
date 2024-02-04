% 上升时间，超调量，峰值时间，稳态时间
sys = tf([0,0,1],[1,1,1]);
[y,t] = step(sys);
[Ymax,k] = max(y);
Tp = t(k)     %峰值时间

C = dcgain(sys); %求终值
ov = (Ymax-C)/C %超调量

n = 1;
while y(n)<0.9*C
    n = n+1;
end
Tr = t(n) %上升时间

% 稳定时间采用公式法，取5%
wn = 1;
a = 0.5; %阻尼比
Ts = 3/(wn*a) %调节时间/稳态时间
step(sys)