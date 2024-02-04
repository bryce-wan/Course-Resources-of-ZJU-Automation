f = conv([1,1],conv([1,5],[1,-2]));
sys1 = tf([50],f);
sys2 = tf([1],[1]);
SYS = feedback(sys1,sys2,-1);
figure(1);
nyquist(sys1)
figure(2);
step(SYS)