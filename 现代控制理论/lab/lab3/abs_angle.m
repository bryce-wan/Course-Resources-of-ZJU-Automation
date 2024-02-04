clc;clear;

array = [1.256 12.56 62.8];
for a = array
    %a_ = 1/(0.5*a*1i+1);
    a_ = -10/((a*1i+1)*(0.1*1i*a+1));

    %20*log10(abs(1/(a*x*1i+1)))
    %20*log10(angle(1/(a*x*1i+1)))
    %20*log10(abs(-10/((a*x*1i+1)*(b*x*1i+1))))
    %20*log10(angle(-10/((a*x*1i+1)*(b*x*1i+1))))

    20*log10(abs(a_));
    angle(a_)/pi*180;
end

