sys=tf([1.53],[0.0254 1 0]);
figure(1)
rlocus(sys);
hold on;
sd=-40+54.574i;
plot(real(sd), imag(sd), '^');

%%

frac=(1.53)/((-40+i*54.574)*(0.0254*(-40+i*54.574)+1));
abs(frac)
phase(frac)