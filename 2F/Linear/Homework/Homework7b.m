%% Notes with Doc Hartnett
%/ In gain equation use normalized W0
% In notmalized W0 values, Section 1 is alway >1, Section 2 is always <1


%/
%% Problem 1
Amax_1=1;
Amin_1=25;
P1_1=3000;
P2_1=4000;
S1_1=1500;
S2_1=8000;

Ratio_1=6.5;
Order_1=4;
CF_1=3464.1;
W0NORM_1=[18845.95,25137]; %%% IM DUMB - These are the un normalized values
W0_1=W0NORM_1./(2*pi*CF_1); %%% These are normalized
Q_1=[3.5309,3.5309];

% Stage 1
C_1(1)=0.01e-06;
Ra_1(1)=10000;
Rb_1(1)=(3-(sqrt(2)/Q_1(1)))*Ra_1(1);
A_1(1)=1+(Rb_1(1)/Ra_1(1));
SCF_1(1)=1/W0_1(1);
G_1(1)=-10*log10(1+(Q_1(1)^2)*((1/SCF_1(1))-SCF_1(1))^2)+20*log10((2*sqrt(2)*Q_1(1))-1);
% This gain is in dB.
% Converting gian to linear to find the gain of the Voltage Divider
G_Lin_1(1)=10^(-G_1(1)/20);
Req_1(1)=sqrt(2)/(C_1(1)*W0NORM_1(1));
syms R1 R2
VD1_1 = solve((R2*R1)/(R1+R2) == Req_1(1), R2/(R1+R2) == G_Lin_1(1));

% Stage 2
C_1(2)=0.01e-06;
Ra_1(2)=10000;
Rb_1(2)=(30-(sqrt(2)/Q_1(2)))*Ra_1(2);
SCF_1(2)=1/W0_1(2);
G_1(2)=-10*log10(1+(Q_1(2)^2)*((1/SCF_1(2))-SCF_1(2))^2)+20*log10((2*sqrt(2)*Q_1(2))-1);
G_Lin_1(2)=10^(-G_1(2)/20);
Req_1(2)=sqrt(2)/(C_1(2)*W0NORM_1(2));
VD2_1 = solve((R2*R1)/(R1+R2) == Req_1(2), R2/(R1+R2) == G_Lin_1(2));

%% Problem 2
Amax_2=0.5;
Amin_2=20;
P1_2=4000;
P2_2=5000;
S1_2=2500;
S2_2=8000;

Ratio_2=5.5;
Order_2=4;
CF_2=sqrt(S1_2*S2_2);
W0NORM_2=[0.89371,1.1189];
W0_2=W0NORM_2.*(2*pi*CF_2); % un normalize - mult by CF
Q_2=[6.3136,6.3136];

% Stage 1
C_2(1)=(0.000000005);
Req_2(1)=1/(C_2(1)*W0_2(1));
Stage1R(1)=Req_2(1)/(2*Q_2(1));
Stage1R(2)=(2*Q_2(1)*Req_2(1));
% Plug in CF for frequency in order to find at overall center frequency
G_2(1)=-10*log10(1+(Q_2(1)^2)*((1/W0NORM_2(2))-W0NORM_2(2))^2)+20*log10(2*(Q_2(1)^2));
% Convert to Linear
G_Lin_2(1)=10^(-G_2(1)/20);
VD1_2=solve((R2*R1)/(R1+R2) == Stage1R(1), R2/(R1+R2) == G_Lin_2(1)); 



% Stage 2
C_2(2)=(5e-09);
Req_2(2)=1/(C_2(2)*W0_2(2));
Stage2R(1)=Req_2(2)/(2*Q_2(2));
Stage2R(2)=(2*Q_2(2)*Req_2(2));
G_2(2)=-10*log10(1+(Q_2(2)^2)*((1/W0NORM_2(1))-W0NORM_2(1))^2)+20*log10(2*(Q_2(2)^2));
G_Lin_2(2)=10^(-G_2(2)/20);
VD2_2=solve((R2*R1)/(R1+R2) == Req_2(2), R2/(R1+R2) == G_Lin_2(2));


