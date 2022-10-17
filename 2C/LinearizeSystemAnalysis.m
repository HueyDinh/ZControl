% ReadTxt_MEM458_Lab2C_CCW_smooth.m
fileID = fopen("linearize_perturbation.txt",'r');
formatSpec = '%d %d %f';
sizeA = [3 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
n=size(A);
t=A(1,1:n(2))*0.001;
x=A(2,1:n(2))*0.892;
v=A(3,1:n(2))*1000*0.892;
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

vel_equil = -0.3268*0.892*1000;
input_perturbation = 25/255*100;

v_perturbation = v-(vel_equil);

figure;
plot(t,v_perturbation,'r-')

log_fit = 
