k = 43.685;
f1 = conv([1,2],[1,4,5]);
f2 = [k,k];
sys = tf(f2,f1)  %只用开环传递函数即可
w = logspace(0,4,50);
bode(sys,w);
grid;
[Gm,Pm,Wcg,Wcp] = margin(sys)