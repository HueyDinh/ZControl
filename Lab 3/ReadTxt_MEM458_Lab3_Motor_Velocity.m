% ReadTxt_MEM458_Lab3_Motor_Velocity.m
fileID = fopen('file_MEM458_Lab3_Motor_Velocity.txt','r');
formatSpec = '%d %d %f';
sizeA = [3 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
n=size(A);
t=A(1,1:n(2));
x=A(2,1:n(2));
v=A(3,1:n(2));
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
plot(t/1000,x,'r-')
title('counts(red) vs. time, sec')
grid on;
grid minor;
figure(502)
plot(t(1:100)/1000,x(1:100),'r-')
title('counts(red) vs. time, sec')
grid on;
grid minor;
figure(503)
plot(t/1000,v_old,'b-')
title('counts/time(blue) vs. time, sec')
grid on;
grid minor;

figure(510)
plot(t/1000,v,'m-')
title('counts/time(purple) vs. time, sec')
grid on;
grid minor;

