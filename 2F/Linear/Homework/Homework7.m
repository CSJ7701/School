addpath(genpath("/home/csj7701/class/F23/Linear"))

%% Group 1
% Butterworth Bandpass

Amax1=1;
Amin1=25;
LP1=3000;
UP1=4000;
LS1=1500;
US1=8000;
[W1,CF1]=CJ_BPW(UP1,LP1,US1,LS1) % Find W using Band Pass Symmetry Function
n1=CJ_Butterorder(Amin1,Amax1,W1) % Find Order
w01=CJ_w0low(1,Amax1,n1)
bpoles1=CJ_Butterpoles(n1,W1) % Find Butterworth Poles using W from Symmetry Function
b1=CJ_BPB(UP1,LP1) % Find B
poles1=CJ_BandPoles(b1,CF1,bpoles1) % find Bandpass poles from b and butterworth poles
[w01,Q1]=CJ_QW(poles1) % find w0's and q's for band pass poles

%%% Something's Wrong. My answers aren't correct - not sure whether there's
%%% an issue with my code, or with my logic/sequence of events.


%% Group 2
%Chebyshev Bandpass

Amax2=0.5;
Amin2=20;
LP2=4000;
UP2=5000;
LS2=2500;
US2=8500;
W2=CJ_BPW(UP2,LP2,US2,LS2);
n2=CJ_ChevyOrder(Amin2,Amax2,W2);
bpoles2=CJ_Butterpoles(n2,W2);
cpoles2=CJ_ChevyPoles(Amax2,n2,bpoles2);
b2=CJ_BPB(UP2,LP2);
poles2=CJ_BandPoles(b2,cpoles2);
[wo2,Q2]=CJ_QW(poles2);


%% Group 3
% Chebyshev Notch (I am group 3, don't need to do this)

Amax3=0.5;
Amin3=25;
LP3=2000;
UP3=5000;
LS3=2500;
US3=4000;
