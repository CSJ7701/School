addpath(genpath("/home/csj7701/class/F23/Linear"))

Amax=1.5;
Amin=35;
wp=1200;
ws=4800;

w=CJ_W(ws,wp);
n=CJ_ChevyOrder(Amin,Amax,w)
bpoles=CJ_Butterpoles(n,w);
cpoles=CJ_ChevyPoles(Amax,n,bpoles);
CJ_QW(cpoles);

w_act=wp*(1./abs(cpoles));

wo1=0.9225*wp;
wo2=0.4211*wp;
q1=2.2912;
q2=0.5;

n1=[0 0 wo1^2];
n2=[0 wo2];
d1=[1 wo1/q1 wo1^2];
d2=[1 wo2];

w=logspace(1,5,1000);

H1=freqs(n1,d1,w);
H2=freqs(n2,d2,w);
H=H1.*H2;

H1db=20*log10(abs(H1));
H2db=20*log10(abs(H2));
Hdb=20*log10(abs(H));

semilogx(w,Hdb,w,H1db,w,H2db);grid;

