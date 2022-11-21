% Filename: mem458Lab4CntrlDesign.m, which will call MotorPosCntrl.mdl for 
% simulation, and then call plot_A.m to plot the closed-loop position 
% control response
clear
ref_position = 180   % in degrees
%K=1   % Proportional controller gain = K
K=1
%Let the sampling period be T=0.01 seconds
Ts=0.01   % sampling period
% Consider the analog system to be controlled, Gp(s)=w_ss/(s*(tau*s+1)
% where the output of Gp(s) is the angular displacement of the DC motor in
% degree, and the input is PWM in duty cycle percentage with 100
% representing the full available 9V voltage
w_ss = 6.05
num = w_ss
den = [0.08 1  0]
[Ac,Bc,Cc,Dc]=tf2ss(num,den);

%and find G(z)=[A,B,C,D]

[A,B]=c2d(Ac,Bc,Ts)
C=Cc
D=Dc

A_cl=A-B*K*C
eAcl=eig(A_cl)
eAcl_mag=abs(eAcl)
eAcl_angle=angle(eAcl)
sigma = (1/Ts)*log(eAcl_mag(1))
w = (1/Ts)*eAcl_angle(1)
wn = sqrt(sigma^2 + w^2)
zeta = -sigma / wn

% Simulation 
sim_time=2,
sim_options = simset('SrcWorkspace', 'current','DstWorkspace', 'current');
open('MotorPosCntrl')  
sim('MotorPosCntrl', [0, sim_time], sim_options);        
run('plot_A')
