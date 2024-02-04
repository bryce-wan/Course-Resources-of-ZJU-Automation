syms w a;
w = 6;
figure(1);
for a = 0.1:0.1:1
    sys = tf([0,0,w*w],[1,2*a*w,w*w]);
    step(sys);
    hold on;
end
a = 2;
sys = tf([0,0,w*w],[1,2*a*w,w*w]);
step(sys);
title('w = 6,a取不同值');
legend('0.1','0.2','0.3','0.4','0.5','0.6','0.7','0.8','0.9','1.0','2.0');

figure(2);

a = 0.7;
for w = 2:2:12
    sys = tf([0,0,w*w],[1,2*a*w,w*w]);
    step(sys);
    hold on;
end
legend('2','4','6','8','10','12');
title('a = 0.7,w取不同值');
