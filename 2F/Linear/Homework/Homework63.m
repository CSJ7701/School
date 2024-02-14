  wp=40000;
  wo1=1.0174*wp;
  q1 = 6.1521;
  wo2=0.7759*wp;
  q2 = 1.7174;
  wo3=0.4112*wp;
  q3 = 0.666;

  VD = 10^(-0.4/20);

  n1=[0 0 wo1^2];
  n2=[0 0 wo2^2];
  n3=[0 0 wo3^2];
  d1=[1 wo1/q1 wo1^2];
  d2=[1 wo2/q2 wo2^2];
  d3=[1 wo3/q3 wo3^2];

  w=logspace(3,5,1000);
  H1=freqs(n1,d1,w);
  H2=freqs(n2,d2,w);
  H3=freqs(n3,d3,w);
  H=VD*H1.*H2.*H3;

  H1db=20*log10(abs(H1));
  H2db=20*log10(abs(H2));
  H3db=20*log10(abs(H3));
  Hdb=20*log10(abs(H));

  semilogx(w,Hdb,w,H1db,w,H2db,w,H3db);grid;
