F1 = 2000;
F2 = 3200; 
Fs = 15000;

t = 0:1/Fs:(10000)/Fs;
inputSignal = cos(2*pi*F1*t) + cos(2*pi*F2*t);

figure;
subplot(4, 1, 1);
plot(t, inputSignal);
xlabel('Time (s)');
ylabel('Amplitude');
title('Input');

subplot(4, 1, 2);
f = linspace(0, Fs/2, length(inputSignal)/2);
inputSignalFFT = abs(fft(inputSignal));
plot(f, inputSignalFFT(1:length(f)));
xlabel('Frequency');
ylabel('Magnitude');
title('Input fft');

cutOffFreq =  3 * F1 / Fs;
filterOrder = 100;
b = fir1(filterOrder, cutOffFreq, 'high');

filteredSignal = filter(b, 1, inputSignal);

subplot(4, 1, 3);
plot(t, filteredSignal);
xlabel('Time');
ylabel('Amplitude');
title('Output');

subplot(4, 1, 4);
filteredSignalFFT = abs(fft(filteredSignal));
plot(f, filteredSignalFFT(1:length(f)));
xlabel('Frequency');
ylabel('Magnitude');
title('Output fft');

%{
%3
applyFilter('input.wav', 'output.wav');
function applyFilter(inputFile, outputFile)
    [inputSignal, fs] = audioread(inputFile);
    outputSignal = filter([-0.000919098208468256032757648377184978017,  0.000005727059532390275441800144701209874], [1.507943758424029390141640760703012347221+0.000000000000001776356839400250464677811i 0.769755413823339007528545607783598825336+0.000000000000001332267629550187848508358i], inputSignal);
    
    inputSpectrum = abs(fft(inputSignal));
    outputSpectrum = abs(fft(outputSignal));
    
    audiowrite(outputFile, outputSignal, fs);
    
    figure;
    subplot(2, 1, 1);
    plot(linspace(0, fs, length(inputSpectrum)), inputSpectrum);
    title('input spectrum');
    xlabel('frequency');
    ylabel('magnitude');
    
    subplot(2, 1, 2);
    plot(linspace(0, fs, length(outputSpectrum)), outputSpectrum);
    title('output  spectrum');
    xlabel('frequency');
    ylabel('magnitude');
    
end
}%
