
%% Open Loop Transfer Function
s=zpk('s'); % Set 's' = laplace variable
Motor=tf(2.083,[1, 1.71]); % Find the transfer function for motor block
G=(Motor*0.1)/s; % Finds G, theta/Ea

%% Open Loop Unity Step Response
OLoopUnitStep=step(G); % Finds the Open Loop Unity Step Response 
plot(OLoopUnitStep)
xlabel('Time');
ylabel('Angle');
title('Open Loop Unity Step Response')
%% Unit Step Response
syms 's'
G=0.2083/(s+1.71);
ilaplace(G)
%% Verifying the original transfer function
syms 't'
laplace(0.2083*exp(-1.71*t))*(0.1/s);
