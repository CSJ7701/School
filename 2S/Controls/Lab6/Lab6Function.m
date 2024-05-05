function [G_Comp, K, Ki] = Lab6Function(PhaseMargin, GainCrossFreq, G)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
figure(1)
bode(G); grid on;
title("Uncompensated Bode Plot")
axis([1,1000, -190,10])
G_info=allmargin(G);
gain_cross_freq=G_info.PMFrequency;
PM=G_info.PhaseMargin;

% Plot Design Point
axh = findall(gcf, 'type', 'axes');
DesignPointHeight=-180+PhaseMargin;
hold(axh(2),'on')
plot(axh(2),GainCrossFreq, DesignPointHeight, '^','LineWidth',1)

% Design Controller
sd=j*GainCrossFreq
G_sd=evalfr(G,sd);
theta_c=deg2rad(DesignPointHeight)-angle(G_sd);
theta_p=angle(sd);
theta_z=theta_c+theta_p;
alfa=GainCrossFreq/tan(theta_z);

Gc=tf([1 alfa],[1 0]);
Gc_at_sd=evalfr(Gc, sd);
G_at_sd=evalfr(G, sd);
K=1/(abs(Gc_at_sd) * abs(G_at_sd));
Ki=K*alfa;

PI=K*Gc;
G_Comp=PI*G;

% Plot Compensated Bode
figure(2)
bode(G_Comp); grid on;
title("Compensated Bode Plot")
% Plot Design Point
axh=findall(gcf, 'type', 'axes');
hold(axh(2), 'on');
plot(axh(2),GainCrossFreq, DesignPointHeight, '^', 'LineWidth',1);
end