% Filename: plot_A.m
% plot after running simulink file
figure(1)
subplot(1,2,1)
plot(t,yout(:,2),'m-', t,yout(:,1),'b-')
grid on
grid minor
title('displacement (deg) vs. time (sec)')
hold on

subplot(1,2,2)
plot(t,u,'b-')
grid on
grid minor
title('u (duty cycle)  vs. time (sec)')
hold on
