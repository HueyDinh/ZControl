clc;clear;close all;
% ReadTxt_MEM458_Lab3_Motor_Velocity.m
fileID = fopen('lab4dataExp.txt','r');
formatSpec = '%ld %d';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
n=size(A);
t=A(1,1:n(2))*64/16e6;
x=A(2,1:n(2));
v = zeros(length(t),1);
v(2:end) = diff(x)./diff(t);
v_smooth = movmean(v,20);
countToRPMConv = 0.892/360*60;
countToRadConv = 0.892*pi/180;

figure;
plot(t,x,'r-')
title('counts(red) vs. time, sec')
xlabel("Time (s)")
ylabel("Encoder Count");
grid on;
grid minor;

figure;
plot(t(1:100),x(1:100),'r-')
title('counts(red) vs. time, sec - Zoomed')
xlabel("Time (s)")
ylabel("Encoder Count");
grid on;
grid minor;

figure;
plot(t,x*countToRadConv,'r-')
title('Angular displacement (red) vs. time, sec')
xlabel("Time (s)")
ylabel("\theta (rad)");
grid on;
grid minor;

figure;
plot(t,v,'b-')
title('counts/time(blue) vs. time, sec')
xlabel("Time (s)")
ylabel("Encoder Count Rate of Change (\mu s^{-1})");
grid on;
grid minor;

figure;
plot(t,v_smooth,'m-')
title('counts/time(purple) vs. time, sec - Post-Processed')
xlabel("Time (s)")
ylabel("Encoder Count Rate of Change (\mu s^{-1})");
grid on;
grid minor;

figure;
plot(t,v_smooth*countToRPMConv,'m-')
title('Angular velocity (purple) vs. time, sec - Post-Processed')
xlabel("Time (s)")
ylabel("\omega (RPM)");
grid on;
grid minor;
