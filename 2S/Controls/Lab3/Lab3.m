%% LAB 3: Standard 2nd Order System Identification
disp('Automatic Control Systems (1331)')
disp('Christian Johnson & Riley Thorburn')
disp('Dr. Emami')
disp(date())

 %% Part A
L=(47*10^(-3));
C=(0.22*10^(-6));
R=500;


Tftop=[1/(L*C)];
s=zpk('s');
Tfbot=(s^2+(R/L)*s+(1/(C*L)));

Tf=Tftop/Tfbot; 
figure(1); 
step(Tf)
grid on;
figure(2);
bode(Tf);
grid on; 
% Part D

% The issue with the step response graph is that it is underdamped. You can
% solve this by adding lossy elements into the circuit. 

%% Effect of Damping Ratio & Natural Frequency of the Pole Locations



[poles, ~]=pzmap(Tf);

figure (3);
grid on;
zeta=0:0.25:1;
 Labels = '\Zeta=' + string(zeta);
for i = 1:length(zeta)
    Wn=8400;    
    Tftop=(Wn^2);
    Tfbot=(s^2+(2*zeta(i)*Wn)*s+(Wn^2));
    Tf(i)=Tftop/Tfbot;
    hold on
    pzmap(Tf(i));
   
    legend(Labels); 
    
    
end
hold off

figure(4); 
Wn=7000:500:10000;
zeta=.54
 Labels = '\Wn=' + string(Wn);
 hold on;
for i=1:length(Wn)

    Tftop=(Wn(i)^2);
    Tfbot=(s^2+(2*zeta*Wn(i))*s+(Wn(i)^2));
    Tf=Tftop/Tfbot;
 
    pzmap(Tf)
    legend(Labels); 
    
end
hold off
    
% Analysis for Part B (part b and c)

% The effect of damping ratio on location of poles: as damping ratio gets
% larger, the pole's real and complex values get larger. The poles are
% increasing at a decreasing rate. 

%The effect of natural frequency on location of poles: As natural frequency
%increases, the pole's real and complex values are approaching zero. 

%%  Part C: Effect of Pole Location on Step and Frequency Response

figure (5);
grid on;
zeta=0:0.25:1.5;
 Labels = '\Zeta=' + string(zeta);
for i = 1:length(zeta)
    Wn=8400;    
    Tftop=(Wn^2);
    Tfbot=(s^2+(2*zeta(i)*Wn)*s+(Wn^2));
    Tf(i)=Tftop/Tfbot;
    hold on
    step(Tf(i),0.0025);
   
    legend(Labels); 
    
    
end
hold off
% As damping ratio increases, the system goes from undamped to overdamped.
% The Overshoot percentage starts to decrease and the settling time
% decreases up to the point that zeta=1 and then it starts to increase
% again.
figure (6);
grid on;
zeta=0:0.25:1.5;
 Labels = '\Zeta=' + string(zeta);
for i = 1:length(zeta)
    Wn=8400;    
    Tftop=(Wn^2);
    Tfbot=(s^2+(2*zeta(i)*Wn)*s+(Wn^2));
    Tf(i)=Tftop/Tfbot;
    hold on
  bode(Tf(i));
   
    legend(Labels); 
    
    
end
hold off

% Damping ratio on frequency response: As damping ratio increases, there is
% a decrease in the maximum magnitude. The real component of the pole
% increase. This will smooth the phase response and prevent the vertical
% discontuinity when zeta=0; 
%%
figure(7); 
Wn=7000:500:10000;
zeta=.54
 Labels = '\Wn=' + string(Wn);
 hold on;
for i=1:length(Wn)

    Tftop=(Wn(i)^2);
    Tfbot=(s^2+(2*zeta*Wn(i))*s+(Wn(i)^2));
    Tf=Tftop/Tfbot;
 
   step(Tf)
    legend(Labels); 
    
end
hold off
%Effect of natural frequencies on step responses: As you increase the
%natural frequency there is a linear delay of the maximum amplitude in the
%step response. All of the responses are underdamped. 
figure(8); 
Wn=7000:500:10000;
zeta=.54
 Labels = '\Wn=' + string(Wn);
 hold on;
for i=1:length(Wn)

    Tftop=(Wn(i)^2);
    Tfbot=(s^2+(2*zeta*Wn(i))*s+(Wn(i)^2));
    Tf=Tftop/Tfbot;
 
    bode(Tf)
    legend(Labels); 
    
end
hold off

%  Effect of natural frequency on frequency response: At low frequencies,
%  all of the responses have the same amplitude. At high frequencies an
%  increase in wn causes a subsequent increase in amplitude. For Phase, the
%  responses are all close to zero for low frequencies and as frequency
%  increases the phase starts to deviate 

%% Part C part e

L=(47*10^(-3));
C=(0.22*10^(-6));
s=tf('s');

figure(9);

zeta=0:0.25:1.5;
hold on;
for i = 1:length(zeta)
    R(i)=(2*zeta(i)*L)*(1/sqrt(L*C));
    Tftop=(1/(L*C));
    Tfbot(i)=(s^2+(R(i)/L)*s+(1/(C*L)));
    Tf(i)=Tftop/Tfbot(i); 
    hold on;
    figure(9)
    step(Tf(i), 0.005);
   
  
    Labels = '\R=' + string(R);     
    legend(Labels)

end 
hold off; 

% Underdamped: R= Between 231-693 ohms 
% Overdamped: R=1155+
% Undamped: R=0-231 ohms
% Critically damped: R=924

% Zeta is used, R is calculated using a range of zeta values, that way
% "guess and check" is not the method used to find resistance values.
% Underdamped, overdamped, and undamped was found by graph characteristics
% such as OS percentage. Critically damped does not have any visually
% unique characterisitcs, we looked for repeated poles on the real axis in
% order to find where it was critically damped. The resistance overall is
% changing the zeta value or damping frequency, which has an effect on step
% response. The resistance amd damping frequency have a direct relationship
% so as R increases, so does zeta and the step response will change as was
% analyzed previouslly in this lab. 

%%

pos=((1.59-1)/1)*100
zeta=(-log(pos/100))/sqrt(pi^2+log(pos/100)^2)
Ts=17
wn=4/(Ts*zeta)

s=tf('s')
G=(wn^2)/((s^2)+(2*wn*zeta*s)+(wn^2))
figure(11)
step(G)
num=(wn^2);
den=[1,2*wn*zeta,wn^2];
% State Space
[A,B,C,d]=tf2ss(num, den)

%{
Measured normalized heading, measured by hand then verify with matlab the
response from the heading.
Solved with system, found the settling time.
Problem was that the ship was swinging back and forth (it will eventully
stabilize) and we do not know how the ship responds to input. From that
swinging, we were given a normalized step response from which we were able
to determine a transfer function for the ships motion. We saw that given
very little information, we were able to accurately model the ships
behavior and get very close to perfectly modeling the ship's step response
graph.
%}


%% Conclusion 

%{
The lab began by examining the transfer function of a simple RLC circuit. 
We plotted and analyzed its step and frequency responses, 
revealing an underdamped system. We then explored how damping ratio and 
natural frequency influence pole locations. After plotting poles on the 
s-plane for the continuous-time transfer function, we created a for loop 
to vary the damping ratio within a specified range. Similarly, we used 
another for loop to vary the natural frequency and plotted the results. 
Analysis showed that increasing damping ratio leads to larger real and 
complex pole values. Regarding the natural frequency's effect on pole 
location, we observed that as it increased, pole magnitudes approached 
zero.
%}
%%










