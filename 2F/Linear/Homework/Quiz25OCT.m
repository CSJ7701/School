addpath(genpath("/home/csj7701/class/F23/Linear"))
%% Chebychev Notch Filter

Amax=0.5;%db
Amin=25;%db
wp1=2;%Hz
wp2=5;%hz
ws1=2.5;%hz
ws2=4;%hz
wp=abs(wp1-wp2);
ws=abs(ws1-ws2);
w=CJ_W(ws,wp);


n=CJ_ChevyOrder(Amin, Amax, w);
bpoles=CJ_Butterpoles(n,w)
cpoles=CJ_ChevyPoles(Amax,n,bpoles)