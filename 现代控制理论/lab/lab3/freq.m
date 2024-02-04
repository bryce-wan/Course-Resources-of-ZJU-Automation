clc;clear;

w = linspace(0,5,200);
b = [1];
a = [0.5 1];
H = freqs(b,a,w);
subplot(2,1,1);
plot(w,abs(H));
set(gca,'xtick',[0 1 2 3 4 5]);
set(gca,'ytick',[0 0.4 0.707 1]);
xlabel('\omega');
ylabel('|H(j\omega)|');
title('幅频响应曲线')
subplot(2,1,2);
plot(w,angle(H));

set(gca,'xtick',[0 1 2 3 4 5]);
xlabel('\omega');
ylabel('\phi(\omega)')
title('相频响应曲线')
