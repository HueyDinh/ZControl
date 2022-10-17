% ReadTxt_MEM458_Lab2C_CCW_smooth.m
fileID = fopen('file_MEM458_Lab2C_CCW.txt','r');
formatSpec = '%d %d %f';
sizeA = [3 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
n=size(A);
t=A(1,1:n(2))*0.001;
x=A(2,1:n(2))*0.0161;
v=A(3,1:n(2))*16.1;
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
 
figure(501)
plot(t,x,'r-')
title('displacement(red) vs. time, sec')
grid on;
grid minor;
figure(502)
plot(t(1:100),x(1:100),'r-')
title('displacement(red) vs. time, sec')
grid on;
grid minor;

figure(503)
plot(t(1:100),v_old(1:100),'b-')
title('velocity(blue) vs. time, sec')
grid on;
grid minor;
 
figure(510)
plot(t(1:100),v(1:100),'m-')
title('velocity(purple) vs. time, sec')
grid on;
grid minor;
hold on;

t2=linspace(0,0.39,100);
v2=-4.988*(1-exp(-t2/0.08));
figure(510)
plot(t2,v2,'b-')
grid on;
grid minor;
