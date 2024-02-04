%先不妨让K=1
k=0.1;
sys1 = tf([1*k,6*k,13*k],[1,3,0]);
sys2 = tf([0,1],[1,1]);
sys = feedback(sys1,sys2,-1)
[y,t] = step(sys);
[Ymax,i] = max(y);
% 更改k的参数可以测得 k=0.2 时 Mp = 1.1768 ，k=0.1 时 Mp=1.0243
for k = 0.1:0.01:0.2
    sys1 = tf([1*k,6*k,13*k],[1,3,0]);
    sys2 = tf([0,1],[1,1]);
    sys = feedback(sys1,sys2,-1);
    [y,t] = step(sys);
    [Ymax,i] = max(y);
    if(abs(Ymax-1.0948) < 0.01) 
        break;
    end
end
disp(k)
disp(Ymax)
sys1 = tf([1*k,6*k,13*k],[1,3,0]);
sys2 = tf([0,1],[1,1]);
sys = feedback(sys1,sys2,-1)
SYS = zpk(sys)
[Z,P,K] = zpkdata(SYS,'v')
zeta = cos(atan(0.5925/0.5286))