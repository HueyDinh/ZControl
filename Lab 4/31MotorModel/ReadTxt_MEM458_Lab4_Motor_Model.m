clc; clear; close all;
% ReadTxt_MEM458_Lab4_Motor_Model.m
fileID = fopen('file_MEM458_Lab4_Motor_Model.txt','r');
formatSpec = '%d %d %f';
sizeA = [3 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
n=size(A);
t=A(1,1:n(2))/1000;   % time,  in sec
x=A(2,1:n(2));     % displacement, in count
v=A(3,1:n(2))*1000;  % velocity, in count/sec
v_old = v;
v(2)=(v(1)+v(2))/2;
v(3)=(v(2)*2+v(3))/3;
v(4)=(v(3)*3+v(4))/4;
v(5)=(v(4)*4+v(5))/5;
v(6)=(v(5)*5+v(6))/6;
v(7)=(v(6)*6+v(7))/7;
v(8)=(v(7)*7+v(8))/8;
v(9)=(v(9)*8+v(9))/9;

for i=10:1:n(2)
    v(i)=(v(i-1)*9+v(i))/10;
end

% 1073 counts  is equivalent to   922 degrees
x=x*922/1073; % convert counts to degrees
v=v*922/1073;  % convert counts to degrees
v_old=v_old*922/1073;  % convert counts to degrees
figure(4)
plot(t,x,'r-')
title('Fig.4: displacement, deg (red) vs. time, sec')
grid on;
grid minor;
figure(5)
plot(t(1:100),x(1:100),'r-')
title('Fig.5: displacement, deg (red) vs. time, sec')
grid on;
grid minor;
figure(6)
plot(t,v_old,'b-')
title('Fig.6: velocity, deg/sec(blue) vs. time, sec')
grid on;
grid minor;

figure(7)
plot(t,v,'m-')
title('Fig.7: velocity, deg/sec(purple) vs. time, sec')
grid on;
grid minor;

figure(8)
plot(t(1:200),v(1:200),'m-')
title('Fig.8: velocity, deg/sec(purple) vs. time, sec')
grid on;
grid minor;
hold on;

w_ss = 242;
figure(8)
t2=linspace(0,0.79,100);
% typical dynamis model to match the experimenal data
v2=w_ss*(1-exp(-t2/0.08)); 
plot(t2,v2,'b-')
grid on;
grid minor;

