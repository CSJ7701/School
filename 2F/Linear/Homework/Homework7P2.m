addpath(genpath("/home/csj7701/class/F23/Linear"))

%%Group 1
% Butterworth Bandpass
Amax1=1;
Amin1=25;
LP1=2*pi*3000;
UP1=2*pi*4000;
LS1=2*pi*1500;
US1=2*pi*8000;

[W1,CF1]=CJ_BPW(UP1,LP1,US1,LS1)
n1=CJ_Butterorder(Amin1,Amax1,W1)
w01=CJ_w0low(1,Amax1,n1)
bpoles1=CJ_Butterpoles(n1,w01)
b1=CJ_BPB(UP1,LP1)
poles1=CJ_BandPoles(b1,CF1,bpoles1)
[w01,Q1]=CJ_QW(poles1)

