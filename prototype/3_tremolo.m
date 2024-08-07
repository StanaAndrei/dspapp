addTremolo('input2.wav', 'output.wav', 0.95, 40);

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

end