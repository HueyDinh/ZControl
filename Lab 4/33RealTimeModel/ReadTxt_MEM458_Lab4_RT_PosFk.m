clc; clear; close all;
% ReadTxt_MEM458_Lab4_RT_PosFk.m
% fileID = fopen('file_MEM458_Lab4_RT_PosFk.txt','r');
fileID = fopen('file_MEM458_Lab4_RT_PosFk.txt','r');
formatSpec = '%d %d %f %f';
sizeA = [4 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
n=size(A);
t=A(1,1:n(2));
x=A(2,1:n(2));
duty=A(3,1:n(2));
deg=A(4,1:n(2));

figure(721)
plot(t/1000000,duty,'r.')
title('duty cycle vs. time, sec')
grid on;
grid minor;

figure(722)
plot(t(1:100)/1000000,duty(1:100),'r.')
title('duty cycle vs. time, sec')
grid on;
grid minor;

figure(723)
plot(t/1000000,deg,'b.')
title('displacement, deg vs. time, sec')
grid on;
grid minor;

figure(724)
plot(t(1:100)/1000000,deg(1:100),'b.')
title('displacement, deg vs. time, sec')
grid on;
grid minor;


