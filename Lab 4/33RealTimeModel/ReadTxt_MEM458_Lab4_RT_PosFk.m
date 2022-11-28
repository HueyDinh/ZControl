clc; clear; close all;
% ReadTxt_MEM458_Lab4_RT_PosFk.m
% fileID = fopen('file_MEM458_Lab4_RT_PosFk055.txt','r');
fileID = fopen('file_MEM458_Lab4_RT_PosFk1.txt','r');
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
title('Duty Cycle vs. Time (s)')
grid on; grid minor;

figure(722)
plot(t(1:100)/1000000,duty(1:100),'r.')
title('Duty Cycle vs. Time (s) - Zoomed')
grid on; grid minor;

figure(723)
plot(t/1000000,deg,'b.')
title("Displacement (deg) vs. Time (s)")
grid on; grid minor;

figure(724)
plot(t(1:100)/1000000,deg(1:100),'b.')
title("Displacement (deg) vs. Time (s) - Zoomed")
grid on; grid minor;


