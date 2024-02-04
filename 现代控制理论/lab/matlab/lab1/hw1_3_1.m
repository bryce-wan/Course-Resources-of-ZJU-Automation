%先把题目中的非单位负反馈模型化为单位负反馈
sys = tf([0,1,8,20],[1,6,8,0])
rlocus(sys);
hold on;
z = 0.44:0.01:0.6;
zwn = 1:1:20;
sgrid(z,zwn);
sgrid(0.565,zwn)
[k,pole] = rlocfind(sys);
A = k/2
SYS1 = tf([k,8*k,20*k],[1,4,0]);
SYS2 = tf([0,0.2],[1,2]);
SYS0 = feedback(SYS1,SYS2,-1);
SYS = zpk(SYS0)