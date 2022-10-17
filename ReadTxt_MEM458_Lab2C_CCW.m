% ReadTxt_MEM458_Lab2C_CCW.m
fileID = fopen('file_MEM458_Lab2C_CCW.txt','r');
formatSpec = '%d %d %f';
sizeA = [3 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
n=size(A);
t=A(1,1:n(2));
x=A(2,1:n(2));
v=A(3,1:n(2));
A2=[t;x];
figure(401)
plot(t/1000,x,'b-')
title('counts(blue) vs. time, sec')
grid on;
grid minor;

figure(402)
plot(t(1:100)/1000,x(1:100),'r-')
title('x(red) vs. time, sec')
grid on;
grid minor;

figure(403)
plot(t(1:100)/1000,v(1:100),'b-')
title('v(blue) vs. time, sec')
grid on;
grid minor;

