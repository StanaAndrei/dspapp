
[signal, fs] = audioread('input.wav');
plotSignalAMS(signal, fs);

addTremolo('input.wav', 'output.wav', 0.95, 40);

addEcho('input.wav', 'output-with-feedback.wav', 6000)

function addEcho(inputWavefile, outputWavefile, circularBuffSize)
    [inputSignal, sampleRate] = audioread(inputWavefile);
    circularBuffer = zeros(circularBuffSize, size(inputSignal, 2));
    bufferIndex = uint32(1);
    circularBuffer2 = zeros(circularBuffSize, size(inputSignal, 2));
    gain = 0.5;
    gainFB = 0.5;
    outputSignal = zeros(size(inputSignal));
    
    for i = 1:size(inputSignal, 2)
        for j = 1:size(inputSignal, 1)
            delayedSample = circularBuffer(bufferIndex, i);
            delaySample2 = circularBuffer2(bufferIndex, i);
            %outputSignal(j, i) = inputSignal(j, i) + gain*delayedSample;
            outputSignal(j, i) = gainFB*delaySample2 + inputSignal(j, i) + (gain - gainFB)*delayedSample;
            circularBuffer(bufferIndex, i) = inputSignal(j, i);
            circularBuffer2(bufferIndex, i) = outputSignal(j, i);
            
            bufferIndex = bufferIndex + 1;
            if bufferIndex > circularBuffSize
                bufferIndex = uint32(1);
            end
        end
    end
    audiowrite(outputWavefile, outputSignal, sampleRate);
    
    figure;
    
    subplot(2, 1, 1);
    plot(inputSignal);
    title('input');
    
    subplot(2, 1, 2);
    plot(outputSignal);
    title('output');
    
    plotSignalAMS(outputSignal, sampleRate);
end


function addTremolo(inputFile, outputFile, modAmpl, modFr)
    [inputWave, fs] = audioread(inputFile);
    
    carrier = zeros(1, length(inputWave));
    outputWave = zeros(1, length(inputWave));
    for i=1:length(inputWave)
        carrier(i) = 1 + modAmpl*sin(2*pi*modFr/fs*i);
        outputWave(i) = inputWave(i) * carrier(i);
    end
    
    audiowrite(outputFile, outputWave, fs);
    
    figure;
    
    subplot(3,1,1);
    plot(inputWave(1:1000));
    title('input');
    xlabel('time');
    ylabel('amplitude');
    
    subplot(3,1,2);
    plot(outputWave(1:1000));
    title('output');
    xlabel('time');
    ylabel('amplitude');
    
    subplot(3,1,3);
    plot(carrier(1:1000));
    title('carrier');
    xlabel('time');
    ylabel('amplitude');
    
    figure;
    subplot(3,1,1);
    spectrogram(inputWave);
    title('input');

    subplot(3,1,2);
    spectrogram(outputWave);
    title('output');

    
    subplot(3,1, 3);
    spectrogram(carrier);
    title('carrier');

    plotSignalAMS(outputWave, fs);
end

function plotSignalAMS(signal, fs)
    t = (0:length(signal)-1)/fs;
    figure;
    subplot(3,1,1);
    plot(t, signal);
    title('amplitude');
    xlabel('time');
    ylabel('amplitude');
    
    subplot(3, 1, 2);
    n = length(signal);
    f = (0:n-1) * fs/n;
    magnitude = abs(fft(signal)/n);
    plot(f, magnitude);
    title('magnitude');
    xlabel('frequency');
    ylabel('magnitude');
    
    subplot(3, 1, 3);
    spectrogram(signal(:,1));
    title('spectogram');
    xlabel('time');
    ylabel('frequency');
end
%}
%{
t=0:0.001:1;
signal = 15 * sin(2*pi*10*t - pi/4) + 20 * sin(2*pi*30*t) + 35 * sin(2*pi*70*t + 3*pi/4);
signal(abs(signal) < 1e-5) = 0;

N1 = length(signal);
FFT1 = fft(signal);

Fs = 1000;
f = -500:(Fs/length(t)):(500 - Fs/length(t));


magnitudine1 = abs(FFT1);
phase = angle(FFT1);

subplot(2,1,1)
plot(f,fftshift(magnitudine1))
title('Signal')
xlabel('frequency')
ylabel('magnitude')

subplot(2,1,2)
plot(f,fftshift(phase))
xlabel('frequency')
ylabel('phase')
%}