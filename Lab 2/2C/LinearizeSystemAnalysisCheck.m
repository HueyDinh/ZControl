% ReadTxt_MEM458_Lab2C_CCW_smooth.m
fileID = fopen("linearize_perturbation2.txt",'r');
formatSpec = '%d %d %f';
sizeA = [3 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
n=size(A);
t=A(1,1:n(2))*0.001;
x=A(2,1:n(2))*0.892*pi/180;
v=A(3,1:n(2))*1000*0.892*pi/180;
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

vel_equil = -0.31266*0.892*1000*pi/180;
input_perturbation = 25/255*100;

v_perturbation = v-(vel_equil);

delay = 3;
A = -0.62;
tau = 0.11;
curve_fit_eqn = @(t) A*(1-exp(-(t-delay)/tau)).*heaviside(t-delay);

figure;
plot(t,v_perturbation,'r-',"DisplayName","Arduino's Perturbation Output"); hold on;
plot(t,curve_fit_eqn(t),'b-',"LineWidth",2,"DisplayName",sprintf("Curve Fit line: \\omega = %.3f exp(-t/%.3f)",A, tau));
xlabel("Time (s)");
ylabel("Angular Velocity (rad/s)");
grid on;
grid minor;
legend(location = "best");
