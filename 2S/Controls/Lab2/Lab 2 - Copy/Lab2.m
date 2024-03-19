Max_speed=max(wl(:,2));
Gain=Max_speed./Vm;
Gain_db=20*log10(Gain);
Avg_Gain=mean(Gain);
% Above here was given in the lab report.

Freq_List=[0 0.2 0.4 0.6 0.8 1 1.2 1.4 1.6 1.8 10 20 30 40 50 60 70 80 90 100];
% list of frequencies - essentially given from the table
Freq_List_rs=Freq_List.*6.28;
% Converting to radians per second
Gain_List=[1.6276 1.6276 1.62155 1.6118 1.6069 1.58865 1.57285 1.56555 1.5424 1.53145 0.92635 0.6366 0.46125 0.4065 0.34805 0.2945 0.2543 0.2263 0.2141 0.18855];

Gain_db_List=20*log10(Gain_List);

figure(1)
semilogx(Freq_List_rs,Gain_List,'-')
title("Linear Frequency Response")
xlabel("Frequency (rad/s)")
ylabel("Gain (Linear)")
grid on;
[x,y]=ginput(1);
al_lin=2*pi*x;
tau_lin=1/al_lin;

figure(2)
semilogx(Freq_List_rs, Gain_db_List, '-')
title("Logarithmic Frequency Response")
xlabel("Frequency (rad/s)")
ylabel("Gain (Logarithmic)")
grid on;
[x,y]=ginput(1);
al_log=2*pi*x;
tau_log=1/al_lin;

%% Part 2
% (7)
% (8)
figure(3)
% Plot time response from step response
plot(wl(:,1),wl(:,3))
hold on
plot(wl(:,1),wl(:,2))
hold off


figure(4)
plot(wl(:,1),wl(:,2))
hold on
plot(Vm(:,1),Vm(:,2))
title("Use this one for Ginput")

uiwait(msgbox("Select Steady State"))
[~,yss]=ginput(1);
uiwait(msgbox("Select Initial Values"))
[t0, y0]=ginput(1);
yline(0.63*yss+y0)
uiwait(msgbox("Select t1 - Intersection"));
[t1, y1]=ginput(1);
uiwait(msgbox("Select U Min"))
[~, u_min]=ginput(1);
uiwait(msgbox("Select U Max"))
[~, u_max]=ginput(1);

%{
For ginput:
we are selecting yss, which is effectively max y,
t0 and y0, which are the values when the graph first begins to rise,
t1 and y1, which is the intersection between the graph and the horizontal
line,
and umin and umax, which are the min and max of the step function
%}
%%
K=(yss-y0)/(u_max-u_min)
tau=t1-t0

%% Part 3

K=1.528;
tau=0.0252;

%{
Changing K (initially 1):
No visible effect when changing to 1.25
Tried changing to 2 - ideal response was significantly higher (5)


Changing tau to 0.2 (from 0.1):
y0 was higher, and the ideal plot for wl seemed shallower 


Explain why the nominal values differ from the ideal:
- Real world factors such as friction
- Physical differences in the machine (wear and tear, manufacturing
imperfections, etc)
- General inefficiency


%}


