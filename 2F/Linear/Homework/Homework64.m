addpath(genpath("/home/csj7701/class/F23/Linear"))
Amax=2;
Amin=30;
wp=5000;
ws=2500;
w=CJ_W(ws,wp);

n=CJ_ChevyOrder(Amin,Amax,w)
bpoles=CJ_Butterpoles(n,w);
cpoles=CJ_ChevyPoles(Amax,n,bpoles);
CJ_QW(cpoles);

w_act=wp*(1./abs(cpoles));


w01=10622;
w02=5188;
q1=0.929;
q2=4.59;

n1=[1 0 0];
n2=[1 0 0];
d1=[1 w01/q1 w01^2];
d2=[1 w02/q2 w02^2];

w=logspace(3,5,1000);
H1=freqs(n1,d1,w);
H2=freqs(n2,d2,w);
H=H1.*H2;

H1db=20*log10(abs(H1));
H2db=20*log10(abs(H2));
Hdb=20*log10(abs(H));

semilogx(w,H1db,w,H2db,w,Hdb);grid;




