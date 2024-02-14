%%% Below is some sample code to read, analyze in the frequency domain,
%%% filter and write music wav files.
%%% Of course you can also plot in the time domain if you like!
%%% Music_Analyzer.m
%%% 28 November 2022
%%%
 
clear
close all
[filenamein, pathnamein] = uigetfile('*.wav', 'Pick a "bad" .wav file to filter ...  ');

filenameout='Filtered_Wav_File.wav';
 
%% Read in the wave file
[y,fs]=audioread([pathnamein filenamein]);
 
%% Sample code to display Power Spectral Density
figure(1)
% % PWELCH Power Spectral Density estimate via Welch's method.
% %     [Pxx,F] = PWELCH(X,WINDOW,NOVERLAP,NFFT,Fs) estimates Power Spectral Density 
% %     of a discrete-time signal vector X.  
% %     PWELCH with no output arguments by default plots the PSD estimate in dB per unit 
% %     frequency in the current figure window.
% %     Note:  This is computing a frequency domain average.  (It has no phase info) **
 
[Pxx,F] = pwelch(y,hann(22050),0,22050,1);
plot(F, 10*log10(abs(Pxx)))
title(['PSD of file: ', filenamein])
xlabel('Fraction of Sampling Frequency')
ylabel('Power Spectrum Magnitude (dB)')
grid on
 
%% Sample code to use Freqz command for frequency domain plot
figure(2)
% %  [H,W] = FREQZ(B,A,N) returns the N-point complex frequency response
% %     vector H and the N-point frequency vector W in radians/sample of
% %     the filter.
% %    This does not average
[H,w]=freqz(y(1:4096),1,4096);
plot(w/(2*pi), 20*log10(abs(H)));
title(['FREQZ of file: ', filenamein])
xlabel('Fraction of Sampling Frequency')
ylabel('Magnitude (dB)')
grid on
 
 
%% Sample code to display Spectrogram - takes a while to perform this
% % You may want to comment this out after using it once or twice
figure(3)
% %  SPECGRAM Calculate spectrogram from signal.
% %     [B,F,T] = SPECGRAM(A,NFFT,Fs,WINDOW,NOVERLAP) calculates the spectrogram for 
% %     the signal in vector A. 
specgram(y,2048,1)                
title(['SPECGRAM of file: ', filenamein])
ylabel('Fraction of Sampling Frequency')
xlabel('Time (samples)')
grid on
colorbar
 
% % Send data to sound card - Listen to wav file
numsecs=10;
sound(y(1:numsecs*fs),22050);
disp('Press enter to continue')
pause
 
%% Sample code for filtering and writing new wav file
 
% % Numerator Coefficients
num1=[1      -0.3749       1 ];
num2=[1      -0.3749       1 ];
num3=[1      -0.3749       1 ];
num4=[1      -0.3749       1 ];
   
% % Denominator Coefficients
den1=[1   -0.4107    0.8383];
den2=[1   -0.2772    0.8362];
den3=[1   -0.5268    0.9308];
den4=[1   -0.1911    0.9285];
 
% % Combine Coefficients into single numerator and denominator
num=conv(num1, num2);
num=conv(num, num3);
num=conv(num, num4)
den=conv(den1, den2);
den=conv(den, den3);
den=conv(den, den4)
      
k=1/(max(abs(freqz(num, den, 1024))));  %scale numerator to set max gain to 0 dB
    
num=num*k;
 
 
%% Plot Magnitude Response of your filter
figure(4)
[H,w]=freqz(num,den,4096);
plot(w/2/pi,20*log10(abs(H)))
title('Magnitude Response of Filter')
ylabel('Magnitude Response (dB)')
xlabel('Fraction of Sampling Frequency')
axis([0 0.5 -50 10]);
grid on
 
%% Plot pole/zero plot
figure(5)
zplane(num,den)
title('Pole/Zero Plot')
    
%% Implement filter
newy=filter(num, den, y);
%newy=newy/max(abs(newy));   %% use if necessary to prevent clipping in
                                                        % wavwrite function (this is effectively a
                                                        % gain change
 
%% Save filtered data to wavefile
audiowrite(filenameout, newy, fs);
  
%% look at filtered file in frequency domain
figure(6)
[Pnewy,F] = pwelch(newy,hann(22050),0,22050,1);
plot(F, 10*log10(abs(Pnewy)))
title(['PSD of file: ', filenameout])
xlabel('Fraction of Sampling Frequency');
ylabel('Power Spectrum Magnitude (dB)') 
axis([0 0.5 -50 10]);
grid on
 
%%  Look at both filtered and unfiltered file on same plot
% % in the frequency domain
figure(7)
[pyy, f] = pwelch(y,hann(22050),0,22050,1);
[pyynew, f] = pwelch(newy,hann(22050),0,22050,1);
magy=10*log10(abs(pyy));
magynew=10*log10(abs(pyynew));
plot(f,magy,f,magynew);
title(['PSD of files: ', filenamein , ' and ' filenameout])
xlabel('Fraction of Sampling Frequency');
ylabel('Power Spectrum Magnitude (dB)') 
axis([0 0.5 -50 10]);
grid on
legend('Original Music', 'Filtered Music')   
 
%% Send filtered data to sound card
disp('Press Enter to Continue and to Play Filtered Music')
pause
numsecs=10;
sound(newy(1:numsecs*fs),22050);
 
 
%% group delay plot
% figure(10)
% [gd,wd]=grpdelay(num,den,512);
% plot(wd/2/pi, gd)
% title('Group Delay of Filter')
% xlabel('Fraction of Sampling Frequency');
% ylabel('Group Delay in Samples');  
% grid on
 
